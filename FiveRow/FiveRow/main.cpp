

//#include "MAP.h"
#include "UI_BOARD.h"

WCHAR g_szWndClass[MAXSTR];
WCHAR g_szTitle[MAXSTR];

HINSTANCE g_hInst;

UI_BOARD* g_board;
MAP* g_map;
class PLAYER* g_players[3];
class COMPUTER* g_computer;
int g_mode = PLAYER_PLAYER;


ATOM MyRegisterClass(HINSTANCE);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitInstance(HINSTANCE, int);
void OnPaint(HDC hdc);
void OnLButtonDownMode1(HDC hdc, int wx, int wy); //PLAYER_PLAYER
void OnLButtonDownMode2(HDC hdc, int wx, int wy); //PLAYER_AI
//void OnLButtonDown(HDC hdc, int x, int y);
void OnMouseOver(HDC hdc, int wx, int wy);
void showWinner(int status);


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
		g_board->updateBoard();

		g_players[PLAYER] = new class PERSON();
		g_computer = new class COMPUTER();
		g_computer->setLevel(1);
		g_computer->beforeStart();
		
		g_players[COMPUTER] = g_computer;
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
		HDC hdc = GetDC(hwnd);
		if (PLAYER_PLAYER == g_mode) {
			OnLButtonDownMode1(hdc, x, y);
		}
		else {
			OnLButtonDownMode2(hdc, x, y);
		}
		ReleaseDC(hwnd, hdc);
	}
	break;
	case WM_MOUSEMOVE:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		HDC hdc = GetDC(hwnd);
		OnMouseOver(hdc,x, y);
		ReleaseDC(hwnd, hdc);
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

	g_board->draw(hdc);

}

void showWinner(int status) {
	if (!status) {
		return;
	}
	char tmp[100] = { 0 };
	if (status != -1) {
		wsprintfA(tmp, "The Winner is %s\n", status == WHITE ? "WHITE" : "BLACK");
	}
	else {
		wsprintfA(tmp, "Game Draw");
	}
	MessageBoxA(NULL, tmp, "ÎÒÊÇÉµ±Æ", MB_OK);
}

void OnLButtonDownMode1(HDC hdc, int wx, int wy) {  //PLAYER_PLAYER

	int x = (wx - 10) / 40;
	int y = (wy - 10) / 40;
	//debug
	CHAR str[100];


	int status = g_map->hasWinner();

	wsprintfA(str, "Chess(%d,%d) => %d\n", x, y,status);
	OutputDebugStringA(str);

	if (status == 0) { //in game
		if (x >= 0 && x < MAPWIDTH && y >= 0 && y < MAPWIDTH) {
			if (!g_map->boardIndex(x, y)) {
				g_map->putChess(POSITION{ x,y });
				g_board->updateBoard();
				g_board->draw(hdc);
			}
		}
	}
	status = g_map->hasWinner();
	wsprintfA(str,"            => %d\n", status);
	OutputDebugStringA(str);
	if(status) {
		showWinner(status);
	}
}
void OnLButtonDownMode2(HDC hdc, int wx, int wy) {


}
void OnMouseOver(HDC hdc,int wx, int wy) {
	int x = (wx ) / 40;
	int y = (wy) / 40;

	POSITION p{ -1,-1 };
	if (!g_map->hasWinner()) {
		if (x >= 0 && x < MAPWIDTH && y >= 0 && y < MAPWIDTH) {
			if (!g_map->boardIndex(x, y)) {
				p = POSITION{ x,y };
			}
		}
	}
	g_board->drawTipCircle(hdc, p);
}
