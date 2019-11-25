#include "UI_BOARD.h"


UI_BOARD::UI_BOARD(Gdiplus::Rect& rc):m_DrawRect(rc)
{
	m_bkGround = new Gdiplus::Image(TEXT("picture/board.jpg"));
	m_chess[BLACK] = new Gdiplus::Image(TEXT("picture/black_chess.png"));
	m_chess[WHITE] = new Gdiplus::Image(TEXT("picture/white_chess.png"));
}

UI_BOARD::~UI_BOARD()
{
	//delete m_bkGround;
	//delete m_chess[BLACK];
	//delete m_chess[WHITE];
}

void UI_BOARD::setMap(MAP* map)
{
	m_map = map;
}

void UI_BOARD::drawMap(HDC hdc)
{
	Gdiplus::Bitmap bk(m_DrawRect.Width,m_DrawRect.Height);

	Gdiplus::Graphics gbuf(&bk);
	
	Gdiplus::Rect rc(m_DrawRect);
	rc.Width = rc.Height;
	gbuf.DrawImage(m_bkGround, rc);

	drawMapChess(gbuf);

	Gdiplus::Graphics graphics(hdc);
	graphics.DrawImage(&bk,m_DrawRect);
}

void UI_BOARD::drawChess(POSITION p, Gdiplus::Graphics& graphics)
{
	int step = (m_DrawRect.Height / 535.0) * 33;
	int x = (m_DrawRect.Height / 535.0) * (20 + 35 * p.x) - step / 2;
	int y = (m_DrawRect.Height / 535.0) * (20 + 35 * p.y) - step / 2;
	
	Gdiplus::Rect rcChess(x, y, step, step);
	Gdiplus::Image* img = m_chess[m_map->boardIndex(p.x, p.y)];
	graphics.DrawImage(img, rcChess);
}

void UI_BOARD::drawMapChess(Gdiplus::Graphics& graphics)
{
	int length = m_map->getSumSteps();
	for (int i = 0; i < length; i++) {
		POSITION p = m_map->moveIndex(i);
		drawChess(p, graphics);
	}
}
