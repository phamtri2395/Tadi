#include "StatusBar.h"
#include "vglobal.h"

#include "../controller/statusbarController.h"

LRESULT CALLBACK StatusBarProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
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
bool regisStatusBar(void) {
	WNDCLASS wc = { 0 };
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = StatusBarProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = StatusBarClass;
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(COLOR_STATUS_BAR);

	if (!RegisterClass(&wc)) {
		MessageBox(NULL,
			_T("Failed to register Status Bar"),
			_T("Failed"),
			MB_ICONERROR);

		return false;
	}

	return true;
}
bool unregisStatusBar(void) {
	if (!UnregisterClass(StatusBarClass, NULL)) {
		MessageBox(NULL,
			_T("Failed to unregister Status Bar"),
			_T("Failed"),
			MB_ICONERROR);

		return false;
	}

	return true;
}