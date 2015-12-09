#include "buttonController.h"

#include "../view/Button.h"

#include "../view/vglobal.h"

/* Declare Caption's buttons's handle */
HWND hWndClose = NULL;
HWND hWndMin = NULL;
HWND hWndHelp = NULL;

/* Declare StatusBar's button's handle */
HWND hWndAbout = NULL;
HWND hWndSave = NULL;

void CreateButtonCaption(HWND hWnd) {
	/* Create Caption's buttons */
	hWndClose = CreateWindowEx( // Close button
		NULL,
		ButtonClass,
		NULL,
		WS_VISIBLE | WS_CHILD,
		WINDOW_WIDTH - BUTTON_WIDTH_CAPTION, 0,
		BUTTON_WIDTH_CAPTION, BUTTON_HEIGHT_CAPTION,
		hWnd,
		NULL,
		rootInst,
		NULL
		);
	if (!hWndClose) { // handle errors
		MessageBox(NULL,
			_T("Failed to create Close button"),
			_T("Failed"),
			MB_ICONERROR);
	}
	//SetWindowLong(hWndClose, GWL_EXSTYLE, GetWindowLong(hWndClose, GWL_EXSTYLE) | WS_EX_LAYERED); // Set Button's window to EX_LAYERED style
	//SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA); // Make Button's window 0% transparent

	hWndMin = CreateWindowEx( // Min button
		NULL,
		ButtonClass,
		NULL,
		WS_VISIBLE | WS_CHILD,
		WINDOW_WIDTH - BUTTON_WIDTH_CAPTION * 2, 0,
		BUTTON_WIDTH_CAPTION, BUTTON_HEIGHT_CAPTION,
		hWnd,
		NULL,
		rootInst,
		NULL
		);
	if (!hWndMin) { // handle errors
		MessageBox(NULL,
			_T("Failed to create Min button"),
			_T("Failed"),
			MB_ICONERROR);
	}

	hWndHelp = CreateWindowEx( // Help button
		NULL,
		ButtonClass,
		NULL,
		WS_VISIBLE | WS_CHILD,
		WINDOW_WIDTH - BUTTON_WIDTH_CAPTION * 3, 0,
		BUTTON_WIDTH_CAPTION, BUTTON_HEIGHT_CAPTION,
		hWnd,
		NULL,
		rootInst,
		NULL
		);
	if (!hWndHelp) { // handle errors
		MessageBox(NULL,
			_T("Failed to create Help button"),
			_T("Failed"),
			MB_ICONERROR);
	}
}

void CreateButtonStatus(HWND hWnd) {
	/* Create About's buttons */
	hWndAbout = CreateWindowEx(
		NULL,
		ButtonClass,
		NULL,
		WS_VISIBLE | WS_CHILD,
		BUTTON_STATUS_MARGIN_SIDE, (STATUS_BAR_HEIGHT - BUTTON_HEIGHT_STATUS) / 2,
		BUTTON_WIDTH_STATUS, BUTTON_HEIGHT_STATUS,
		hWnd,
		NULL,
		rootInst,
		NULL
		);
	if (!hWndAbout) { // handle errors
		MessageBox(NULL,
			_T("Failed to create About button"),
			_T("Failed"),
			MB_ICONERROR);
	}

	/* Create Save's buttons */
	hWndSave = CreateWindowEx(
		NULL,
		ButtonClass,
		NULL,
		WS_VISIBLE | WS_CHILD,
		WINDOW_WIDTH - BUTTON_WIDTH_STATUS - BUTTON_STATUS_MARGIN_SIDE, (STATUS_BAR_HEIGHT - BUTTON_HEIGHT_STATUS) / 2,
		BUTTON_WIDTH_STATUS, BUTTON_HEIGHT_STATUS,
		hWnd,
		NULL,
		rootInst,
		NULL
		);
	if (!hWndSave) { // handle errors
		MessageBox(NULL,
			_T("Failed to create Save button"),
			_T("Failed"),
			MB_ICONERROR);
	}
}



void sendButtonMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CREATE:
		if ((hWnd != roothWnd) && (wParam == (WPARAM)("CREATE_CAPTION_BUTTON"))) CreateButtonCaption(hWnd);
		if ((hWnd != roothWnd) && (wParam == (WPARAM)("CREATE_STATUS_BUTTON"))) CreateButtonStatus(hWnd);
		break;

	default:
		DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
}





void RegisButton(void) { regisButton(); }
void UnregisButton(void) { unregisButton(); }