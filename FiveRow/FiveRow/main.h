#pragma once
#include "music.h"


WCHAR g_szWndClass[MAXSTR];
WCHAR g_szTitle[MAXSTR];

HINSTANCE g_hInst;
HWND g_main_hwnd;

class UI_BOARD* g_board;
class MAP* g_map;
class PLAYER* g_player;
class COMPUTER* g_computer;
int g_status = 0;
bool g_started = false;

SETTING g_setting{
	PLAYER,
	2,
	PLAYER_PLAYER,
	true,
	true
};		//loading default setting

ATOM MyRegisterClass(HINSTANCE);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK DlgSettingProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK DlgAboutProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
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
void applySetting(HWND hDlg);
void startGame(int mode,int firstPlayer);
void endGame();
void takeBack();
void msgNotStarted();


