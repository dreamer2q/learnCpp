

//#include "MAP.h"
#include "UI_BOARD.h"

WCHAR g_szWndClass[MAXSTR];
WCHAR g_szTitle[MAXSTR];

HINSTANCE g_hInst;

UI_BOARD* g_board;
MAP* g_map;
class PLAYER* g_players[3];
class COMPUTER* g_computer;


ATOM MyRegisterClass(HINSTANCE);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitInstance(HINSTANCE, int);
void OnPaint(HDC hdc);
void OnLButtonDown(int x, int y);
void OnMouseOver(int wx, int wy);


int APIENTRY wWinMain(HINSTANCE hInstance,HINSTANCE prevInstance,LPWSTR lpCmdLine,int nCmdShow) {

	LoadStringW(hInstance, IDS_WNDCLASS, g_szWndClass, MAXSTR);
	LoadStringW(hInstance, IDS_TITLE, g_szTitle, MAXSTR);

	Gdiplus::GdiplusStartupInput gdiInput;
	ULONG_PTR gdiToken;
	GdiplusStartup(&gdiToken, &gdiInput, NULL);

	MyRegisterClass(hInstance);
	
	if (!InitInstance(hInstance, nCmdShow)) {
		return FALSE;
	}

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	
	delete g_map;
	delete g_board;
	delete g_players[PLAYER];
	delete g_players[COMPUTER];

	Gdiplus::GdiplusShutdown(gdiToken);

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

HWND hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, g_szWndClass, g_szTitle, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
	CW_USEDEFAULT, CW_USEDEFAULT, WIN_WIDTH, WIN_HEIGHT, NULL, NULL, hInstance, NULL);

if (!hWnd) {
	MessageBox(NULL, TEXT("Create WindowEx Error"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
	return FALSE;
}

ShowWindow(hWnd, nCmdShow);
UpdateWindow(hWnd);
return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {

	case WM_CREATE:
	{
		RECT rcClient;
		GetClientRect(hwnd, &rcClient);
		Gdiplus::Rect rc(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);
		g_map = new MAP();
		g_map->setFirstPlayer(PLAYER);
		g_board = new UI_BOARD(rc);
		g_board->setMap(g_map);
<<<<<<< HEAD

=======
		g_players[PLAYER] = new class PERSON();
		g_computer = new class COMPUTER();
		//g_computer->setLevel(1);
		g_computer->beforeStart();
		
		g_players[COMPUTER] = g_computer;
>>>>>>> 97b42f3f02cb7497be02306b328dcba850995d54
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		OnPaint(hdc);

		EndPaint(hwnd, &ps);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		OnLButtonDown(x, y);
		OnMouseOver(x, y);
		HDC dc = GetDC(hwnd);
		OnPaint(dc);
		ReleaseDC(hwnd, dc);
	}
	break;
	case WM_MOUSEMOVE:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		OnMouseOver(x, y);
		HDC dc = GetDC(hwnd);
		OnPaint(dc);
		ReleaseDC(hwnd, dc);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

void OnPaint(HDC hdc) {

	g_board->drawMap(hdc);

}

void OnLButtonDown(int wx, int wy) {
	CHAR str[100];
	wsprintfA(str, "Mouse(%d,%d)\n", wx, wy);
	//OutputDebugStringA(str);

	//double factor = 800 / 535.0;
	int x = (wx - 10) / 40;
	int y = (wy - 10) / 40;

	wsprintfA(str, "Chess(%d,%d)\n", x, y);
	OutputDebugStringA(str);

	if (x >= 0 && x < MAPWIDTH && y >= 0 && y < MAPWIDTH) {
		if (!g_map->boardIndex(x, y)) {
			g_map->putChess(POSITION{ x,y });
			OutputDebugStringA("Start boardIndex");
			class PLAYER* player = g_players[g_map->getCurPlayer()];
			player->OnLButtonDown(POSITION{ x,y });
			POSITION p = player->play();
			g_map->putChess(p);
		}
	}
}

void OnMouseOver(int wx, int wy) {
	int x = (wx ) / 40;
	int y = (wy) / 40;

	POSITION p{ -1,-1 };
	if (x >= 0 && x < MAPWIDTH && y >= 0 && y < MAPWIDTH) {
		if (!g_map->boardIndex(x, y)) {
			p = POSITION{ x,y };
		}
	}
	g_board->setTipCircle(p);
}
