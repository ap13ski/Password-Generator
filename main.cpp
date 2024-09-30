#include "main.h"


//=============================================================================

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
#define ID_BUTTON_INFO				1011

#define RANGE_MIN 			5
#define RANGE_MAX 			30
#define DEFAULT_TICFREQ 	1
#define DEFAULT_PAGESIZE 	1

//=============================================================================
const char* FONT_NORMAL = "Tahoma";
const char* FONT_MONO = "Courier New";

const char* STR_APP_NAME = "Password Generator";
const char* STR_APP_ABOUT = "About - Password Generator";

const char* STR_ERROR_REG_CLASS = "Error while registering a class instance.\nApplication will be terminated.";

const char* STR_EMPTY = "";

const char* STR_GROUPBOX_SETTINGS = "Settings";
const char* STR_LABEL_SYMBOLS = "Characters included:";
const char* STR_CHECKBOX_LOWER = "a-z";
const char* STR_CHECKBOX_UPPER = "A-Z";
const char* STR_CHECKBOX_DIGITS = "0-9";
const char* STR_CHECKBOX_SPECIAL = "@#$";

const char* STR_BUTTON_COPY = "Copy";
const char* STR_BUTTON_GENERATE = "Generate";
const char* STR_BUTTON_INFO = "Info";

const char* STR_APP_ABOUT_TEXT = 	"Password Generator v.1.0 64-bit\n\n\n"
									"Created by ap13ski\n"
									"https://github.com/ap13ski\n"
									"ap13ski@gmail.com\n\n"	
									"Compiled with MinGW-W64 v.8.1.0 64-bit\n"
									"https://sourceforge.net/projects/mingw/\n\n"	
									"Packed with UPX 4.2.4 64-bit\n"
									"https://upx.github.io/\n";

//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{	
	HWND hwnd;
	MSG msg;

	WNDCLASSEX wndmain;
	wndmain.cbSize = sizeof(WNDCLASSEX);
	wndmain.style = 0;
	wndmain.lpfnWndProc = WndProc;
    wndmain.cbClsExtra = 0;
    wndmain.cbWndExtra = 0;
    wndmain.hInstance = hInstance;
    wndmain.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP_ICON));
    wndmain.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndmain.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wndmain.lpszMenuName = NULL;
    wndmain.lpszClassName = STR_APP_NAME;
	wndmain.hIconSm = NULL;

    if (!RegisterClassEx(&wndmain))
	{
		MessageBox(NULL, STR_ERROR_REG_CLASS, STR_APP_NAME, MB_ICONERROR);
		return 0;
    }

	hwnd = CreateWindowEx(0, wndmain.lpszClassName, STR_APP_NAME, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 380, 300, 0, NULL, hInstance, NULL);	

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
	INITCOMMONCONTROLSEX initCCEx;
	InitCommonControlsEx(&initCCEx); 	
	
	ctlGroupboxSettings = CreateWindowEx(0, TEXT("BUTTON"), STR_GROUPBOX_SETTINGS, WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 10, 10, 350, 170, hwnd, (HMENU)0, NULL, NULL);

	ctlLabelNumber = CreateWindowEx	(0, TEXT("Static"), STR_EMPTY, WS_CHILD | WS_VISIBLE, 20, 40, 250, 16, hwnd, (HMENU)ID_LABEL_NUMBER, 0,	NULL);
	
	ctlTrackBarNumber = CreateWindowEx(0, TRACKBAR_CLASS, STR_EMPTY, WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | WS_TABSTOP, 12, 60, 346, 40, hwnd, (HMENU)ID_TRACKBAR_NUMBER, 0, NULL);

	SendMessage(ctlTrackBarNumber, TBM_SETRANGE,  TRUE, MAKELONG(RANGE_MIN, RANGE_MAX)); 
	SendMessage(ctlTrackBarNumber, TBM_SETTICFREQ, DEFAULT_TICFREQ, 0); 
	SendMessage(ctlTrackBarNumber, TBM_SETPAGESIZE, 0,  DEFAULT_PAGESIZE); 
	SendMessage(ctlTrackBarNumber, TBM_SETPOS, TRUE, number); 

	ctlLabelSymbols = CreateWindowEx(0, TEXT("Static"), STR_LABEL_SYMBOLS, WS_CHILD | WS_VISIBLE, 20, 119, 250, 16, hwnd, (HMENU)ID_LABEL_SYMBOLS, 0, NULL);

	ctlCheckboxLower = CreateWindowEx(0, TEXT("BUTTON"), TEXT("a-z"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | WS_TABSTOP, 20, 140, 60, 30, hwnd, (HMENU)ID_CHECKBOX_LOWER, NULL, NULL);
	ctlCheckboxUpper = CreateWindowEx(0, TEXT("BUTTON"), TEXT("A-Z"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | WS_TABSTOP, 110, 140, 60, 30, hwnd, (HMENU)ID_CHECKBOX_UPPER, NULL, NULL);
	ctlCheckboxDigits = CreateWindowEx(0, TEXT("BUTTON"), TEXT("0-9"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | WS_TABSTOP, 200, 140, 60, 30, hwnd, (HMENU)ID_CHECKBOX_DIGITS, NULL, NULL);
	ctlCheckboxSpecial = CreateWindowEx(0, TEXT("BUTTON"), TEXT("@#$"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | WS_TABSTOP, 290, 140, 60, 30, hwnd, (HMENU)ID_CHECKBOX_SPECIAL, NULL, NULL);
	
	SendMessage(ctlCheckboxLower, BM_SETCHECK, TRUE, 0); 
	SendMessage(ctlCheckboxUpper, BM_SETCHECK, TRUE, 0); 
	SendMessage(ctlCheckboxDigits, BM_SETCHECK, TRUE, 0); 
	SendMessage(ctlCheckboxSpecial, BM_SETCHECK, TRUE, 0); 

	ctlTextboxPassword = CreateWindowEx(WS_EX_CLIENTEDGE | WS_EX_RIGHT, TEXT("EDIT"), STR_EMPTY, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, 10, 190, 350, 30, hwnd, (HMENU)ID_TEXTBOX_PASSWORD, NULL, NULL);

	ctlButtonCopy = CreateWindowEx(0, "BUTTON", STR_BUTTON_COPY, WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 130, 230, 110, 30, hwnd, (HMENU)ID_BUTTON_COPY, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);     

	ctlButtonGenerate = CreateWindowEx(0, "BUTTON", STR_BUTTON_GENERATE, WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 250, 230, 110, 30, hwnd, (HMENU)ID_BUTTON_GENERATE, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL); 

	ctlButtonInfo = CreateWindowEx(0, "BUTTON", STR_BUTTON_INFO, WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP, 10, 230, 110, 30, hwnd, (HMENU)ID_BUTTON_INFO, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL); 
	
	UpdateLabelNumber();
	UpdateTextboxPassword();

	CreateFontCustom(hFontNormal, FW_NORMAL, FONT_NORMAL);
	CreateFontCustom(hFontBold, FW_BOLD, FONT_NORMAL);
	CreateFontCustom(hFontMono, FW_NORMAL, FONT_MONO);
	
	UpdateFonts();		
	
	SetFocus(ctlButtonGenerate);
}

//=============================================================================
void UpdateNumber() 
{
	number = SendMessage(ctlTrackBarNumber, TBM_GETPOS, 0, 0);	
}

//=============================================================================
void UpdateLabelNumber() 
{
	char buffer[30]; 
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
bool GetCheckboxState(HWND hwnd, int buttonID)
{
	return (IsDlgButtonChecked(hwnd, buttonID) == BST_CHECKED);
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
    int length = GetWindowTextLength(hEdit);
    if (length <= 0) { return ""; }

    std::string text(length, '\0');
    GetWindowText(hEdit, &text[0], length + 1);

    return text;
}

//===================================================
void UpdateFonts()
{	
	UpdateFont(ctlGroupboxSettings, hFontBold);
	UpdateFont(ctlTrackBarNumber, hFontNormal);
	UpdateFont(ctlLabelNumber, hFontNormal);
	UpdateFont(ctlLabelSymbols, hFontNormal);
	UpdateFont(ctlCheckboxLower, hFontNormal);
	UpdateFont(ctlCheckboxUpper, hFontNormal);
	UpdateFont(ctlCheckboxDigits, hFontNormal);
	UpdateFont(ctlCheckboxSpecial, hFontNormal);
	UpdateFont(ctlTextboxPassword, hFontNormal);
	UpdateFont(ctlButtonCopy, hFontNormal);
	UpdateFont(ctlButtonGenerate, hFontBold);
	UpdateFont(ctlButtonInfo, hFontNormal);	
}

//===================================================
void UpdateFont(HWND& hControl, HFONT& hFont)
{
	SendMessage(hControl, WM_SETFONT, (WPARAM)hFont, TRUE);	
}

//===================================================
void CreateFontCustom(HFONT& hFontCustom, int fnWeight, LPCTSTR lpszFace)
{
	hFontCustom = CreateFont
	(
		0, 							// int nHeight               // height of font
		0, 							// int nWidth                // average character width
		0, 							// int nEscapement           // angle of escapement
		0, 							// int nOrientation          // base-line orientation angle
		fnWeight, 					// int fnWeight              // font weight
		FALSE, 						// DWORD fdwItalic           // italic attribute option
		FALSE, 						// DWORD fdwUnderline        // underline attribute option
		FALSE, 						// DWORD fdwStrikeOut        // strikeout attribute option
		DEFAULT_CHARSET, 			// DWORD fdwCharSet          // character set identifier
		OUT_DEFAULT_PRECIS, 		// DWORD fdwOutputPrecision  // output precision
		CLIP_DEFAULT_PRECIS, 		// DWORD fdwClipPrecision    // clipping precision
		DEFAULT_QUALITY, 			// DWORD fdwQuality          // output quality
		DEFAULT_PITCH | FF_SWISS, 	// DWORD fdwPitchAndFamily   // pitch and family
		lpszFace			 		// LPCTSTR lpszFace          // typeface name
	);
}

//=============================================================================
void ShowInfo()
{
	MessageBox(NULL, STR_APP_ABOUT_TEXT, STR_APP_ABOUT, MB_OK | MB_ICONINFORMATION);	
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

					case ID_BUTTON_INFO:
						ShowInfo();
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