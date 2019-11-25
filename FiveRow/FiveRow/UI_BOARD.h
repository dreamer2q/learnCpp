#pragma once

#include "include.h"
#include "MAP.h"

class UI_BOARD
{
public:
	UI_BOARD(Gdiplus::Rect& rc);
	~UI_BOARD();
	void setMap(class MAP* map);

	void drawMap(HDC hdc);
	void drawChess(POSITION p,int index,Gdiplus::Graphics& graphics);
	void drawMapChess(Gdiplus::Graphics& graphics);

private:
	Gdiplus::Image* m_bkGround;
	Gdiplus::Image* m_chess[3];
	Gdiplus::Rect m_DrawRect;

	class MAP* m_map;
};

