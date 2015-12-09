#pragma once
#include <windows.h>

extern void sendStatusBarMessage(HWND, UINT, WPARAM, LPARAM);

extern void RegisStatusBar(void);
extern void UnregisStatusBar(void);