
#include "UI_BOARD.h"
#include "main.h"

int APIENTRY wWinMain(HINSTANCE hInstance,HINSTANCE prevInstance,LPWSTR lpCmdLine,int nCmdShow) {

	LoadStringW(hInstance, IDS_WNDCLASS, g_szWndClass, MAXSTR);
	LoadStringW(hInstance, IDS_TITLE, g_szTitle, MAXSTR);

	Gdiplus::GdiplusStartupInput gdiInput;
	ULONG_PTR gdiToken;
	GdiplusStartup(&gdiToken, &gdiInput, NULL);//init

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
	wcex.hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_ICON_APP));
	wcex.hInstance = hInstance;
	wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_APP));
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
		g_board->updateInfo();
		SetTimer(hwnd, PLAYER_INFO_UPDATE, 100, drawInfoTimerProc);
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
		case IDM_LOADBOARD:
			startGame(SHOWCHESS, NOBODY);
			break;
		case IDM_CREATEBOARD:
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_STARTCREAT), hwnd, DlgNewCreateProc);
			break;
		case IDM_SAVEBOARD:
			saveBoardToFile();
			break;
		case IDM_LOAD_HALFBOARD:
			startGame(LOADHALF, NOBODY);
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
	case WM_PLAYER_MUSIC:  
		//电脑下棋后的执行
		playPutchessMusic();
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
	case WM_RBUTTONDOWN:
	{
		POINT pt;
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		ClientToScreen(hwnd, &pt);
		HMENU hMenu = LoadMenu(g_hInst, MAKEINTRESOURCE(IDR_POPUP_MENU));
		hMenu = GetSubMenu(hMenu, 0);
		TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hwnd, NULL);
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
	case WM_ERASEBKGND:
		//避免闪烁
		return TRUE;
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

		SetDlgItemText(hDlg, IDC_EDIT_PLAYER1, g_config.Players[PLAYER]);
		SetDlgItemText(hDlg, IDC_EDIT_PLAYER2, g_config.Players[PLAYER2]);
		SetDlgItemText(hDlg, IDC_EDIT_PLAYER_AI, g_config.Players[COMPUTER]);

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
		break;
		return TRUE;
	}
	case WM_CLOSE:
		EndDialog(hDlg, 0);
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
	{
		HWND staticHwnd = GetDlgItem(hDlg, IDC_STATIC_ABOUT);
		WCHAR strAbout[512] = { 0 };
		wsprintfW(strAbout, L"五指棋\n\n游戏引擎：\nYixin2017 Engine\n\n参与开发人员：\nJack Li\nBob\nZiskan\nBilly\n\nGithub：\ngithub.com/dreamer2q/learnCpp \n\n此程序仅用于学习与交流");
		SetWindowText(staticHwnd, strAbout);
		return TRUE;
	}
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

INT_PTR CALLBACK DlgNewCreateProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		CheckDlgButton(hDlg, IDC_R_HALFAIFIRST,TRUE);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		if (wmId == IDOK) {
			int firstPlayer = PLAYER;
			g_setting.modeCreate = PLAYER_AI;
			if (IsDlgButtonChecked(hDlg,IDC_R_HALFPLAYER)) {
				firstPlayer = PLAYER;
				g_setting.modeCreate = PLAYER_PLAYER;
			}
			else if (IsDlgButtonChecked(hDlg, IDC_R_HALFAIFIRST)) {
				firstPlayer = COMPUTER;
			}
			EndDialog(hDlg, 1);
			startGame(CREATECHESS, firstPlayer);
		}
		else if (wmId == IDCANCEL) {
			EndDialog(hDlg, 0);
		}
		break;
	}
	default:
		break;
	}
	return (INT_PTR)FALSE;
}

void initNew() {

	RECT rcClient;
	GetClientRect(g_main_hwnd, &rcClient);
	Gdiplus::Rect rc(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);
	
	getConfig();

	g_map = new MAP();//游戏的所有数据
	g_board = new UI_BOARD(rc);//处理所有画图
	g_board->setMap(g_map);

	g_player[PLAYER] = new class PERSON(TEXT("picture/player.png"),g_map);
	g_player[PLAYER2] = new class PERSON(TEXT("picture/player2.png"), g_map);
	g_player[PLAYER]->setPlayerName(g_config.Players[PLAYER]);
	g_player[PLAYER2]->setPlayerName(g_config.Players[PLAYER2]);
	g_player[PLAYER]->setPlayerInt(PLAYER);
	g_player[PLAYER2]->setPlayerInt(PLAYER2);
	g_computer = new class COMPUTER(TEXT("picture/yixin.png"), g_map);
	g_computer->setPlayerName(g_config.Players[COMPUTER]);
	g_computer->setCallback((COMPUTER_CALLBACK)computerCallback);
	g_computer->setPlayerInt(COMPUTER);
	initMusic();
}

void getConfig()
{	
	//读取配置文件,更新全局变量
	WCHAR buf[32] = { 0 };
	GetPrivateProfileString(L"Config", L"BackGroundMusic", L"true", buf, 32, g_config.ConfigFile);
	g_setting.bkMusic = !lstrcmpW(L"true", buf);
	GetPrivateProfileString(L"Config", L"BackGroundEffect", L"true", buf, 32, g_config.ConfigFile);
	g_setting.bkEffect = !lstrcmpW(L"true", buf);
	GetPrivateProfileString(L"Config", L"Level", L"2", buf, 32, g_config.ConfigFile);
	g_setting.level = _wtoi(buf);

	GetPrivateProfileString(L"INFO", L"Player1", L"玩家1", g_config.Players[PLAYER], MAXSTR, g_config.ConfigFile);
	GetPrivateProfileString(L"INFO", L"Player2", L"玩家2", g_config.Players[PLAYER2], MAXSTR, g_config.ConfigFile);
	GetPrivateProfileString(L"INFO", L"Computer", L"弈心", g_config.Players[COMPUTER], MAXSTR, g_config.ConfigFile);
}

void saveConfig()
{
	//写入配置文件
	//SETTING
	WCHAR buf[32] = { 0 };
	WritePrivateProfileString(L"Config", L"BackGroundMusic", g_setting.bkMusic ? L"true" : L"false", g_config.ConfigFile);
	WritePrivateProfileString(L"Config", L"BackGroundEffect", g_setting.bkEffect ? L"true" : L"false", g_config.ConfigFile);
	_itow_s(g_setting.level, buf, 10);
	WritePrivateProfileString(L"Config", L"Level", buf, g_config.ConfigFile);
	//INFO
	WritePrivateProfileString(L"INFO", L"Player1", g_config.Players[PLAYER], g_config.ConfigFile);
	WritePrivateProfileString(L"INFO", L"Player2", g_config.Players[PLAYER2], g_config.ConfigFile);
	WritePrivateProfileString(L"INFO", L"Computer", g_config.Players[COMPUTER], g_config.ConfigFile);
}

void freeNew()
{
	//I do not know why delete will arise an error, therefor I just comment them since when the function is called, the program is over.
	//delete g_map;
	//delete g_board;
	//delete g_player;
	delete g_computer;

	closeMusic();
	KillTimer(g_main_hwnd, PLAYER_INFO_UPDATE);
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

	GetDlgItemText(hDlg,IDC_EDIT_PLAYER1,g_config.Players[PLAYER],MAXSTR);
	GetDlgItemText(hDlg, IDC_EDIT_PLAYER2, g_config.Players[PLAYER2], MAXSTR);
	GetDlgItemText(hDlg, IDC_EDIT_PLAYER_AI, g_config.Players[COMPUTER], MAXSTR);
	g_player[PLAYER]->setPlayerName(g_config.Players[PLAYER]);
	g_player[PLAYER2]->setPlayerName(g_config.Players[PLAYER2]);
	g_computer->setPlayerName(g_config.Players[COMPUTER]);

	updateBkMusic();
	saveConfig();
}

void startGame(int mode, int firstPlayer)
{
	if (isInGame()) {
		int ret = MessageBox(g_main_hwnd, L"正在游戏中，你确定要新开局吗？", L"新开局", MB_YESNO | MB_ICONQUESTION);
		if (IDNO == ret) return;	
	}
	
	//前置处理，避免打开取消/失败的不友好
	if (mode == LOADHALF || mode == SHOWCHESS) {
		char filename[MAXSTR] = { 0 };
		if (!fileDlg(filename, true)) return;	//取消打开文件
		if (!g_map->loadBoardFromFile(filename)) {
			MessageBoxA(g_main_hwnd, "打开棋盘文件失败，请检查格式是否正确！", "error",MB_OK | MB_ICONERROR);
			return;
		}
		if (mode == SHOWCHESS && g_map->getMode() != SHOWCHESS) {
			MessageBoxA(g_main_hwnd, "请使用载入残局打开", "error", MB_OK | MB_ICONEXCLAMATION);
			return;
		}
	}
	else {
		g_map->setFirstPlayer(firstPlayer);
		g_map->setMode(mode);
	}

	//////////////////////////////////////
	g_setting.mode = mode;
	switch (mode)
	{
	case PLAYER_PLAYER:
	{
		g_map->init();
		g_player[PLAYER]->reset(15 * 60 * 1000);
		g_player[PLAYER2]->reset(15 * 60 * 1000);
		g_board->setPlayer(g_player[PLAYER], g_player[PLAYER2]);
		g_player[PLAYER]->startRecodingTime();
	}
		break;
	case PLAYER_AI:
	{
		g_map->init();
		g_computer->setLevel(g_setting.level);
		g_computer->beforeStart();
		g_computer->reset(15 * 60 * 1000);
		g_player[PLAYER]->reset(15 * 60 * 1000);
		if (firstPlayer == PLAYER) {
			g_board->setPlayer(g_player[PLAYER], g_computer);
			g_player[PLAYER]->startRecodingTime();
		}
		else {
			g_board->setPlayer(g_computer, g_player[PLAYER]);
			g_computer->playFirstStep();
		}
	}
		break;
	case SHOWCHESS:
		//what needs to be done here???
		break;
	case LOADHALF:
	{
		g_setting.mode = g_map->getMode();
		switch (g_setting.mode)
		{
		case PLAYER_PLAYER:
			g_player[PLAYER]->reset(15 * 60 * 1000);
			g_player[PLAYER2]->reset(15 * 60 * 1000);
			g_board->setPlayer(g_player[PLAYER], g_player[PLAYER2]);
			g_player[PLAYER]->startRecodingTime();
			break;
		case PLAYER_AI:
			g_player[PLAYER]->reset(15 * 60 * 1000);
			g_computer->reset(15 * 60 * 1000);
			g_computer->setLevel(g_setting.level);

			g_computer->loadHalf();

			if (g_map->getFirstPlayer() == PLAYER) {
				g_board->setPlayer(g_player[PLAYER], g_computer);
			}
			else {
				g_board->setPlayer(g_computer, g_player[PLAYER]);
			}

			if (g_map->getCurPlayer() == COMPUTER) {
				g_computer->playFirstStep();
			}
			else {
				g_player[PLAYER]->startRecodingTime();
			}
			break;
		default:
			MessageBoxA(g_main_hwnd, "文件错误", "ERROR", MB_OK | MB_ICONERROR);
			overGame();
			return;
			break;
		}

	}
		break;
	case CREATECHESS:
		g_map->init();
		break;
	}

	////////////////////////////////////////
	g_board->updateBoard();
	g_board->updateInfo();
	playBkMusic();
	refreshBoard();
}

void overGame()
{
	g_map->setMode(g_setting.mode = ENDGAME);
	stopBkMusic();
}

void takeBack()
{
	if (!isInGame()) return;
	switch (g_setting.mode)
	{
	case SHOWCHESS:
		return;
	case PLAYER_PLAYER:
	case PLAYER_AI:
	{
		if (g_map->getSumSteps() < 2) return;
		//这里回应某人要求，将该死的对话框去掉了
		//int ret = MessageBoxA(g_main_hwnd, "你想要悔棋吗？", "悔棋", MB_YESNO | MB_ICONQUESTION);
		//if (IDYES != ret) return;
		auto p = g_map->takeBack();
		auto p2 = g_map->takeBack();
		if (g_setting.mode == PLAYER_AI) {
			g_computer->takeBack(p);
			g_computer->takeBack(p2);
		}
	}
		break;
	case CREATECHESS:
		if(g_map->getSumSteps() < 1) return;
		g_map->takeBack();
		break;
	}
	g_board->updateBoard();
	refreshBoard();
}

void OnPaint(HDC hdc) {
	g_board->draw(hdc);
}

void checkWinner() {

	if (!isInGame())return;
	switch (g_setting.mode)
	{
	case CREATECHESS:
	case SHOWCHESS:
	case LOADHALF:
		return;
	}

	int status;
	if (!(status = g_map->hasWinner())) if (!(status = checkTimeout())) return;
	
	char stat[100] = { 0 };
	switch (status)
	{
	case WHITE:
	case BLACK:
			wsprintfA(stat, "%s获胜\n", status == WHITE ? "白棋" : "黑棋");
			if (g_map->getMode() == PLAYER_AI) {
				if (g_map->getCurPlayer() == PLAYER) {
					playLoseMusic();
				}
				else {
					playWinMusic();
				}
			}
			break;
	case DRAW:
			wsprintfA(stat, "平局");
			break;
	}
	overGame();
}

void CALLBACK drawInfoTimerProc(HWND hwnd, UINT message, UINT_PTR timerId, DWORD elaps)
{
	HDC hdc= GetDC(hwnd);
	g_board->updateInfo();
	g_board->drawInfo(hdc);
	ReleaseDC(g_main_hwnd, hdc);
}

void computerCallback(POSITION p) 
{
	g_map->putChess(p);
	g_board->updateBoard();
	InvalidateRgn(g_main_hwnd, NULL, TRUE);
	//playBkMusic
	SendMessage(g_main_hwnd, WM_PLAYER_MUSIC,0, 0);
	g_player[PLAYER]->startRecodingTime();
	checkWinner();
}

void OnLButtonDown(HDC hdc, int wx, int wy) {
	int x = (wx) / 40;
	int y = (wy) / 40;
	POSITION p{ x,y };

	if (showNecessaryInfo()) {
		return;
	}

	switch (g_map->getMode()) {
	case SHOWCHESS:
		procShowChess(wx, wy);
		break;
	case CREATECHESS:
		if (g_map->isEmpty(p)) g_map->putChess(p);
		break;
	case PLAYER_PLAYER:
		if (g_map->isEmpty(p)) procPlayerPlayer(p);
		break;
	case PLAYER_AI:
		if (g_map->isEmpty(p)) procPlayerComputer(p);
		break;
	default:
		MessageBoxA(g_main_hwnd, "Unkown Mode", "Error", MB_OK | MB_ICONERROR);
		break;
	}

	g_board->updateBoard();
	g_board->updateInfo();
	g_board->draw(hdc);
	checkWinner();
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
			//MessageBoxA(g_main_hwnd, "弱智AI还在计算！", "AI", MB_OK | MB_ICONINFORMATION);
		}
	}
	else {
		playPutchessMusic();
		g_player[PLAYER]->play(p);
		g_player[PLAYER]->endRecordingTime();
		g_computer->play(p);
	}
}

int checkTimeout()
{
	const int out = 15 * 60 * 1000;
	if (g_setting.mode == PLAYER_PLAYER) {
		if (g_player[PLAYER]->getLeftTime() > out) {
			return BLACK;
		}
		if (g_player[PLAYER2]->getLeftTime() > out) {
			return WHITE;
		}
	}
	else {
		if (g_player[PLAYER]->getLeftTime() > out) {
			return (::COMPUTER == g_map->getFirstPlayer() ? BLACK : WHITE);
		}
		else if (g_computer->getLeftTime() > out) {
			return (PLAYER == g_map->getFirstPlayer() ? BLACK : WHITE);
		}
	}
	return EMPTY;
}

void saveBoardToFile()
{
	if (showNecessaryInfo()) return;
	
	static bool isProcessing = false;	//防止函数重复调用的尴尬😅
	if (isProcessing) return;
	isProcessing = true;

	int saveMode = g_setting.modeCreate;
	if (g_setting.mode != CREATECHESS) {
		//int ret = MessageBoxA(g_main_hwnd, "你要保存棋谱吗？", "询问", MB_ICONINFORMATION | MB_OKCANCEL);
		//if(ret!=IDOK)	return;
		saveMode = g_setting.mode;
	}
	
	char fileName[MAXSTR] = { 0 };
	if (fileDlg(fileName, false)) {
		if (g_map->saveBoardToFile(fileName,saveMode)) {
			//MessageBoxA(g_main_hwnd, "保存成功！", "SUCCESS", MB_OK | MB_ICONINFORMATION);
		}
		else {
			MessageBoxA(g_main_hwnd, "保存失败！", "FAILURE", MB_OK | MB_ICONWARNING);
		}
	}
	else {
		//用户取消
	}
	isProcessing = false;
}

bool fileDlg(char* filename, bool isOpen)
{
	OPENFILENAMEA ofn = { 0 };
	memset(&ofn, 0, sizeof(ofn));
	//char filename[MAXSTR] = { 0 };
	ofn.lStructSize = sizeof(OPENFILENAMEA);
	ofn.hwndOwner = g_main_hwnd;
	ofn.lpstrFilter = "棋谱文件(*.ces)\0*.ces\0所有文件(*.*)\0*.*\0\0";
	ofn.nFilterIndex = 0;
	ofn.hInstance = g_hInst;
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAXSTR;
	//这里踩了一个很大的坑，不知道文件对话框会改变目录，导致Gdiplus的图片无法显示，这里加上OFN_NOCHANGEDIR修复。
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;				//文件、目录必须存在，隐藏只读选项
	ofn.lpstrDefExt = ".ces";

	if (isOpen) {
		return GetOpenFileNameA(&ofn);
	}
	else {
		return GetSaveFileNameA(&ofn);
	}
	return false;
}

void procShowChess(int x, int y)
{
	RECT prev{ 600,0,800,300 };
	RECT next{ 600,300,800,800 };
	bool ret;

	char debug[128] = { 0 };
	wsprintfA(debug, "click (%d,%d) \n", x, y);
	OutputDebugStringA(debug);

	if (isInRECT(&prev, x, y)) {
		ret = g_map->prev();
	}
	else if(isInRECT(&next,x,y)){
		ret = g_map->next();
	}
	else {
		return;
	}
	if (!ret) {
		//MessageBoxA(g_main_hwnd, "无法进行上一步/下一步查看", "失败", MB_OK | MB_ICONINFORMATION);
		return;
	}
}

bool isInRECT(PRECT prc, int x, int y)
{
	return x > prc->left && x<prc->right && y < prc->bottom && y > prc->top;
}

bool showNecessaryInfo()
{
	switch (g_setting.mode)
	{
	case NOTSTARTED:
		//MessageBoxA(g_main_hwnd, "游戏未开始", "GAME", MB_OK | MB_ICONINFORMATION);
		return true;
	case ENDGAME:
		//MessageBoxA(g_main_hwnd, "游戏结束", "GAME", MB_OK | MB_ICONINFORMATION);
		return true;
	}
	return false;
}

void OnMouseOver(HDC hdc, int wx, int wy) {
	if (!isInGame()) {
		return;
	}

	int x = (wx) / 40, y = (wy) / 40;
	POSITION p{ -1,-1 };				//-1 means erase previous rectangle
	switch (g_setting.mode)
	{
	case SHOWCHESS:
		break;
	case PLAYER_AI:
		if (g_computer->isThinking()) break;
	case PLAYER_PLAYER:
	case CREATECHESS:
		if (isInMap(x, y) && !g_map->boardIndex(x, y)) p = POSITION{ x,y };

		break;
	}
	g_board->drawTipCircle(hdc, p);
}

bool isInGame()
{
	return g_setting.mode != NOTSTARTED && g_setting.mode != ENDGAME;
}

void refreshBoard()
{
	HDC hdc = GetDC(g_main_hwnd);
	g_board->draw(hdc);
	ReleaseDC(g_main_hwnd, hdc);
	SendMessage(g_main_hwnd, WM_PAINT, 0, 0);
}
