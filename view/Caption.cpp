#include "Caption.h"
#include "vglobal.h"

#include "../controller/captionController.h"

#include <tchar.h>
#include <windowsx.h>

/* Global variables */
HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, L"resource/cover.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
bool f_trackcap = false;
int x_pos = 0;
int y_pos = 0;

void PaintCaption(HWND hWnd) {
	BITMAP bitmap;
	PAINTSTRUCT ps;

	HDC hdc = BeginPaint(hWnd, &ps);

	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hBitmap);

	GetObject(hBitmap, sizeof(bitmap), &bitmap);

	BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);

	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);

	EndPaint(hWnd, &ps);

	ReleaseDC(hWnd, hdc);
}

void MoveWindow(HWND hWnd, int x, int y) {
	RECT rect;
	GetWindowRect(hWnd, &rect);
	
	SetWindowPos(hWnd, 0, rect.left + (x - x_pos), rect.top + (y - y_pos), 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW);
}





LRESULT CALLBACK CaptionProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_MOUSEMOVE:
		if (wParam == 0x0001) // If Left Mouse button is down
		{
			int x_npos = GET_X_LPARAM(lParam);
			int y_npos = GET_Y_LPARAM(lParam);

			MoveWindow(roothWnd, x_npos, y_npos);
		}
		break;
	case WM_LBUTTONDOWN: // Set focus & Track mouse
		SetFocus(hWnd);
		if (!f_trackcap) {
			f_trackcap = true;
			x_pos = GET_X_LPARAM(lParam);
			y_pos = GET_Y_LPARAM(lParam);

			SetLayeredWindowAttributes(roothWnd, 0, (255 * WINDOW_TRANSPARENT_RATIO) / 100, LWA_ALPHA); // Make window transparent
		}
		break;
	case WM_LBUTTONUP:
		if (f_trackcap) {
			f_trackcap = false;
			
			SetLayeredWindowAttributes(roothWnd, 0, 255, LWA_ALPHA); // Make window %0 transparent
		}
		break;

	case WM_PAINT:
		PaintCaption(hWnd);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}





/* Register & Unregister */
bool regisCaption(void) {
	WNDCLASS wc = { 0 };
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = CaptionProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = CaptionClass;
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(0xFFFFFF);

	if (!RegisterClass(&wc)) {
		MessageBox(NULL,
			_T("Failed to register Caption Bar"),
			_T("Failed"),
			MB_ICONERROR);

		return false;
	}

	return true;
}
bool unregisCaption(void) {
	if (!UnregisterClass(CaptionClass, NULL)) {
		MessageBox(NULL,
			_T("Failed to unregister Caption Bar"),
			_T("Failed"),
			MB_ICONERROR);

		return false;
	}

	return true;
}