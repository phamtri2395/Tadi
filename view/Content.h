#pragma once
#include <tchar.h>
#include <windows.h>

static TCHAR ContentClass[] = _T("Content");

extern HWND hWndContent;
extern bool isPaintResult;
extern const char* expResult;
extern int resultLength;

/* Textbox's Procedure */
extern LRESULT CALLBACK TextBoxContentProc(HWND, UINT, WPARAM, LPARAM);

/* Paint result */
void PaintResult(HWND, const char*);

bool regisContent(void);
bool unregisContent(void);