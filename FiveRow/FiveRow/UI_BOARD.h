#pragma once

#include "include.h"
#include "MAP.h"
#include "PERSON.h"
#include "COMPUTER.h"

class UI_BOARD
{
public:
	UI_BOARD(Gdiplus::Rect& rc);
	~UI_BOARD();
	void setMap(class MAP* map);

	void drawMap(HDC hdc);
	void drawChess(POSITION p,int index,Gdiplus::Graphics& graphics);
	void drawMapChess(Gdiplus::Graphics& graphics);
	void setTipCircle(POSITION p);
private:
	POSITION encodeXY(POSITION p);
	Gdiplus::Image* m_bkGround;
	Gdiplus::Image* m_chess[3];
	Gdiplus::Rect m_DrawRect;

	POSITION m_TipCircle;
	int m_Sep;
	class MAP* m_map;
};

