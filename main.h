#ifndef MAIN_H
#define MAIN_H
//#############################################################################


#include <windows.h>
#include <commctrl.h>
#include <string>
#include "password.h"
#include "clipboard.h"

#include "resources.h"

#pragma comment(lib, "comctl32.lib")

//=============================================================================

#define DEFAULT_NUMBER 12

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
HWND ctlButtonInfo;

HFONT hFontNormal;
HFONT hFontBold;
HFONT hFontMono;

NS_CLIPBOARD::Clipboard clipboard;

int number = DEFAULT_NUMBER;
bool isCheckboxLower = true;
bool isCheckboxUpper = true;
bool isCheckboxDigits = true;
bool isCheckboxSpecial = true;
NS_PASSWORD::PasswordGenerator pGenerator(number, isCheckboxLower, isCheckboxUpper, isCheckboxDigits, isCheckboxSpecial);

bool isTracking = false;

//=============================================================================
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CreateControls(HWND hwnd);
void UpdateNumber();
void UpdateLabelNumber();

void CreateFontCustom(HFONT& hFont, int fnWeight, LPCTSTR lpszFace);
void UpdateFont(HWND& hControl, HFONT& hFont);
void UpdateFonts();

void UpdateTextboxPassword();

bool GetCheckboxState(HWND hwnd, int buttonID);
bool ClipboardCopy(const std::string& str);
std::string Generate(int number, bool isCheckboxLower, bool isCheckboxUpper, bool isCheckboxDigits, bool isCheckboxSpecial);
std::string GetEditText(HWND hEdit);

void ShowInfo();


//#############################################################################
#endif