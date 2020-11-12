#pragma once

#include "music.h"
#include <commdlg.h>

//����֮��
#define WM_PLAYER_MUSIC WM_NULL
//TIMER ID
#define PLAYER_INFO_UPDATE 10001

//ȫ�ֱ�������
WCHAR g_szWndClass[MAXSTR];
WCHAR g_szTitle[MAXSTR];

HINSTANCE g_hInst;
HWND g_main_hwnd;

class UI_BOARD* g_board;
class MAP* g_map;
class PERSON* g_player[2];
class COMPUTER* g_computer;

//��Ϸ����
SETTING g_setting{
	2,							//level
	NOTSTARTED,					//mode
	PLAYER_AI,					//modeCreate
	false,						//bkMusic
	false						//bkEffect
};								//default setting
CONFIG g_config{
	L".\\config.ini",
	{
		L"���1",
		L"���2",
		L"����"
	}
};

//��������
ATOM MyRegisterClass(HINSTANCE);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK DlgSettingProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK DlgAboutProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK DlgNewCreateProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitInstance(HINSTANCE, int);
void OnPaint(HDC hdc);
void OnLButtonDown(HDC hdc, int wx, int wy);
void OnMouseOver(HDC hdc, int wx, int wy);
void checkWinner();
void CALLBACK drawInfoTimerProc(HWND hwnd,UINT message,UINT_PTR timerId,DWORD elaps);
void computerCallback(POSITION p);

void initNew();
void getConfig();
void saveConfig();
void freeNew();
void applySetting(HWND hDlg);
void startGame(int mode,int firstPlayer);
void overGame();
void takeBack();
void procPlayerPlayer(POSITION p);
void procPlayerComputer(POSITION p);
int checkTimeout();
void saveBoardToFile();
bool fileDlg(char* filename, bool isOpen);
void procShowChess(int x, int y);
bool isInRECT(PRECT prc,int x,int y);
bool showNecessaryInfo();
bool isInGame();
void refreshBoard();

//definitions end
