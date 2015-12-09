#pragma once
#include <windows.h>

extern void sendCaptionMessage(HWND, UINT, WPARAM, LPARAM);

extern void RegisCaption(void);
extern void UnregisCaption(void);