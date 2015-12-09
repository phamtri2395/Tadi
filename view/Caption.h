#pragma once
#include <tchar.h>
#include <windows.h>

static TCHAR CaptionClass[] = _T("Caption");
/* Caption's handle */
extern HWND hWndCaption;

bool regisCaption(void);
bool unregisCaption(void);