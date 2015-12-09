#pragma once
#include <tchar.h>
#include <windows.h>

static TCHAR StatusBarClass[] = _T("StatusBar");

extern HWND hWndStatusBar;

bool regisStatusBar(void);
bool unregisStatusBar(void);