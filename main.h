#ifndef MAIN_H
#define MAIN_H
//#############################################################################


#include <windows.h>
#include <commctrl.h>
#include <string>
#include "password.h"
#include "clipboard.h"

#include "resources.h"

//=============================================================================

#define DEFAULT_NUMBER 12
#define BUFFER_STR 512
#define BUFFER_NUM 30

//=============================================================================
HINSTANCE hInst;

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
bool is_checkbox_lower = true;
bool is_checkbox_upper = true;
bool is_checkbox_digits = true;
bool is_checkbox_special = true;
NS_PASSWORD::PasswordGenerator pGenerator(number, is_checkbox_lower, is_checkbox_upper, is_checkbox_digits, is_checkbox_special);

bool is_tracking = false;

//=============================================================================
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
std::string LoadStrFromResource(HINSTANCE hInstance, int str_id);
void CreateControls(HWND hwnd);
void UpdateNumber();
void UpdateLabelNumber();

void CreateFontCustom(HFONT& hFont, int fnWeight, LPCTSTR lpszFace);
void UpdateFont(HWND& hControl, HFONT& hFont);
void UpdateFonts();

void UpdateTextboxPassword();

bool GetCheckboxState(HWND hwnd, int button_id);
bool ClipboardCopy(const std::string& str);
std::string Generate(int number, bool is_checkbox_lower, bool is_checkbox_upper, bool is_checkbox_digits, bool is_checkbox_special);
std::string GetEditText(HWND hEdit);

void ShowInfo();


//#############################################################################
#endif