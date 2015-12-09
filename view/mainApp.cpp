#include "../controller/mainController.h"

#include <windows.h>
#include <tchar.h>

#include "vglobal.h"

/* Global Variables */
static TCHAR WindowClass[] = _T("win32App"); // Windows class's name
static TCHAR Title[] = _T("Tadi"); //Window's title
HINSTANCE rootInst = NULL;
HWND roothWnd = NULL;

#define COLOR_WBACKGROUND 0xFFFFFF

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);





/* WinMain */
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	/* WNDCLASSEX */
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(COLOR_WBACKGROUND));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WindowClass;
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex)) { // Register window class, if failed throw message and end program
		MessageBox(NULL,
			_T("Failed to register Window's class"),
			_T("Failed"),
			MB_ICONERROR);

		return 1;
	}

	/* Register Control's class */
	RegisterControl();

	/* Create Window and handle errors */
	HWND hWnd = CreateWindow(
		WindowClass,
		Title,
		WS_POPUP,
		GetSystemMetrics(SM_CXSCREEN) / 2 - WINDOW_WIDTH / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - WINDOW_HEIGHT / 2,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
		);
	if (!hWnd) { // throw message if can't create window
		MessageBox(NULL,
			_T("Failed to Create Window"),
			_T("Failed"),
			MB_ICONERROR);

		return 1;
	}

	rootInst = hInstance; // Store window's instance
	roothWnd = hWnd; // Store window's HWND

	sendMainMessage(hWnd, WM_CREATE, NULL, NULL);

	ShowWindow(hWnd, nCmdShow); // show & update window
	UpdateWindow(hWnd);
	SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED); // Set Window to EX_LAYERED style
	SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA); // Make Window 0% transparent



	/* Handle messages */
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}





/* Window's main Procedure */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {

	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}