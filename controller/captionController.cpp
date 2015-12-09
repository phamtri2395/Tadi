#include "captionController.h"
#include "buttonController.h"

#include "../view/Caption.h"

#include "../view/vglobal.h"

/* Declare caption's handle */
HWND hWndCaption = NULL;

void CreateCaption(HWND hWnd) {
	hWndCaption = CreateWindowEx(
		NULL,
		CaptionClass,
		NULL,
		WS_VISIBLE | WS_CHILD,
		0, 0,
		WINDOW_WIDTH, CAPTION_HEIGHT,
		hWnd,
		NULL,
		rootInst,
		NULL
		);
	if (!hWndCaption) { // handle errors
		MessageBox(NULL,
			_T("Failed to create Create Caption"),
			_T("Failed"),
			MB_ICONERROR);
	}

	/* Create Caption button */
	sendButtonMessage(hWndCaption, WM_CREATE, (WPARAM)("CREATE_CAPTION_BUTTON"), NULL);
}





void sendCaptionMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CREATE:
		CreateCaption(hWnd);
		break;

	default:
		DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
}





void RegisCaption(void) { regisCaption(); }
void UnregisCaption(void) { unregisCaption(); }