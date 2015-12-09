#include "mainController.h"

#include "../view/vglobal.h"

#include "captionController.h"
#include "buttonController.h"
#include "statusbarController.h"
#include "historylistController.h"
#include  "contentController.h"

#include "../core/arithmeticCore.h"
#include "../core/extlib/strLib.h"

void sendMainMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CREATE:
		/* Create Caption */
		if (hWnd == GetAncestor(hWnd, GA_ROOT)) {
			sendCaptionMessage(hWnd, message, wParam, lParam);
		}
		/* Create Status Bar */
		if (hWnd == GetAncestor(hWnd, GA_ROOT)) {
			sendStatusBarMessage(hWnd, message, wParam, lParam);
		}
		/* Create History List */
		if (hWnd == GetAncestor(hWnd, GA_ROOT)) {
			sendHistoryListMessage(hWnd, message, wParam, lParam);
		}
		/* Create Content */
		if (hWnd == GetAncestor(hWnd, GA_ROOT)) {
			sendContentMessage(hWnd, message, wParam, lParam);
		}
		break;
	case WM_EXPRESSION_TEXT: {
		char* s = (char*)lParam;
		const char* result;
		Expression exp(s);



		if (exp.verify() == "OK") {
			result = exp.toString();

			/* Store points */
			int count = 0;
			for (int x = 0 - NUMBER_OF_POINT / 2; x <= NUMBER_OF_POINT / 2; x += 1) {
				points[count++] = { 300 + (x), 200 - (int)exp.at(x) };
			}

			sendContentMessage(hWnd, WM_PRINT_EXPRESSION, (WPARAM)length(result), (LPARAM)result);
		}

		break;
	}

	default:
		DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
}





void RegisterControl(void) {
	RegisCaption();
	RegisButton();
	RegisStatusBar();
	RegisHistoryList();
	RegisContent();
}