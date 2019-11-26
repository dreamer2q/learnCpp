#pragma once

typedef struct {
	int firstPlayer;
	int level;
	int mode;
} SETTING;

WCHAR g_szWndClass[MAXSTR];
WCHAR g_szTitle[MAXSTR];

HINSTANCE g_hInst;
HWND g_main_hwnd;

class UI_BOARD* g_board;
class MAP* g_map;
class PLAYER* g_player;
class COMPUTER* g_computer;
int g_mode = PLAYER_AI;
int g_status = 0;
SETTING g_setting;

ATOM MyRegisterClass(HINSTANCE);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR DlgStartProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitInstance(HINSTANCE, int);
void OnPaint(HDC hdc);
void OnLButtonDown(HDC hdc, int wx, int wy);
void OnMouseOver(HDC hdc, int wx, int wy);
void checkWinner();
void showThinking();
void CALLBACK computerTimerProc(HDC hdc);
void initData();
void initNew();
void freeNew();




