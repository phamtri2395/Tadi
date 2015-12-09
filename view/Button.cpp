#include "Button.h"
#include "vglobal.h"

#include "../controller/buttonController.h"

/* Global Variables */
bool f_trackbutt = false;
TRACKMOUSEEVENT tme;

/* Track mouse */
void TrackMouse(HWND hWnd) {
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = TME_HOVER | TME_LEAVE;
	tme.hwndTrack = hWnd;
	tme.dwHoverTime = 1;
	TrackMouseEvent(&tme);
}

void PaintButton (HWND hWnd) {
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;

	GetClientRect(hWnd, &rect);
	hdc = BeginPaint(hWnd, &ps);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkMode(hdc, TRANSPARENT);

	/* Paint different kind of button */
	if ((hWnd == hWndHelp) || (hWnd == hWndClose) || (hWnd == hWndMin)) {
		if (f_trackbutt) FillRect(hdc, &rect, CreateSolidBrush(COLOR_GROW_BUTTONCAPTION));
		else FillRect(hdc, &rect, CreateSolidBrush(COLOR_BKGROUND_BUTTONCAPTION));
	} else if ((hWnd == hWndAbout) || (hWnd == hWndSave)) {
		if (f_trackbutt) FillRect(hdc, &rect, CreateSolidBrush(COLOR_GROW_BUTTONSTATUS));
		else FillRect(hdc, &rect, CreateSolidBrush(COLOR_BKGROUND_BUTTONSTATUS));
	}



	/* Select Font */
	HFONT hFont;
	hFont = (HFONT)CreateFont(
		20, 8,
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

	/* Paint Caption button */
	if (hWnd == hWndClose)
		DrawText(hdc, L"x", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	else if (hWnd == hWndMin)
		DrawText(hdc, L"_", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	else if (hWnd == hWndHelp)
		DrawText(hdc, L"?", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);



	/* Select Font */
	hFont = (HFONT)CreateFont(
		20, 8,
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

	/* Paint StatusBar button */
	if (hWnd == hWndAbout)
		DrawText(hdc, L"About", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	else if (hWnd == hWndSave)
		DrawText(hdc, L"Save", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);



	EndPaint(hWnd, &ps);

	ReleaseDC(hWnd, hdc);
}

void RedrawButton(HWND hWnd) {
	RECT rect;
	GetClientRect(hWnd, &rect);
	InvalidateRect(hWnd, &rect, 1);
}

void DoButtonCaptionFunc(HWND hWnd) {
	if (hWnd == hWndClose)
		PostQuitMessage(0);
	else if (hWnd == hWndMin)
		ShowWindow(roothWnd, SW_SHOWMINIMIZED);
}



LRESULT CALLBACK ButtonProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_MOUSEMOVE:
		if (!f_trackbutt) TrackMouse(hWnd);
		break;
	case WM_MOUSEHOVER:
		tme.dwFlags = TME_LEAVE;
		f_trackbutt = true;
		RedrawButton(hWnd);
		break;
	case WM_MOUSELEAVE:
		tme.dwFlags = TME_HOVER | TME_LEAVE;
		f_trackbutt = false;
		RedrawButton(hWnd);
		break;

	case WM_LBUTTONDOWN: // Set focus & Do button's function
		SetFocus(hWnd);

		DoButtonCaptionFunc(hWnd);
		break;

	case WM_PAINT:
		PaintButton(hWnd);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}





/* Register & Unregister */
bool regisButton(void) {
	WNDCLASS wc = { 0 };
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = ButtonProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = ButtonClass;
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(COLOR_GROW_BUTTONCAPTION);

	if (!RegisterClass(&wc)) {
		MessageBox(NULL,
			_T("Failed to register Button"),
			_T("Failed"),
			MB_ICONERROR);

		return false;
	}

	return true;
}
bool unregisButton(void) {
	if (!UnregisterClass(ButtonClass, NULL)) {
		MessageBox(NULL,
			_T("Failed to unregister Button"),
			_T("Failed"),
			MB_ICONERROR);

		return false;
	}

	return true;
}