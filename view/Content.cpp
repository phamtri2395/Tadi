#include "Content.h"
#include "vglobal.h"

#include "../controller/contentController.h"

void PaintResult(HWND hWnd) {
	PAINTSTRUCT ps;
	HDC hdc;



	/* Paint result */
	hdc = BeginPaint(hWndContent, &ps);
	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkMode(hdc, TRANSPARENT);

	/* Select Font */
	HFONT hFont;
	hFont = (HFONT)CreateFont(
		24, 10,
		0, 0,
		FW_NORMAL,
		FALSE, FALSE, FALSE,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		CLEARTYPE_NATURAL_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		L"Clear Sans Light");
	if (hFont) {
		SelectObject(hdc, hFont);
		DeleteObject(hFont);
	}

	TextOut(hdc, 10, TEXTBOX_HEIGHT + 3, L"Result:", 7);

	/* Select Font */
	hFont = (HFONT)CreateFont(
		CONTENT_FONT_HEIGHT, CONTENT_FONT_WIDTH,
		0, 0,
		FW_NORMAL,
		FALSE, FALSE, FALSE,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		CLEARTYPE_NATURAL_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		L"Clear Sans Regular");
	if (hFont) {
		SelectObject(hdc, hFont);
		DeleteObject(hFont);
	}

	wchar_t textResult[TEXT_LENGHT];
	mbstowcs(textResult, expResult, TEXT_LENGHT);

	TextOut(hdc, 30, TEXTBOX_HEIGHT + 30, textResult, resultLength);



	/* Plot Graph */

	// Set pen's color
	HPEN hOldPen, hNewPen;
	hNewPen = CreatePen(PS_SOLID, 1, RGB(180, 0, 0));   // aqua color (mixes green and blue)
	hOldPen = (HPEN)SelectObject(hdc, hNewPen);
	// Draw the axes
	MoveToEx(hdc, 100, 200, NULL);
	LineTo(hdc, 500, 200);
	MoveToEx(hdc, 300, 100, NULL);
	LineTo(hdc, 300, 300);

	// Draw Graph
	PolyBezier(hdc, points, 400);


	EndPaint(hWndContent, &ps);
}

/* Content's Procedure */
LRESULT CALLBACK ContentProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_LBUTTONDOWN: // Set focus
		SetFocus(hWnd);
		break;

	case WM_PAINT:
		if (isPaintResult)
			PaintResult(hWnd);

		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}



/* Register & Unregister */
bool regisContent(void) {
	WNDCLASS wc = { 0 };
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = ContentProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = ContentClass;
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(COLOR_CONTENT);

	if (!RegisterClass(&wc)) {
		MessageBox(NULL,
			_T("Failed to register Content"),
			_T("Failed"),
			MB_ICONERROR);

		return false;
	}

	return true;
}
bool unregisContent(void) {
	if (!UnregisterClass(ContentClass, NULL)) {
		MessageBox(NULL,
			_T("Failed to unregister Content"),
			_T("Failed"),
			MB_ICONERROR);

		return false;
	}

	return true;
}