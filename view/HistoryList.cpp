#include "HistoryList.h"
#include "vglobal.h"

#include "../controller/historylistController.h"

LRESULT CALLBACK HistoryListProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_LBUTTONDOWN: // Set focus
		SetFocus(hWnd);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/* Register & Unregister */
bool regisHistoryList(void) {
	WNDCLASS wc = { 0 };
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = HistoryListProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = HistoryListClass;
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(COLOR_HISTORY_LIST);

	if (!RegisterClass(&wc)) {
		MessageBox(NULL,
			_T("Failed to register History List"),
			_T("Failed"),
			MB_ICONERROR);

		return false;
	}

	return true;
}
bool unregisHistoryList(void) {
	if (!UnregisterClass(HistoryListClass, NULL)) {
		MessageBox(NULL,
			_T("Failed to unregister History List"),
			_T("Failed"),
			MB_ICONERROR);

		return false;
	}

	return true;
}