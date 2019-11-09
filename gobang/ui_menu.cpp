#include "ui_menu.h"

#include <conio.h>

IMAGE* g_workingImg;

void startDraw(IMAGE* t) {
	g_workingImg = GetWorkingImage();
	SetWorkingImage(t);
}
void endDraw() {
	SetWorkingImage(g_workingImg);
}

UIMENU::UIMENU(int width, int height) {
	m_menuImg = new IMAGE(width, height);
	this->m_height = height;
	this->m_width = width;
}

UIMENU::~UIMENU() {
	delete m_menuImg;
}

void UIMENU::draw(){
	startDraw(m_menuImg);

	roundrect(10, 10, m_menuImg->getwidth() - 10, m_menuImg->getheight() - 10, 10, 10);

	IMAGE pngLogo;
	loadimage(&pngLogo, _T("PNG"), _T("M_LOGO"), 200, 200, true);
	putimage(m_menuImg->getwidth() / 2 - pngLogo.getwidth() / 2 - 20, 20, &pngLogo);

	//rectangle(260, 250, 500, 290);
	RECT t1{ 260,250,500,290 };
	drawtext(L"1.开始游戏", &t1, DT_CENTER);
	t1 = RECT{260,300,500,340};
	drawtext(L"2.关于游戏", &t1, DT_CENTER);
	t1 = RECT{ 260,350,500,390 };
	drawtext(L"3.结束游戏", &t1, DT_CENTER);

	t1 = RECT{ 260,500,500,540 };
	drawtext(L"By 梦之翼", &t1, DT_CENTER);

	endDraw();
	putimage(0, 0, m_menuImg);
}

SELECTION UIMENU::getSelection(){
	char ch;
	while (true) {
		ch = _getch();
		switch (ch) {
		case '1':
			return STARTGAME;
		case '2':
			return ABOUTGAME;
		case '0':
			return EXITGAME;
		default:
			MessageBox(GetHWnd(), L"test", L"test", MB_OK);
			break;
		}
	}
	return EXITGAME;
}
