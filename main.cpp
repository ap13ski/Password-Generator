#include <windows.h>
#include <commctrl.h>
#include <string>
#include "password.h"
#include "clipboard.h"

#pragma comment(lib, "comctl32.lib")

#define ID_TRACKBAR_NUMBER			1001
#define ID_LABEL_NUMBER				1002
#define ID_LABEL_SYMBOLS			1003
#define ID_CHECKBOX_LOWER			1004
#define ID_CHECKBOX_UPPER			1005
#define ID_CHECKBOX_DIGITS			1006
#define ID_CHECKBOX_SPECIAL			1007
#define ID_TEXTBOX_PASSWORD			1008
#define ID_BUTTON_COPY				1009
#define ID_BUTTON_GENERATE			1010

#define DEFAULT_NUMBER		12
#define RANGE_MIN 			5
#define RANGE_MAX 			30
#define DEFAULT_TICFREQ 	1
#define DEFAULT_PAGESIZE 	1

//=============================================================================
HWND ctlGroupboxSettings;
HWND ctlTrackBarNumber;
HWND ctlLabelNumber;
HWND ctlLabelSymbols;
HWND ctlCheckboxLower;
HWND ctlCheckboxUpper;
HWND ctlCheckboxDigits;
HWND ctlCheckboxSpecial;
HWND ctlTextboxPassword;
HWND ctlButtonCopy;
HWND ctlButtonGenerate;

HFONT hFont;
HFONT hFontMono;

NS_CLIPBOARD::Clipboard clipboard;

int number = DEFAULT_NUMBER;
bool isCheckboxLower = true;
bool isCheckboxUpper = true;
bool isCheckboxDigits = true;
bool isCheckboxSpecial = true;
NS_PASSWORD::PasswordGenerator pGenerator(number, isCheckboxLower, isCheckboxUpper, isCheckboxDigits, isCheckboxSpecial);

bool isTracking = false;

int tabOrder[] = {
	ID_TRACKBAR_NUMBER,		// 0
	ID_CHECKBOX_LOWER,		// 1
	ID_CHECKBOX_UPPER,		// 2
	ID_CHECKBOX_DIGITS,		// 3
	ID_CHECKBOX_SPECIAL,	// 4
	ID_TEXTBOX_PASSWORD,	// 5
	ID_BUTTON_GENERATE,		// 6
	ID_BUTTON_COPY			// 7
};

int currentFocus = 0;

//=============================================================================
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CreateFontCustom(HFONT& hFont, LPCTSTR fontFamily, int fontSize);
void CreateControls(HWND hwnd);
void UpdateNumber();
void UpdateLabelNumber();
void UpdateFont(HWND& hCtrl, HFONT& hFont);
void UpdateFonts();
void UpdateTextboxPassword();

void ChangeFocusByTabIncrease();
bool GetCheckboxState(HWND hwnd, int nIDButton);
bool ClipboardCopy(const std::string& str);
std::string Generate(int number, bool isCheckboxLower, bool isCheckboxUpper, bool isCheckboxDigits, bool isCheckboxSpecial);
std::string GetEditText(HWND hEdit);

//=============================================================================
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow)
{
	const char szAppName[] = TEXT("WinAPI Password Generator");
	const char szErrRegClass[] = TEXT("Error while registering a class instance.\nApplication will be terminated.");
	HWND hwnd;
	MSG msg;

	WNDCLASSEX wndmain; // = {0};				
	wndmain.cbSize = sizeof(WNDCLASSEX);					// UINT cbSize; 		// Size in bytes --> sizeof(WNDCLASSEX)
	wndmain.style = 0;										// UINT style;			// Specifies class styles (any combination)
	wndmain.lpfnWndProc = WndProc;							// WNDPROC lpfnWndProc;	// Pointer to window procedure
    wndmain.cbClsExtra = 0;									// int cbClsExtra;		// Number of extra bytes to allocate following the window-class structure
    wndmain.cbWndExtra = 0;									// int cbWndExtra;		// Number of extra bytes to allocate following the window instance
    wndmain.hInstance = hInstance;							// HINSTANCE hInstance;	// Handle to instance that contains window procedure for class.
    wndmain.hIcon = LoadIcon(NULL, IDI_APPLICATION);		// HICON hIcon;			// Handle to class icon. If NULL, system provides a default icon.
    wndmain.hCursor = LoadCursor(NULL, IDC_ARROW);			// HCURSOR hCursor;		// Handle to class cursor.
    wndmain.hbrBackground = GetSysColorBrush(COLOR_3DFACE);	// HBRUSH hbrBackground;// Handle to class background brush (HBRUSH).
    wndmain.lpszMenuName = NULL;							// LPCSTR lpszMenuName; // Pointer to c-string that specifies the resource name of the class menu (resource file).
    wndmain.lpszClassName = szAppName;						// LPCSTR lpszClassName;// Pointer to c-string (specifies window class name) or atom (class atom).
	wndmain.hIconSm = NULL;									// HICON hIconSm; 		// Handle to small icon associated with window class. If NULL, using hIcon.

    if (!RegisterClassEx(&wndmain))
	{
        MessageBox(NULL, szErrRegClass, szAppName, MB_ICONERROR);
        return 0;
    }

	hwnd = CreateWindowEx
	(
		0,									// DWORD dwExStyle			// extended window style
		wndmain.lpszClassName,				// LPCSTR lpClassName		// registered class name
		szAppName,							// LPCSTR lpWindowName		// window name
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME | WS_VISIBLE,	// DWORD dwStyle			// window style
		CW_USEDEFAULT, CW_USEDEFAULT,		// int X, int Y				// X, Y positions of window
		359, 293,							// int nWidth, int nHeight	// width, height of window
		0,									// HWND hWndParent			// handle to parent or owner window
		NULL,								// HMENU hMenu				// menu handle or child identifier
		hInstance,							// HINSTANCE hInstance		// handle to application instance
		NULL								// LPVOID lpParam			// window-creation data
	);	


	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}

//=============================================================================
void CreateControls(HWND hwnd)
{
	CreateFontCustom(hFont, "Tahoma", 0);			//TODO: Interface scaling
	CreateFontCustom(hFontMono, "Courier New", 0);	//TODO: Interface scaling

	INITCOMMONCONTROLSEX initCCEx;
	InitCommonControlsEx(&initCCEx); 	
	
	ctlGroupboxSettings = CreateWindowEx(0, TEXT("BUTTON"), TEXT("Settings"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX,10,10,331,170, hwnd, (HMENU)0, NULL, NULL);

	ctlLabelNumber = CreateWindowEx
	(
		0,						// DWORD dwExStyle			// extended window style
		TEXT("Static"),			// LPCSTR lpClassName		// registered class name
		TEXT("0"),				// LPCSTR lpWindowName		// window name
		WS_CHILD | WS_VISIBLE,	// DWORD dwStyle			// window style
		19, 40,					// int X, int Y				// X, Y positions of window
		250, 16,				// int nWidth, int nHeight	// width, height of window
		hwnd,					// HWND hWndParent			// handle to parent or owner window
		(HMENU)ID_LABEL_NUMBER,	// HMENU hMenu				// menu handle or child identifier
		0,						// HINSTANCE hInstance		// handle to application instance
		NULL					// LPVOID lpParam			// window-creation data
	);
	
	ctlTrackBarNumber = CreateWindowEx
	(
		0,										// DWORD dwExStyle			// extended window style
		TRACKBAR_CLASS,							// LPCSTR lpClassName		// registered class name
		TEXT("WinAPI Password Generator"),		// LPCSTR lpWindowName		// window name
		WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | WS_TABSTOP,	// DWORD dwStyle			// window style
		12, 62,									// int X, int Y				// X, Y positions of window
		327, 40,								// int nWidth, int nHeight	// width, height of window
		hwnd,									// HWND hWndParent			// handle to parent or owner window
		(HMENU)ID_TRACKBAR_NUMBER,				// HMENU hMenu				// menu handle or child identifier
		0,										// HINSTANCE hInstance		// handle to application instance
		NULL									// LPVOID lpParam			// window-creation data
	);

	SendMessage(ctlTrackBarNumber, TBM_SETRANGE,  TRUE, MAKELONG(RANGE_MIN, RANGE_MAX)); 
	SendMessage(ctlTrackBarNumber, TBM_SETTICFREQ, DEFAULT_TICFREQ, 0); 
	SendMessage(ctlTrackBarNumber, TBM_SETPAGESIZE, 0,  DEFAULT_PAGESIZE); 
	SendMessage(ctlTrackBarNumber, TBM_SETPOS, TRUE, number); 

	ctlLabelSymbols = CreateWindowEx
	(
		0,						// DWORD dwExStyle			// extended window style
		TEXT("Static"),			// LPCSTR lpClassName		// registered class name
		TEXT("Characters included:"),	// LPCSTR lpWindowName		// window name
		WS_CHILD | WS_VISIBLE,	// DWORD dwStyle			// window style
		19, 113,				// int X, int Y				// X, Y positions of window
		250, 16,				// int nWidth, int nHeight	// width, height of window
		hwnd,					// HWND hWndParent			// handle to parent or owner window
		(HMENU)ID_LABEL_SYMBOLS,// HMENU hMenu				// menu handle or child identifier
		0,						// HINSTANCE hInstance		// handle to application instance
		NULL					// LPVOID lpParam			// window-creation data
	);

	ctlCheckboxLower = CreateWindowEx(0, TEXT("BUTTON"), TEXT("a-z"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | WS_TABSTOP, 20, 136, 55, 30, hwnd, (HMENU)ID_CHECKBOX_LOWER, NULL, NULL);
	ctlCheckboxUpper = CreateWindowEx(0, TEXT("BUTTON"), TEXT("A-Z"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | WS_TABSTOP, 90, 136, 55, 30, hwnd, (HMENU)ID_CHECKBOX_UPPER, NULL, NULL);
	ctlCheckboxDigits = CreateWindowEx(0, TEXT("BUTTON"), TEXT("0-9"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | WS_TABSTOP, 160, 136, 55, 30, hwnd, (HMENU)ID_CHECKBOX_DIGITS, NULL, NULL);
	ctlCheckboxSpecial = CreateWindowEx(0, TEXT("BUTTON"), TEXT("@#$"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | WS_TABSTOP, 230, 136, 60, 30, hwnd, (HMENU)ID_CHECKBOX_SPECIAL, NULL, NULL);
	
	SendMessage(ctlCheckboxLower, BM_SETCHECK, TRUE, 0); 
	SendMessage(ctlCheckboxUpper, BM_SETCHECK, TRUE, 0); 
	SendMessage(ctlCheckboxDigits, BM_SETCHECK, TRUE, 0); 
	SendMessage(ctlCheckboxSpecial, BM_SETCHECK, TRUE, 0); 

	ctlTextboxPassword = CreateWindowEx(WS_EX_CLIENTEDGE | WS_EX_RIGHT, TEXT("EDIT"), TEXT("0"), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, 10, 190, 331, 25, hwnd, (HMENU)ID_TEXTBOX_PASSWORD, NULL, NULL);

	ctlButtonCopy = CreateWindowEx
	(
		0,											// extended window style
		"BUTTON",									// predefined class 
		"Copy",										// button text 
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP,	// styles 
		150, 225,									// X, Y positions of window 
		91, 28,										// width, height of window
		hwnd,										// parent window 
		(HMENU)ID_BUTTON_COPY,						// menu handle or child identifier 
		(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE), // handle to application instance
		NULL // pointer not needed 
	);     

	ctlButtonGenerate = CreateWindowEx
	(
		0,											// extended window style
		"BUTTON",									// predefined class 
		"Generate",									// button text 
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON ,	// styles 
		250, 225,									// X, Y positions of window 
		91, 28,									// width, height of window
		hwnd,										// parent window 
		(HMENU)ID_BUTTON_GENERATE,					// menu handle or child identifier 
		(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE), // handle to application instance
		NULL // pointer not needed 
	); 
	
	UpdateLabelNumber();
	UpdateTextboxPassword();

	//TODO: Interface scaling
	//UpdateFonts();
	
	//SetFocus(ctlButtonGenerate);
}

//=============================================================================
void UpdateNumber() 
{
	number = SendMessage(ctlTrackBarNumber, TBM_GETPOS, 0, 0);	
}

//=============================================================================
void UpdateLabelNumber() 
{
	TCHAR buffer[30]; 
	wsprintf(buffer, TEXT("Characters count: %ld"), number);
	SetWindowText(ctlLabelNumber, buffer);	
}

//=============================================================================
std::string Generate(int number, bool isCheckboxLower, bool isCheckboxUpper, bool isCheckboxDigits, bool isCheckboxSpecial)
{	
	std::string password = pGenerator.GenerateNewPassword(number, isCheckboxLower, isCheckboxUpper, isCheckboxDigits, isCheckboxSpecial);
	return password;
}

//=============================================================================
void UpdateTextboxPassword()
{
	std::string password = Generate(number, isCheckboxLower, isCheckboxUpper, isCheckboxDigits, isCheckboxSpecial);
	SetWindowText(ctlTextboxPassword, password.c_str());
}

//=============================================================================
bool GetCheckboxState(HWND hwnd, int nIDButton)
{
	return (IsDlgButtonChecked(hwnd, nIDButton) == BST_CHECKED);
}

//=============================================================================
bool ClipboardCopy(const std::string& str)
{
	if (clipboard.SetData(str))
		{ return true; }
	else
		{ return false; }
}

//=============================================================================
std::string GetEditText(HWND hEdit)
{
    int textLength = GetWindowTextLength(hEdit);
    std::string text(textLength + 1, '\0');
    GetWindowText(hEdit, const_cast<char*>(text.data()), static_cast<int>(text.size()));
    return text;
}

//=============================================================================
void CreateFontCustom(HFONT& hFont, LPCTSTR fontFamily, int fontSize)
{
	hFont = CreateFont
	(
		fontSize, 					// int nHeight               // height of font
		0, 							// int nWidth                // average character width
		0, 							// int nEscapement           // angle of escapement
		0, 							// int nOrientation          // base-line orientation angle
		FW_NORMAL, 					// int fnWeight              // font weight
		FALSE, 						// DWORD fdwItalic           // italic attribute option
		FALSE, 						// DWORD fdwUnderline        // underline attribute option
		FALSE, 						// DWORD fdwStrikeOut        // strikeout attribute option
		DEFAULT_CHARSET, 			// DWORD fdwCharSet          // character set identifier
		OUT_DEFAULT_PRECIS, 		// DWORD fdwOutputPrecision  // output precision
		CLIP_DEFAULT_PRECIS, 		// DWORD fdwClipPrecision    // clipping precision
		DEFAULT_QUALITY, 			// DWORD fdwQuality          // output quality
		DEFAULT_PITCH | FF_SWISS, 	// DWORD fdwPitchAndFamily   // pitch and family
		fontFamily			 		// LPCTSTR lpszFace          // typeface name ex. "Tahoma"
	);
}

//=============================================================================
void UpdateFont(HWND& hCtrl, HFONT& hFont)
{
	SendMessage(hCtrl, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
	InvalidateRect(hCtrl, NULL, TRUE);
}

//=============================================================================
void UpdateFonts()
{
	UpdateFont(ctlGroupboxSettings, hFont);
	UpdateFont(ctlTrackBarNumber, hFont);
	UpdateFont(ctlLabelNumber, hFont);
	UpdateFont(ctlLabelSymbols, hFont);
	UpdateFont(ctlCheckboxLower, hFont);
	UpdateFont(ctlCheckboxUpper, hFont);
	UpdateFont(ctlCheckboxDigits, hFont);
	UpdateFont(ctlCheckboxSpecial, hFont);
	UpdateFont(ctlTextboxPassword, hFontMono);
	UpdateFont(ctlButtonCopy, hFont);
	UpdateFont(ctlButtonGenerate, hFont);
}

//=============================================================================
void ChangeFocusByTabIncrease()
{	
	/*	
	TCHAR buffer[30]; 
	wsprintf(buffer, TEXT("%ld"), currentFocus);
	SetWindowText(ctlTextboxPassword, buffer);
	*/

	SetFocus(GetDlgItem(GetActiveWindow(), tabOrder[currentFocus]));
	
	if (currentFocus == 7)
		currentFocus = 0;
	else
		currentFocus++;		
}

//=============================================================================
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_CREATE:
			CreateControls(hwnd);
			SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);
			break;

		case WM_KEYDOWN:
			if (wParam == VK_TAB)
			{ 
				//TODO: TabIndex
				//ChangeFocusByTabIncrease();
			}
			break;

		case WM_HSCROLL:
			UpdateNumber();
			UpdateLabelNumber();

			switch (LOWORD(wParam)) {
				case SB_ENDSCROLL:
				{
					if (isTracking) {isTracking = false; break;}
					UpdateTextboxPassword();  
					break;
				}
				case SB_THUMBTRACK:
				{
					UpdateTextboxPassword(); 
					isTracking = true;
					break;
				}
			}
			break;

		case WM_COMMAND:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				switch (LOWORD(wParam)) {
					
					case ID_BUTTON_COPY:
						ClipboardCopy(GetEditText(ctlTextboxPassword));
						break;

					case ID_BUTTON_GENERATE:
						UpdateTextboxPassword();
						break;	
					
					case ID_CHECKBOX_LOWER:
						isCheckboxLower = GetCheckboxState(hwnd, ID_CHECKBOX_LOWER);
						UpdateTextboxPassword();						
						break;	
					
					case ID_CHECKBOX_UPPER:
						isCheckboxUpper = GetCheckboxState(hwnd, ID_CHECKBOX_UPPER);
						UpdateTextboxPassword();
						break;	
					
					case ID_CHECKBOX_DIGITS:
						isCheckboxDigits = GetCheckboxState(hwnd, ID_CHECKBOX_DIGITS);
						UpdateTextboxPassword();
						break;	
					
					case ID_CHECKBOX_SPECIAL:
						isCheckboxSpecial = GetCheckboxState(hwnd, ID_CHECKBOX_SPECIAL);
						UpdateTextboxPassword();
						break;					
				}
			}
			break;


		case WM_DESTROY:
			PostQuitMessage(0);
			break; 
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}
//=============================================================================