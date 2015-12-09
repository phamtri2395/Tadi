#pragma once
#include <tchar.h>
#include <windows.h>

static TCHAR HistoryListClass[] = _T("HistoryList");

extern HWND hWndHistoryList;

bool regisHistoryList(void);
bool unregisHistoryList(void);
