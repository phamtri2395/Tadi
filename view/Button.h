#pragma once
#include <tchar.h>
#include <windows.h>

static TCHAR ButtonClass[] = _T("Button");

/* Caption's buttons's handle */
extern HWND hWndClose;
extern HWND hWndMin;
extern HWND hWndHelp;
extern HWND hWndAbout;
extern HWND hWndSave;

bool regisButton(void);
bool unregisButton(void);