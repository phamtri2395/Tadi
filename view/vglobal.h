#pragma once

#include <windows.h>

/* Window's properties */
#define WINDOW_WIDTH 625
#define WINDOW_HEIGHT 600
#define WINDOW_TRANSPARENT_RATIO 60

/* Store window's parameter */
extern HINSTANCE rootInst;
extern HWND roothWnd;

/* Caption's properties */
#define CAPTION_HEIGHT 120

/* Caption's Button's properties */
#define COLOR_BKGROUND_BUTTONCAPTION RGB(40,40,47)
#define COLOR_GROW_BUTTONCAPTION 0x464646
#define BUTTON_WIDTH_CAPTION 32 
#define BUTTON_HEIGHT_CAPTION 25

/* Content's properties */
#define COLOR_CONTENT 0xFFFFFF
#define CONTENT_HEIGHT 340
#define CONTENT_FONT_HEIGHT 18
#define CONTENT_FONT_WIDTH 8

/* TextBox's properties */
#define IDC_TEXTBOX 501
#define TEXTBOX_HEIGHT 30
#define TEXTBOX_FONT_HEIGHT 24
#define TEXTBOX_FONT_WIDTH 10
#define TEXT_LENGHT 501

/* StatusBar's Button's properties */
#define COLOR_BKGROUND_BUTTONSTATUS 0x202023
#define COLOR_GROW_BUTTONSTATUS 0x464646
#define BUTTON_WIDTH_STATUS 72
#define BUTTON_HEIGHT_STATUS 30
#define BUTTON_STATUS_MARGIN_SIDE 15

/* Status bar's properties */
#define COLOR_STATUS_BAR 0x202023
#define STATUS_BAR_HEIGHT 50

/* History List's properties */
#define COLOR_HISTORY_LIST 0x262629
#define HISTORY_LIST_HEIGHT 90

/* Set of points */
#define NUMBER_OF_POINT 501
extern POINT points[NUMBER_OF_POINT];

/* Self-defined Messages */
#define WM_EXPRESSION_TEXT (WM_USER + 0x0001)
#define WM_PRINT_EXPRESSION (WM_USER + 0x0002)
#define WM_PLOT_GRAPH (WM_USER + 0x0003)