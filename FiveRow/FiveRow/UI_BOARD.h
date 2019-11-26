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
	void draw(HDC hdc);
	void drawMap(HDC hdc);
	void updateBoard();
	void drawChess(POSITION p,int index,Gdiplus::Graphics& graphics);
	void drawMapChess(Gdiplus::Graphics& graphics);
	void drawTipCircle(HDC hdc,POSITION p);

private:
	POSITION encodeXY(POSITION p);
	Gdiplus::Image* m_bkGround;
	Gdiplus::Image* m_chess[3];

	Gdiplus::Rect m_DrawRect;
	Gdiplus::Bitmap m_bitBuf;

	int m_Sep;
	class MAP* m_map;
};

