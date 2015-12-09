#pragma once
#include <windows.h>

extern void sendHistoryListMessage(HWND, UINT, WPARAM, LPARAM);

extern void RegisHistoryList(void);
extern void UnregisHistoryList(void);