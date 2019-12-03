#include "UI_BOARD.h"


UI_BOARD::UI_BOARD(Gdiplus::Rect& rc):
	m_DrawRect(rc),
	m_DrawPlayerRc(rc.Height,0,rc.Width-rc.Height,rc.Height),
	m_bitBuf(rc.Width,rc.Height),
	m_bitBuf2(rc.Width-rc.Height,rc.Height)
{
	m_bkBord = new Gdiplus::Image(TEXT("picture/board.jpg"));
	m_chess[BLACK] = new Gdiplus::Image(TEXT("picture/black_chess.png"));
	m_chess[WHITE] = new Gdiplus::Image(TEXT("picture/white_chess.png"));
	m_chess[EMPTY] = new Gdiplus::Image(TEXT("picture/tip_chess.png"));
	m_bkImg = new Gdiplus::Image(TEXT("picture/bk.png"));
	m_Sep = (m_DrawRect.Height / 535.0) * 33;
	m_boardAlpha = 0.8;
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

void UI_BOARD::setBoardTransparent(float alpha)
{
	m_boardAlpha = alpha;
}

void UI_BOARD::draw(HDC hdc)
{
	Gdiplus::Bitmap buf(m_DrawRect.Width, m_DrawRect.Height);
	Gdiplus::Graphics g(&buf);
	g.DrawImage(&m_bitBuf, 0, 0);
	g.DrawImage(&m_bitBuf2,m_DrawPlayerRc);
	Gdiplus::Graphics graphics(hdc);
	graphics.DrawImage(&buf, m_DrawRect);
}

void UI_BOARD::drawMap(HDC hdc)
{

}

//绘制棋盘
void UI_BOARD::updateBoard()
{
	Gdiplus::Graphics gbuf(&m_bitBuf);
	//清理之前的缓存，避免重复绘制
	gbuf.Clear(Gdiplus::Color::AntiqueWhite);
	//背景
	gbuf.DrawImage(m_bkImg, m_DrawRect);
	//棋盘
	Gdiplus::Rect rc(m_DrawRect);
	rc.Width = rc.Height;
	drawTransparent(gbuf, m_bkBord,m_boardAlpha,0,0,rc);		//棋盘进行透明处理
	//棋子
	drawMapChess(gbuf);
}

//绘制player信息
void UI_BOARD::updateInfo()
{
	if (!m_player[0]) {
		return;
	}

	Gdiplus::Rect rc(m_DrawRect.Height, 0, m_DrawRect.Width - m_DrawRect.Height, m_DrawRect.Height);
	Gdiplus::Bitmap bufInfo(rc.Width, rc.Height);

	Gdiplus::Rect brc(0, 0, rc.Width, rc.Height);
	Gdiplus::Graphics g(&bufInfo);
	

	Gdiplus::SolidBrush gbruTra(Gdiplus::Color(80, 0, 180, 25));
	g.FillRectangle(&gbruTra, brc);

	Gdiplus::TextureBrush playerBrush1(m_player[0]->getPlayerPortrait(), Gdiplus::WrapMode::WrapModeClamp);
	Gdiplus::TextureBrush playerBrush2(m_player[1]->getPlayerPortrait(), Gdiplus::WrapMode::WrapModeClamp);
	Gdiplus::Bitmap bmp1(128, 128);
	Gdiplus::Bitmap bmp2(128, 128);
	Gdiplus::Graphics g1(&bmp1);
	Gdiplus::Graphics g2(&bmp2);
	Gdiplus::Rect playerRect(0, 0, 128, 128);
	g1.FillEllipse(&playerBrush1, playerRect);
	g2.FillEllipse(&playerBrush2, playerRect);

	const int Y1 = 20;
	const int Y2 = Y1 + 300;
	brc = Gdiplus::Rect(30, Y1, 128, 128);
	g.DrawImage(&bmp1, brc);
	brc = Gdiplus::Rect(30, Y2, 128, 128);
	g.DrawImage(&bmp2, brc);

	Gdiplus::Font mfont(L"宋体", 16);
	Gdiplus::StringFormat mFormat;
	Gdiplus::SolidBrush mBrush(Gdiplus::Color::Black);
	mFormat.SetAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);

	LPCWSTR wName = m_player[0]->getPlayerName();
	Gdiplus::RectF rcF(30, Y1 + 128 + 10, 128, 25);
	g.DrawString(wName, lstrlenW(wName), &mfont, rcF, &mFormat, &mBrush);
	rcF = Gdiplus::RectF(30, Y2 + 138, 128, 25);
	wName = m_player[1]->getPlayerName();
	g.DrawString(wName, lstrlenW(wName), &mfont, rcF, &mFormat, &mBrush);

	WCHAR wLeftTime[128] = { 0 };
	formatTime(m_player[0]->getLeftTime(), wLeftTime);
	rcF = Gdiplus::RectF(30, Y1 + 160, 128, 25);
	g.DrawString(wLeftTime, lstrlenW(wLeftTime), &mfont, rcF, &mFormat, &mBrush);
	formatTime(m_player[1]->getLeftTime(), wLeftTime);
	rcF = Gdiplus::RectF(30, Y2 + 160, 128, 25);
	g.DrawString(wLeftTime, lstrlenW(wLeftTime), &mfont, rcF, &mFormat, &mBrush);

	const WCHAR* wStat[2] = { L"等待" ,L"思考中" };
	const WCHAR* pstat1;
	const WCHAR* pstat2;
	int mode = m_map->getMode();
	if (mode == PLAYER_PLAYER) {
		if (m_map->getCurPlayer() == PLAYER) {
			pstat1 = wStat[1];
			pstat2 = wStat[0];
		}
		else {
			pstat1 = wStat[0];
			pstat2 = wStat[1];
		}
	}
	else {
		pstat1 = wStat[m_map->getCurPlayer() == m_player[0]->getPlayerInt()];
		pstat2 = wStat[m_map->getCurPlayer() == m_player[1]->getPlayerInt()];
	}
	rcF = Gdiplus::RectF(30, Y1 + 185, 128, 25);
	g.DrawString(pstat1, lstrlenW(pstat1), &mfont, rcF, &mFormat, &mBrush);	
	rcF = Gdiplus::RectF(30, Y2 + 185, 128, 25);
	g.DrawString(pstat2, lstrlenW(pstat2), &mfont, rcF, &mFormat, &mBrush);

	Gdiplus::Graphics graphics(&m_bitBuf2);
	//graphics.Clear(0);
	graphics.Clear(Gdiplus::Color::AntiqueWhite);
	graphics.DrawImage(&m_bitBuf, 0, 0, m_DrawPlayerRc.X, m_DrawPlayerRc.Y, m_DrawPlayerRc.Width, m_DrawPlayerRc.Height, Gdiplus::Unit::UnitPixel);
	graphics.DrawImage(&bufInfo,0,0);
}

void UI_BOARD::drawInfo(HDC hdc)
{
	Gdiplus::Graphics graphics(hdc);
	graphics.DrawImage(&m_bitBuf2, m_DrawPlayerRc);
}

void UI_BOARD::drawChess(POSITION p,int index, Gdiplus::Graphics& graphics)
{

	POSITION ep = encodeXY(p);
	int step = (m_DrawRect.Height / 535.0) * 33;	//注意这里依赖图片的大小(更换图片需要修改这里参数)
	
	Gdiplus::Rect rcChess(ep.x, ep.y, step, step);
	Gdiplus::Image* img = m_chess[m_map->boardIndex(p.x, p.y)];
	graphics.DrawImage(img, rcChess);

	WCHAR num[10];
	wsprintfW(num, L"%d", index);
	Gdiplus::Font mfont(L"Arial",16);
	Gdiplus::PointF pf(ep.x+12-5*lstrlenW(num),ep.y+7);		//调试出来的参数
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

Gdiplus::Graphics& UI_BOARD::drawTransparent(Gdiplus::Graphics &g,Gdiplus::Image* img, float alpha,int x,int y,Gdiplus::Rect &rc)
{
	Gdiplus::ColorMatrix cm = {
		1,0,0,0,0,
		0,1,0,0,0,
		0,0,1,0,0,
		0,0,0,alpha,0,
		0,0,0,0,1
	};
	Gdiplus::ImageAttributes imageAttr;
	imageAttr.SetColorMatrix(&cm);
	g.DrawImage(img, rc, x,y, img->GetWidth(), img->GetHeight(), Gdiplus::UnitPixel, &imageAttr);
	return g;
}

void UI_BOARD::drawTipCircle(HDC hdc, POSITION p)
{
	static POSITION m_lastTipCirclePos = { -1,-1 };	//最后一次下棋提示框位置
	if (m_lastTipCirclePos == p) {
		return;
	}
	Gdiplus::Rect rc(0, 0, m_DrawRect.Height, m_DrawRect.Height);
	Gdiplus::Bitmap bufChess(rc.Width,rc.Height);
	Gdiplus::Graphics g(&bufChess);
	if (m_lastTipCirclePos.x >= 0) {
		g.DrawImage(&m_bitBuf,0,0,0,0,rc.Width,rc.Height,Gdiplus::Unit::UnitPixel);
	}
	if (p.x >= 0) {
		POSITION ep = encodeXY(p);
		Gdiplus::Rect rcChess(ep.x, ep.y, m_Sep, m_Sep);
		g.DrawImage(m_chess[EMPTY], rcChess);
	}
	m_lastTipCirclePos = p;
	Gdiplus::Graphics graphics(hdc);
	graphics.DrawImage(&bufChess,rc);
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


