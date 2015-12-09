#include "statusbarController.h"
#include "buttonController.h"

#include "../view/StatusBar.h"

#include "../view/vglobal.h"

HWND hWndStatusBar = NULL;

void CreateStatusBar(HWND hWnd) {
	hWndStatusBar = CreateWindowEx(
		NULL,
		StatusBarClass,
		NULL,
		WS_VISIBLE | WS_CHILD,
		0, WINDOW_HEIGHT - STATUS_BAR_HEIGHT,
		WINDOW_WIDTH, STATUS_BAR_HEIGHT,
		hWnd,
		NULL,
		rootInst,
		NULL
		);
	if (!hWndStatusBar) { // handle errors
		MessageBox(NULL,
			_T("Failed to create Status Bar"),
			_T("Failed"),
			MB_ICONERROR);
	}

	/* Create StatusBar button */
	sendButtonMessage(hWndStatusBar, WM_CREATE, (WPARAM)("CREATE_STATUS_BUTTON"), NULL);
}

void sendStatusBarMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CREATE:
		CreateStatusBar(hWnd);
		break;

	default:
		DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
}





void RegisStatusBar(void) { regisStatusBar(); }
void UnregisStatusBar(void) { unregisStatusBar(); }