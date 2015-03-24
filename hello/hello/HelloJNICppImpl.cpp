#include "HelloJNICppImpl.h"
#include <iostream>
#include <windows.h>
#include <stdio.h>

#include <stdlib.h>
#include <string>
#include <tchar.h>

using namespace std;

#define ID_FILE_OPEN			9000
#define ID_FILE_EXIT			9001
#define ID_HELP_ABOUT			9002
#define ID_GENERATE_RECURSIVE	9003
#define ID_GENERATE_HK			9004
#define ID_GENERATE_BONUS	    9005

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("win32app");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("My First Window");

HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	hInst = hInstance; // Store instance handle in our global variable

	// The parameters to CreateWindow explained:
	// szWindowClass: the name of the application
	// szTitle: the text that appears in the title bar
	// WS_OVERLAPPEDWINDOW: the type of window to create
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
	// 500, 100: initial size (width, length)
	// NULL: the parent of this window
	// NULL: this application does not have a menu bar
	// hInstance: the first parameter from WinMain
	// NULL: not used in this application
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		320, 200,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	// The parameters to ShowWindow explained:
	// hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[500] = _T("Hello, World lol!");

	COLORREF penColor = RGB(255, 0, 0);
	HPEN gPen = CreatePen(PS_SOLID, 2, penColor);

	COLORREF penColorB = RGB(0, 0, 255);
	HPEN gPenB = CreatePen(PS_SOLID, 2, penColorB);

	switch (message)
	{
	case WM_CREATE:
	{
		HMENU hMenu, hSubMenu;
		HANDLE hIcon, hIconSm;

		hMenu = CreateMenu();

		hSubMenu = CreatePopupMenu();
		AppendMenu(hSubMenu, MF_STRING, ID_FILE_OPEN, "&Open");
		AppendMenu(hSubMenu, MF_STRING, ID_FILE_EXIT, "&Exit");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");

		hSubMenu = CreatePopupMenu();
		AppendMenu(hSubMenu, MF_STRING, ID_HELP_ABOUT, "&About");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Help");

		hSubMenu = CreatePopupMenu();
		AppendMenu(hSubMenu, MF_STRING, ID_GENERATE_RECURSIVE, "&Recursive BackTrack");

		AppendMenu(hSubMenu, MF_STRING, ID_GENERATE_HK, "&Hunt and Kill");
		AppendMenu(hSubMenu, MF_STRING, ID_GENERATE_BONUS, "&Recursive Bonus");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Generate Maze");

		SetMenu(hWnd, hMenu);
		
		break;
	}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// Here your application is laid out.
		// For this introduction, we just print out "Hello, World!"
		// in the top left corner.
		TextOut(hdc,
			5, 5,
			greeting, _tcslen(greeting));
		// End application-specific layout section.

		sprintf_s(greeting, "This is green"); // Fill buff with appropriate message
		SetTextColor(hdc, RGB(0, 200, 0)); // Set the text color to blue
		TextOut(hdc, 20, 30, greeting, _tcslen(greeting));

		sprintf_s(greeting, "This is blue"); // Fill buff with appropriate message
		SetTextColor(hdc, RGB(0, 0, 200)); // Set the text color to blue
		TextOut(hdc, 20, 50, greeting, _tcslen(greeting));

		sprintf_s(greeting, "This is bright red"); // Fill buff with appropriate message
		SetTextColor(hdc, RGB(250, 45, 45)); // Set the text color to blue
		TextOut(hdc, 20, 80, greeting, _tcslen(greeting));

		SelectObject(hdc, gPen);
		Rectangle(hdc, 30, 110, 100, 150);
		Ellipse(hdc, 120, 160, 220, 260);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

void sayHello() {
	cout << "Hello World from C++!" << endl;
	WinMain(0, 0, 0, 1);
	return;
}