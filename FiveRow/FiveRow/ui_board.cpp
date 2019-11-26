#include "UI_BOARD.h"


UI_BOARD::UI_BOARD(Gdiplus::Rect& rc):m_DrawRect(rc),m_bitBuf(rc.Width,rc.Height)
{
	m_bkGround = new Gdiplus::Image(TEXT("picture/board.jpg"));
	m_chess[BLACK] = new Gdiplus::Image(TEXT("picture/black_chess.png"));
	m_chess[WHITE] = new Gdiplus::Image(TEXT("picture/white_chess.png"));
	m_chess[EMPTY] = new Gdiplus::Image(TEXT("picture/tip_chess.png"));

	m_Sep = (m_DrawRect.Height / 535.0) * 33;
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

void UI_BOARD::draw(HDC hdc)
{
	Gdiplus::Graphics graphics(hdc);
	graphics.DrawImage(&m_bitBuf, m_DrawRect);
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

void UI_BOARD::updateBoard()
{
	Gdiplus::Graphics gbuf(&m_bitBuf);

	Gdiplus::Rect rc(m_DrawRect);
	rc.Width = rc.Height;
	gbuf.DrawImage(m_bkGround, rc);

	drawMapChess(gbuf);
}

void UI_BOARD::drawChess(POSITION p,int index, Gdiplus::Graphics& graphics)
{

	POSITION ep = encodeXY(p);
	int step = (m_DrawRect.Height / 535.0) * 33;
	
	Gdiplus::Rect rcChess(ep.x, ep.y, step, step);
	Gdiplus::Image* img = m_chess[m_map->boardIndex(p.x, p.y)];
	graphics.DrawImage(img, rcChess);

	WCHAR num[10];
	wsprintfW(num, L"%d", index);
	Gdiplus::Font mfont(L"Arial",16);
	Gdiplus::PointF pf(ep.x+12-5*lstrlenW(num),ep.y+7);
	Gdiplus::Color color;

	if (m_map->getSumSteps() == index) {
		color.SetFromCOLORREF(Gdiplus::Color::Blue);
	}else if(m_map->boardIndex(p.x, p.y) == WHITE) {
		color.SetFromCOLORREF(Gdiplus::Color::Black);
	}else {
		color.SetFromCOLORREF(Gdiplus::Color::White);
	}

	Gdiplus::SolidBrush mbrush(color);
	graphics.DrawString(num, lstrlenW(num), &mfont,pf,&mbrush);
}

void UI_BOARD::drawMapChess(Gdiplus::Graphics& graphics)
{
	int length = m_map->getSumSteps();
	for (int i = 0; i < length; i++) {
		POSITION p = m_map->moveIndex(i);
		drawChess(p,i+1, graphics);
	}
}

void UI_BOARD::drawTipCircle(HDC hdc, POSITION p)
{
	draw(hdc);
	if (p.x >= 0) {
		POSITION ep = encodeXY(p);
		Gdiplus::Rect rcChess(ep.x, ep.y, m_Sep, m_Sep);
		Gdiplus::Graphics graphics(hdc);
		graphics.DrawImage(m_chess[EMPTY], rcChess);
	}
}

POSITION UI_BOARD::encodeXY(POSITION p)
{
	int step = (m_DrawRect.Height / 535.0) * 33;
	int x = (m_DrawRect.Height / 535.0) * (20 + 35 * p.x) - step / 2;
	int y = (m_DrawRect.Height / 535.0) * (20 + 35 * p.y) - step / 2;
	return POSITION{ x,y };
}


