#include "contentController.h"
#include "mainController.h"

#include "../view/Content.h"

#include "../view/vglobal.h"

#include <CommCtrl.h>
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

HWND hWndContent = NULL;
HWND hWndTextbox = NULL;
WNDPROC oldTextBoxProc;

bool isPaintResult = false;
int resultLength = 0;
const char* expResult = "";
POINT points[NUMBER_OF_POINT];

wchar_t text[TEXT_LENGHT];
char ctext[TEXT_LENGHT];

/* TextBox's Procedure */
LRESULT CALLBACK TextBoxContentProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_RETURN:
			GetWindowText(hWndTextbox, text, TEXT_LENGHT); // Get textbox's text
			if(text[0] != _T('\0')) {
				wcstombs(ctext, text, TEXT_LENGHT); // Convert from WCHAR_T to CHAR*
				sendMainMessage(hWnd, WM_EXPRESSION_TEXT, NULL, (LPARAM)(ctext)); // Send message to MainController
			}
			break;
		}
		break;

	default:
		return CallWindowProc(oldTextBoxProc, hWnd, message, wParam, lParam);
	}

	return 0;
}



void CreateTextBox(void) {
	/* Create Textbox */
	hWndTextbox = CreateWindowEx(
		NULL,
		_T("EDIT"),
		NULL,
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
		0, 0,
		WINDOW_WIDTH, TEXTBOX_HEIGHT,
		hWndContent,
		(HMENU)IDC_TEXTBOX,
		rootInst,
		NULL
		);
	if (!hWndTextbox) { // handle errors
		MessageBox(NULL,
			_T("Failed to create TextBox"),
			_T("Failed"),
			MB_ICONERROR);
	}

	/* Subclassing Textbox */
	oldTextBoxProc = (WNDPROC)SetWindowLongPtr(hWndTextbox, GWLP_WNDPROC, (LONG_PTR)TextBoxContentProc);

	/* Select Font */
	HFONT hFont = (HFONT)CreateFont(
		TEXTBOX_FONT_HEIGHT, TEXTBOX_FONT_WIDTH,
		0, 0,
		FW_NORMAL,
		FALSE, FALSE, FALSE,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		CLEARTYPE_NATURAL_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		L"Clear Sans Light");
	/* Set TextBox's font */
	SendMessage(hWndTextbox, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

	/* Set placeholder */
	SendMessage(hWndTextbox, EM_SETCUEBANNER, FALSE, (LPARAM)L"Input expression here...");
}

void CreateContent(HWND hWnd) {
	hWndContent = CreateWindowEx(
		NULL,
		ContentClass,
		NULL,
		WS_VISIBLE | WS_CHILD,
		0, CAPTION_HEIGHT,
		WINDOW_WIDTH, CONTENT_HEIGHT,
		hWnd,
		NULL,
		rootInst,
		NULL
		);
	if (!hWndContent) { // handle errors
		MessageBox(NULL,
			_T("Failed to create Content"),
			_T("Failed"),
			MB_ICONERROR);
	}
}

void sendContentMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CREATE:
		CreateContent(hWnd);
		CreateTextBox();
		break;

	case WM_PRINT_EXPRESSION:
		expResult = (const char*)lParam;
		resultLength = (int)wParam;
		isPaintResult = true;
		RECT rect;
		GetClientRect(hWndContent, &rect);
		InvalidateRect(hWndContent, &rect, 1);
		break;

	default:
		DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
}





void RegisContent(void) { regisContent(); }
void UnregisContent(void) { unregisContent(); }