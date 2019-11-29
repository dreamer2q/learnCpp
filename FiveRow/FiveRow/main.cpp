
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

	//freeNew();
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

	//g_main_hwnd = hWnd;
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

		g_board->updateBoard();
		//g_board->updateInfo();
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDM_ME_FIRST:
			startGame(PLAYER_AI, PLAYER);
			break;
		case IDM_COMPUTER_FIRST:
			startGame(PLAYER_AI, COMPUTER);
			break;
		case IDM_GAYPLAY:
			startGame(PLAYER_PLAYER, PLAYER);
			break;
		case IDM_SETTING:
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DLG_SETTING), hwnd, DlgSettingProc);
			break;
		case IDM_ABOUT:
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DLG_ABOUT), hwnd, DlgAboutProc);
			break;
		case IDM_EXIT:
			PostQuitMessage(0);
			break;
		case IDM_TAKEBACK:
			takeBack();
			break;
		default:
			MessageBoxA(hwnd, "To be implemented!", "INFO", MB_OK | MB_ICONINFORMATION);
			break;
		}
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
	case WM_FLASH:  //电脑下棋后的执行
	{
		HDC hdc = GetDC(hwnd);
		playPutchessMusic();
		OnPaint(hdc);
		ReleaseDC(hwnd,hdc);
	}
	break;
	case WM_TIMER:
	{
		//int timerId = wParam;
		//if (PLAYER_INFO_UPDATE == timerId) {
		//	playerInfoUpdate();
		//}
		//HDC hdc = GetDC(hwnd);
		//computerTimerProc(hdc);
		//ReleaseDC(hwnd, hdc);
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
		OnMouseOver(hdc, x, y);
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

INT_PTR CALLBACK DlgSettingProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		CheckRadioButton(hDlg, IDC_R_LEVEL1, IDC_R_LEVEL4, IDC_R_LEVEL1 + g_setting.level-1);
		CheckDlgButton(hDlg, IDC_CK_BKMUSIC, g_setting.bkMusic);
		CheckDlgButton(hDlg, IDC_CK_EFMUSIC, g_setting.bkEffect);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		if (wmId == IDC_BT_SAVE) {
			applySetting(hDlg);
			EndDialog(hDlg, 0);
		}
		else if (wmId == IDC_BT_CANCEL) {
			EndDialog(hDlg, 0);
		}
		return TRUE;
	}
	default:
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK DlgAboutProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		if (wmId == IDOK || wmId == IDCANCEL) {
			EndDialog(hDlg, 0);
		}
	}
	default:
		break;
	}
	return FALSE;
}

void initData() {

	g_map->init();
	g_map->setFirstPlayer(g_setting.firstToPlay);
	g_map->setMode(g_setting.mode);
	g_computer->setLevel(g_setting.level);
	g_computer->beforeStart();
	
	g_player[PLAYER]->reset(15 * 60 * 1000);
	g_player[PLAYER2]->reset(15 * 60 * 1000);
	g_computer->reset(15 * 60 * 1000);

	if (g_setting.mode == PLAYER_PLAYER) {
		g_board->setPlayer(g_player[PLAYER], g_player[PLAYER2]);
		g_player[PLAYER]->startRecodingTime();
	}
	else if (g_setting.firstToPlay == PLAYER) {
		g_board->setPlayer(g_player[PLAYER], g_computer);
		g_player[PLAYER]->startRecodingTime();
	}
	else {
		g_board->setPlayer(g_computer, g_player[PLAYER]);
	}

	g_board->updateInfo();
	g_board->updateBoard();
}

void initNew() {

	RECT rcClient;
	GetClientRect(g_main_hwnd, &rcClient);
	Gdiplus::Rect rc(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);
	
	g_map = new MAP();
	g_board = new UI_BOARD(rc);
	g_board->setMap(g_map);

	g_player[PLAYER] = new class PERSON(TEXT("picture/player.png"),g_map);
	g_player[PLAYER2] = new class PERSON(TEXT("picture/player2.png"), g_map);
	g_player[PLAYER]->setPlayerName(L"玩家1");
	g_player[PLAYER2]->setPlayerName(L"玩家2");
	g_computer = new class COMPUTER(TEXT("picture/yixin.png"), g_map);
	g_computer->setPlayerName(L"弈心");
	g_computer->setCallback((COMPUTER_CALLBACK)computerCallback);

	initMusic();
}

void freeNew()
{
	delete g_map;
	delete g_board;
	delete g_player;
	delete g_computer;

	closeMusic();
}

void applySetting(HWND hDlg)
{
	char cmd[128] = { 0 };
	for (int i = 0; i < 4; i++) {
		if (IsDlgButtonChecked(hDlg, IDC_R_LEVEL1 + i)) {
			g_setting.level = i + 1;
			wsprintfA(cmd, "SetLevel => %d\n", g_setting.level);
			OutputDebugStringA(cmd);
			break;
		}
	}
	g_setting.bkMusic = IsDlgButtonChecked(hDlg, IDC_CK_BKMUSIC);
	g_setting.bkEffect = IsDlgButtonChecked(hDlg, IDC_CK_EFMUSIC);
	if (g_started) {
		updateBkMusic();
	}
}

void startGame(int mode, int firstPlayer)
{
	g_setting.firstToPlay = firstPlayer;
	g_setting.mode = mode;
	g_started = true;
	g_status = 0;
	initData();

	if (mode == PLAYER_AI && firstPlayer == COMPUTER) {
		g_computer->playFirstStep();
	}

	playBkMusic();
	drawInfoTimerProc(g_main_hwnd, WM_TIMER, PLAYER_INFO_UPDATE, 0);
	SetTimer(g_main_hwnd, PLAYER_INFO_UPDATE, 1000, drawInfoTimerProc);
}

void endGame()
{
	g_started = false;
	KillTimer(g_main_hwnd, PLAYER_INFO_UPDATE);
}

void takeBack()
{
	if (g_started) {
		if (!g_status) {
			if (g_map->getSumSteps() >= 2) {
				int ret;
				ret = MessageBoxA(g_main_hwnd, "你想要悔棋吗？", "悔棋", MB_YESNO | MB_ICONQUESTION);
				if (IDYES == ret) {
					auto p = g_map->takeBack();
					if (g_setting.mode == PLAYER_AI) {
						g_computer->takeBack(p);
					}
					p = g_map->takeBack();
					if (g_setting.mode == PLAYER_AI) {
						g_computer->takeBack(p);
					}
					g_board->updateBoard();
					SendMessage(g_main_hwnd, WM_PAINT, 0, 0);
					return;
				}
			}
		}
		MessageBoxA(g_main_hwnd, "现在不能悔棋啦~", "GAME", MB_OK | MB_ICONINFORMATION);
	}
	else {
		MessageBoxA(g_main_hwnd, "还没开始游戏，你想干嘛？","GAME", MB_OK | MB_ICONWARNING);
	}
}

void msgNotStarted()
{
	MessageBoxA(g_main_hwnd,"游戏未开始","GAME",MB_OK | MB_ICONINFORMATION);	
}

void OnPaint(HDC hdc) {
	g_board->draw(hdc);
}

void checkWinner() {
	if (!g_started) {
		return;
	}
	g_status = g_map->hasWinner();
	if (!g_status) {
		return;
	}
	char tmp[100] = { 0 };
	stopBkMusic();
	if (g_status != -1) {
		wsprintfA(tmp, "%s获胜\n", g_status == WHITE ? "白棋" : "黑棋");
		if (g_setting.mode == PLAYER_PLAYER) {
			playWinMusic();
		}else if (g_map->getCurPlayer() == PLAYER) {
			playLoseMusic();
		}
		else {
			playWinMusic();
		}
	}
	else {
		wsprintfA(tmp, "平局");
	}
	endGame();
	MessageBoxA(g_main_hwnd, tmp, "游戏结束", MB_OK | MB_ICONINFORMATION);
}

void showThinking() {
	MessageBoxA(g_main_hwnd,"弱智AI还在计算！","AI",MB_OK | MB_ICONINFORMATION);
}

void CALLBACK drawInfoTimerProc(HWND hwnd, UINT message, UINT_PTR timerId, DWORD elaps)
{
	HDC hdc= GetDC(hwnd);
	g_board->updateInfo();
	g_board->draw(hdc);
}

void computerCallback(POSITION p) 
{
	g_map->putChess(p);
	g_board->updateBoard();
	SendMessage(g_main_hwnd, WM_FLASH,0, 0);
	g_player[PLAYER]->startRecodingTime();
	checkWinner();
}

void OnLButtonDown(HDC hdc, int wx, int wy) {
	if (g_status || !g_started) {
		return;
	}
	int x = (wx) / 40;
	int y = (wy) / 40;
	//debug
	CHAR str[100];
	wsprintfA(str, "Chess(%d,%d) => %d\n", x, y, g_status);
	OutputDebugStringA(str);

	POSITION p{ x,y };
	if (isInMap(x, y) && !g_map->boardIndex(x, y)) {
		if (g_setting.mode == PLAYER_PLAYER) {
			procPlayerPlayer(p);
		}
		else {
			procPlayerComputer(p);
		}
		g_board->updateBoard();
		g_board->draw(hdc);
		checkWinner();
	}
}

void procPlayerPlayer(POSITION p) {
	playPutchessMusic();
	g_player[g_map->getCurPlayer()]->endRecordingTime();
	g_player[g_map->getCurPlayer()]->play(p);
	g_player[g_map->getCurPlayer()]->startRecodingTime();
}

void procPlayerComputer(POSITION p) {
	if (g_map->getCurPlayer() == COMPUTER) {
		if (g_computer->isThinking()) {
			showThinking();
		}
	}
	else {
		playPutchessMusic();
		g_player[PLAYER]->play(p);
		g_player[PLAYER]->endRecordingTime();
		g_computer->play(p);
	}
}

void OnMouseOver(HDC hdc,int wx, int wy) {
	if (!g_started) {
		return;
	}
	int x = (wx) / 40;
	int y = (wy) / 40;

	POSITION p{ -1,-1 };
	if (!g_status) {
		if (!g_computer->isThinking()) {
			if (isInMap(x,y)) {
				if (!g_map->boardIndex(x, y)) {
					p = POSITION{ x,y };
				}
			}
		}
	}
	g_board->drawTipCircle(hdc, p);
}

