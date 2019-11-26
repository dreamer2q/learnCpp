
#include "UI_BOARD.h"
#include "main.h"

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

	freeNew();
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
		g_main_hwnd = hwnd;
		initNew();
		//DialogBox(hInst, MAKEINTRESOURCE(IDD_DLG_START), hwnd, );
		initData();
		
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
	case WM_TIMER:
	{
		HDC hdc = GetDC(hwnd);
		computerTimerProc(hdc);
		ReleaseDC(hwnd, hdc);
	}
		break;
	case WM_LBUTTONDOWN:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		HDC hdc = GetDC(hwnd);

		OnLButtonDown(hdc, x, y);

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

INT_PTR DlgStartProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
	}
		break;
	case WM_PAINT:
	{

	}
		break;
	default:
		break;
	}
	return (INT_PTR)FALSE;
}

void initData() {
	g_board->setMap(g_map);
	g_map->init();
	g_map->setFirstPlayer(PLAYER);
	g_computer->setLevel(1);
	g_computer->beforeStart();
	

	g_board->updateBoard();
	//g_board->draw()
}

void initNew() {

	RECT rcClient;
	GetClientRect(g_main_hwnd, &rcClient);
	Gdiplus::Rect rc(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);

	g_board = new UI_BOARD(rc);
	g_map = new MAP();
	g_player = new class PERSON();
	g_computer = new class COMPUTER();
}

void freeNew()
{
	delete g_map;
	delete g_board;
	delete g_player;
	delete g_computer;
}

void OnPaint(HDC hdc) {

	g_board->draw(hdc);

}

void checkWinner() {
	g_status = g_map->hasWinner();
	if (!g_status) {
		return;
	}
	char tmp[100] = { 0 };
	if (g_status != -1) {
		wsprintfA(tmp, "%s获胜\n", g_status == WHITE ? "白棋" : "黑棋");
	}
	else {
		wsprintfA(tmp, "平局");
	}
	MessageBoxA(g_main_hwnd, tmp, "游戏结束", MB_OK | MB_ICONINFORMATION);
}

void showThinking() {
	MessageBoxA(g_main_hwnd,"Computer还在思考！","思考",MB_OK | MB_ICONINFORMATION);
}

void CALLBACK computerTimerProc(HDC hdc)
{
	if (!g_status) {
		if (!g_computer->isThinking()) {
			if (g_map->getCurPlayer() == COMPUTER) {
				POSITION p = g_computer->getLastPos();
				g_map->putChess(p);
				g_board->updateBoard();
				g_board->draw(hdc);
				KillTimer(g_main_hwnd, COMPUTER_MAIN_TIMER);
				checkWinner();
			}
		}
	}
}

void OnLButtonDown(HDC hdc, int wx, int wy) {  //PLAYER_PLAYER

	int x = (wx) / 40;
	int y = (wy) / 40;
	//debug
	CHAR str[100];
	wsprintfA(str, "Chess(%d,%d) => %d\n", x, y,g_status);
	OutputDebugStringA(str);

	POSITION p{ x,y };
	if (g_status == 0) { //in game
		if (isInMap(x,y)) {
			if (!g_map->boardIndex(x, y)) {
				if (PLAYER_PLAYER == g_mode) {
					g_map->putChess(p);
				}
				else {
					if (g_map->getCurPlayer() == PLAYER) {
						g_map->putChess(p);
						g_computer->OnLButtonDown(p);
						SetTimer(g_main_hwnd, COMPUTER_MAIN_TIMER, 100, NULL);
					}
					else {
						if (g_computer->isThinking()) {
							showThinking();
						}
					}
				}
				g_board->updateBoard();
				g_board->draw(hdc);
			}
		}
	}
	checkWinner();
}

void OnMouseOver(HDC hdc,int wx, int wy) {
	int x = (wx) / 40;
	int y = (wy) / 40;

	POSITION p{ -1,-1 };
	if (!g_status) {
		if (!g_computer->isThinking()) {
			if (isInMap(x, y)) {
				if (!g_map->boardIndex(x, y)) {
					p = POSITION{ x,y };
				}
			}
		}
	}
	g_board->drawTipCircle(hdc, p);
}

