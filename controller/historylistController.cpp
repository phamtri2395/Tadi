#include "historylistController.h"

#include "../view/HistoryList.h"

#include "../view/vglobal.h"

HWND hWndHistoryList = NULL;

void CreateHistoryList (HWND hWnd) {
	hWndHistoryList = CreateWindowEx(
		NULL,
		HistoryListClass,
		NULL,
		WS_VISIBLE | WS_CHILD,
		0, WINDOW_HEIGHT - HISTORY_LIST_HEIGHT - STATUS_BAR_HEIGHT,
		WINDOW_WIDTH, HISTORY_LIST_HEIGHT,
		hWnd,
		NULL,
		rootInst,
		NULL
		);
	if (!hWndHistoryList) { // handle errors
		MessageBox(NULL,
			_T("Failed to create History List"),
			_T("Failed"),
			MB_ICONERROR);
	}
}

void sendHistoryListMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CREATE:
		CreateHistoryList(hWnd);
		break;

	default:
		DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
}





void RegisHistoryList(void) { regisHistoryList(); }
void UnregisHistoryList(void) { unregisHistoryList(); }