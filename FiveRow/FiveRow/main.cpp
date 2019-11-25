#include <windows.h>

#include <ObjIdl.h>
#include <gdiplus.h>

using namespace Gdiplus;
#pragma comment(lib,"Gdiplus.lib")

#include "resource.h"

#define MAXSTR 256
#define WIN_WIDTH 800
#define WIN_HEIGHT 660

WCHAR g_szWndClass[MAXSTR];
WCHAR g_szTitle[MAXSTR];

HINSTANCE g_hInst;
enum {
	EMPTY = 0,
	WHITE,BLACK
};
Image* g_bkground;
Image* g_chess[3];  // 0=>white 1=>black

ATOM MyRegisterClass(HINSTANCE);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitInstance(HINSTANCE, int);

int APIENTRY wWinMain(HINSTANCE hInstance,HINSTANCE prevInstance,LPWSTR lpCmdLine,int nCmdShow) {

	LoadStringW(hInstance, IDS_WNDCLASS, g_szWndClass, MAXSTR);
	LoadStringW(hInstance, IDS_TITLE, g_szTitle, MAXSTR);

	GdiplusStartupInput gdiInput;
	ULONG_PTR gdiToken;
	GdiplusStartup(&gdiToken, &gdiInput, NULL);
	g_bkground = new Image(TEXT("picture/board.jpg"));
	g_chess[WHITE] = new Image(TEXT("picture/white_chess.png"));
	g_chess[BLACK] = new Image(TEXT("picture/black_chess.png"));


	MyRegisterClass(hInstance);
	
	if (!InitInstance(hInstance, nCmdShow)) {
		return FALSE;
	}
	
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	GdiplusShutdown(gdiToken);
	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.cbWndExtra = 0;
	wcex.cbClsExtra = 0;
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
	wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hInstance = hInstance;
	wcex.hIconSm = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.lpfnWndProc = WndProc;
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MAIN_MENU);
	wcex.lpszClassName = g_szWndClass;
	wcex.style = CS_HREDRAW | CS_VREDRAW;

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	g_hInst = hInstance;

	HWND hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, g_szWndClass, g_szTitle, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,
		CW_USEDEFAULT, CW_USEDEFAULT, WIN_WIDTH, WIN_HEIGHT, NULL, NULL, hInstance, NULL);

	if (!hWnd) {
		MessageBox(NULL, TEXT("Create WindowEx Error"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

VOID OnPaint(HDC hdc) {

	Graphics graphics(hdc);

	//GetClientRect()

	graphics.DrawImage(g_bkground,Rect(0,0,600,600));

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {
		
	case WM_CREATE:

		break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		
		OnPaint(hdc);

		EndPaint(hwnd, &ps);
	}
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

