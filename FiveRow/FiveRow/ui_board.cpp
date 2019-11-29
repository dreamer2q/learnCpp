#include "UI_BOARD.h"


UI_BOARD::UI_BOARD(Gdiplus::Rect& rc):m_DrawRect(rc),m_bitBuf(rc.Width,rc.Height)
{
	m_bkGround = new Gdiplus::Image(TEXT("picture/board.jpg"));
	m_chess[BLACK] = new Gdiplus::Image(TEXT("picture/black_chess.png"));
	m_chess[WHITE] = new Gdiplus::Image(TEXT("picture/white_chess.png"));
	m_chess[EMPTY] = new Gdiplus::Image(TEXT("picture/tip_chess.png"));
	m_bkRight = new Gdiplus::Image(TEXT("picture/bk.png"));
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

}

void UI_BOARD::updateBoard()
{
	Gdiplus::Graphics gbuf(&m_bitBuf);
	//draw background
	Gdiplus::Rect rc(m_DrawRect);
	rc.Width = rc.Height;
	gbuf.DrawImage(m_bkRight, m_DrawRect);
	gbuf.DrawImage(m_bkGround, rc);
	//draw chess
	drawMapChess(gbuf);
}

void UI_BOARD::updateInfo()
{
	Gdiplus::Graphics graphics(&m_bitBuf);
	Gdiplus::Rect rc(m_DrawRect.Height,0, m_DrawRect.Width - m_DrawRect.Height,m_DrawRect.Height);

	Gdiplus::Bitmap bufInfo(rc.Width, rc.Height);
	Gdiplus::Rect brc(0,0,rc.Width,rc.Height);
	Gdiplus::Graphics g(&bufInfo);

	if (!m_player[0]) {
		
		//g.DrawImage(m_bkRight, Gdiplus::Rect(0,0,200,400));
		//graphics.DrawImage(m_bkRight, m_DrawRect);
		//return;
	}


	//g.FillRectangle(Gdiplus::SolidBrush(Gdiplus::Color::LightCyan).Clone(), brc);

	Gdiplus::Pen pen(Gdiplus::Color(255,0,0),2);
	
	int Y1 = 20;
	int Y2 = Y1 + 300;
	brc = Gdiplus::Rect(30, Y1, 128, 128);
	g.DrawRectangle(&pen,brc);
	brc = Gdiplus::Rect(30, Y2, 128, 128);
	g.DrawRectangle(&pen, brc);

	WCHAR wName[] = L"我是傻逼吗？";
	Gdiplus::Font mfont(L"楷体", 16);
	Gdiplus::RectF rcF(30, Y1+128+10, 128, 25);
	Gdiplus::StringFormat mFormat;
	Gdiplus::SolidBrush mBrush(Gdiplus::Color::Black);
	mFormat.SetAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);
	g.DrawString(wName, lstrlenW(wName), &mfont, rcF, &mFormat,&mBrush);
	rcF = Gdiplus::RectF(30, Y2+138, 128, 25);
	g.DrawString(wName, lstrlenW(wName), &mfont, rcF, &mFormat, &mBrush);

	WCHAR wLeftTime[128] = { 0 };
	formatTime(66666, wLeftTime);
	rcF = Gdiplus::RectF(30, Y1 + 160, 128, 25);
	g.DrawString(wLeftTime, lstrlenW(wLeftTime), &mfont,rcF, &mFormat, &mBrush);
	rcF = Gdiplus::RectF(30, Y2 + 160, 128, 25);
	g.DrawString(wLeftTime, lstrlenW(wName), &mfont, rcF, &mFormat, &mBrush);
	
	WCHAR wStat[128] = { 0 };
	wsprintfW(wStat, L"思考中");
	rcF = Gdiplus::RectF(30, Y1 + 185, 128, 25);
	g.DrawString(wStat, lstrlenW(wName), &mfont, rcF, &mFormat, &mBrush);	
	wsprintfW(wStat, L"等待");
	rcF = Gdiplus::RectF(30, Y2 + 185, 128, 25);
	g.DrawString(wStat, lstrlenW(wName), &mfont, rcF, &mFormat, &mBrush);



	graphics.DrawImage(&bufInfo, rc);
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
	if (p.x >= 0) {
		POSITION ep = encodeXY(p);
		Gdiplus::Rect rcChess(ep.x, ep.y, m_Sep, m_Sep);
		Gdiplus::Bitmap bufbitmap(m_DrawRect.Width, m_DrawRect.Height);
		Gdiplus::Graphics g(&bufbitmap);
		g.DrawImage(&m_bitBuf, 0, 0);
		g.DrawImage(m_chess[EMPTY], rcChess);
		Gdiplus::Graphics graphics(hdc);
		graphics.DrawImage(&bufbitmap, 0, 0);
	}
}

void UI_BOARD::drawStart(HDC hdc)
{

}

void UI_BOARD::setPlayer(class PLAYER* p1,class PLAYER* p2)
{
	m_player[0] = p1;
	m_player[1] = p2;
}

POSITION UI_BOARD::encodeXY(POSITION p)
{
	int step = (m_DrawRect.Height / 535.0) * 33;
	int x = (m_DrawRect.Height / 535.0) * (20 + 35 * p.x) - step / 2;
	int y = (m_DrawRect.Height / 535.0) * (20 + 35 * p.y) - step / 2;
	return POSITION{ x,y };
}


