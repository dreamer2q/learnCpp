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

	void draw(HDC hdc);
	void drawMap(HDC hdc);
	void drawTipCircle(HDC hdc,POSITION p);

	void updateBoard();
	void updateInfo();
	void setPlayer(class PLAYER* p1,class PLAYER* p2);
	void setMap(class MAP* map);
private:
	void drawChess(POSITION p, int index, Gdiplus::Graphics& graphics);
	void drawMapChess(Gdiplus::Graphics& graphics);

	POSITION encodeXY(POSITION p);
	Gdiplus::Image* m_bkGround;
	Gdiplus::Image* m_chess[3];

	Gdiplus::Rect m_DrawRect;
	Gdiplus::Bitmap m_bitBuf;

	class PLAYER* m_player[2];

	int m_Sep;
	class MAP* m_map;
};

