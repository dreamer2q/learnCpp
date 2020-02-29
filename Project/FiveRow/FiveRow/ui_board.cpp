//#include "UI_BOARD.h"
#include "UI_BOARD.h"

UI_BOARD::UI_BOARD(Gdiplus::Rect& rc):
	m_DrawRect(rc),
	m_DrawPlayerRc(rc.Height,0,rc.Width-rc.Height,rc.Height),
	m_bitBuf(rc.Width,rc.Height),
	m_bitBuf2(rc.Width-rc.Height,rc.Height)
{
	WCHAR currDir[256] = { 0 };
	GetCurrentDirectory(256, currDir);
	WCHAR Files[][256] = {
		L"\\picture\\board.jpg",
		L"\\picture\\black_chess.png",
		L"\\picture\\white_chess.png",
		L"\\picture\\tip_chess.png",
		L"\\picture\\bk.png"
	};

	WstrRcatN(Files[0], 256, 5, currDir);

	if (!isFileExistN(Files[0], 256, 5)) {
		MessageBoxA(NULL, "�ļ�ȱʧ", "����", MB_OK | MB_ICONERROR);
		exit(-1);
	}

	m_bkBord = new Gdiplus::Image(Files[0]);
	m_chess[BLACK] = new Gdiplus::Image(Files[1]);
	m_chess[WHITE] = new Gdiplus::Image(Files[2]);
	m_chess[EMPTY] = new Gdiplus::Image(Files[3]);
	m_bkImg = new Gdiplus::Image(Files[4]);
	m_Sep = (m_DrawRect.Height / 535.0) * 33;
	m_boardAlpha = 0.8;

	m_player[0] = m_player[1] = NULL;
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
	//��ͼЧ��
	graphics.DrawImage(&buf, m_DrawRect);
}

void UI_BOARD::drawMap(HDC hdc)
{

}

//��������
void UI_BOARD::updateBoard()
{
	Gdiplus::Graphics gbuf(&m_bitBuf);
	//����֮ǰ�Ļ��棬�����ظ�����
	gbuf.Clear(Gdiplus::Color::AntiqueWhite);
	//����
	gbuf.DrawImage(m_bkImg, m_DrawRect);
	//����
	Gdiplus::Rect rc(m_DrawRect);
	rc.Width = rc.Height;
	drawTransparent(gbuf, m_bkBord,m_boardAlpha,0,0,rc);		//���̽���͸������
	//����
	drawMapChess(gbuf);
}

//����player��Ϣ
void UI_BOARD::updateInfo()
{
	Gdiplus::Rect globalRect(m_DrawRect.Height, 0, m_DrawRect.Width - m_DrawRect.Height, m_DrawRect.Height);
	Gdiplus::Bitmap bufInfo(globalRect.Width, globalRect.Height);

	Gdiplus::Rect infoRect(0, 0, globalRect.Width, globalRect.Height);
	Gdiplus::Graphics g(&bufInfo);
	//͸���ڲ�
	
	Gdiplus::SolidBrush transparentBrush(Gdiplus::Color(80, 0, 180, 25));
	g.FillRectangle(&transparentBrush, infoRect);

	//��ͼ�������ɸ��õ�
	Gdiplus::SolidBrush brush(Gdiplus::Color::Black);
	Gdiplus::StringFormat format;
	format.SetAlignment(Gdiplus::StringAlignmentCenter);

	//string buffer
	WCHAR info[512] = { 0 };

	auto mode = m_map->getMode();
	if (mode == NOTSTARTED) {
		static ULONGLONG startTime = GetTickCount64();
		ULONGLONG currTime = GetTickCount64();
		switch ((currTime - startTime) / 5000 % 5)
		{
		case 0:
			wsprintfW(info, L"��ӭ~\n����Miku\n����������\n\n��\n���Ҹ�����һ���淨��");
			break;
		case 1:
			wsprintfW(info, L"��������һ��������ɣ�\n\n������Ͻǡ���Ϸ��->�����֡�\nѡ����ϲ����ģʽ\n��㿪ʼ��Ϸ��~\n");
			break;
		case 2:
			wsprintfW(info, L"��ҪС����Ŷ\n�ҿ��Ǻ���������!\n\n��Ƥ~");
			break;
		case 3:
			wsprintfW(info, L"�ڡ���Ϸ���˵�����ѡ��\n��������\n��������ʹ�á�����о֡�������\n\n��������ɷ���Ŷ");
			break;
		case 4:
			wsprintfW(info, L"���ǲ��ǻ���Щ���أ�\n�͵��������\n\n���๦�ܾ����ڴ�~");
			break;
		}
		Gdiplus::Font font(L"����", 16);
		Gdiplus::RectF infoRc(0, globalRect.Height / 2 - 120, globalRect.Width, 400);
		g.DrawString(info, lstrlenW(info), &font, infoRc, &format, &brush);
	}
	else if (mode == ENDGAME) {
		Gdiplus::Font font(L"����", 20);
		wsprintfW(info, L"��Ϸ����\n\n\n\n��ʤ��");
		Gdiplus::RectF infoRc(0, globalRect.Height / 2 - 200, globalRect.Width, 200);	
		g.DrawString(info, lstrlenW(info), &font, infoRc, &format, &brush);

		int status = m_map->hasWinner();
		wsprintfW(info, L"%s", m_player[status == BLACK ? 0 : 1]->getPlayerName());
		Gdiplus::Font font2(L"����", 24);
		brush.SetColor(Gdiplus::Color::Red);
		infoRc.Y = globalRect.Height / 2;
		g.DrawString(info, lstrlenW(info), &font2, infoRc, &format, &brush);
		
		//5sec ����ʧ
		auto func = [&]()->void{
			Sleep(8000);
			if ( m_map->getMode() == ENDGAME ) {
				m_map->setMode(NOTSTARTED);
			}
		};
		std::thread th(func);
		th.detach();
	}
	else if (mode == SHOWCHESS) {
		Gdiplus::Font font(L"Arial", 16);
		WCHAR info[128] = { 0 };
		int ret = wsprintfW(info, L"%d/%d", m_map->getSumSteps(), m_map->getTotalIndex()+1);                                                              
		Gdiplus::RectF infoRc(0, globalRect.Height / 2 - 10, globalRect.Width, 20);
		
		g.DrawString(info, ret, &font, infoRc, &format, &brush);

		g.DrawString(L"��һ��", 3, &font, Gdiplus::PointF(50, 200), &brush);
		g.DrawString(L"��һ��", 3, &font, Gdiplus::PointF(50, 400), &brush);
	}
	else if (mode == CREATECHESS) {
		Gdiplus::Font font(L"����", 16);

		wsprintfW(info, L"������ˣ��\n��������󱣴�Ŷ");

		Gdiplus::RectF infoRc(0, globalRect.Height / 2 - 50, globalRect.Width, 100);
		g.DrawString(info, lstrlenW(info), &font, infoRc, &format, &brush);
	}
	else if (mode == PLAYER_AI || mode == PLAYER_PLAYER){

		if (!m_player[0])	return;
		
		//����Player��ͷ��ʹ֮���Բ��
		Gdiplus::TextureBrush playerBrush1(m_player[0]->getPlayerPortrait(), Gdiplus::WrapMode::WrapModeClamp);
		Gdiplus::TextureBrush playerBrush2(m_player[1]->getPlayerPortrait(), Gdiplus::WrapMode::WrapModeClamp);
		
		Gdiplus::Bitmap bmp1(128, 128);
		Gdiplus::Bitmap bmp2(128, 128);

		Gdiplus::Graphics g1(&bmp1);
		Gdiplus::Graphics g2(&bmp2);
		Gdiplus::Rect playerRect(0, 0, 128, 128);
		g1.FillEllipse(&playerBrush1, playerRect);
		g2.FillEllipse(&playerBrush2, playerRect);

		//�����ʼ����
		const int Y1 = 20;
		const int Y2 = Y1 + 300;
		//����ͷ��
		infoRect = Gdiplus::Rect(30, Y1, 128, 128);
		g.DrawImage(&bmp1, infoRect);
		infoRect = Gdiplus::Rect(30, Y2, 128, 128);
		g.DrawImage(&bmp2, infoRect);
		
		//��ɫ����
		Gdiplus::Font mfont(L"����", 16);
		LPCWSTR wName = m_player[0]->getPlayerName();
		Gdiplus::RectF rcF(30, Y1 + 128 + 10, 128, 25);
		g.DrawString(wName, lstrlenW(wName), &mfont, rcF, &format, &brush);
		rcF = Gdiplus::RectF(30, Y2 + 138, 128, 25);
		wName = m_player[1]->getPlayerName();
		g.DrawString(wName, lstrlenW(wName), &mfont, rcF, &format, &brush);
		//ʣ��ʱ��
		WCHAR wLeftTime[128] = { 0 };
		formatTime(m_player[0]->getLeftTime(), wLeftTime);
		rcF = Gdiplus::RectF(30, Y1 + 160, 128, 25);
		g.DrawString(wLeftTime, lstrlenW(wLeftTime), &mfont, rcF, &format, &brush);
		formatTime(m_player[1]->getLeftTime(), wLeftTime);
		rcF = Gdiplus::RectF(30, Y2 + 160, 128, 25);
		g.DrawString(wLeftTime, lstrlenW(wLeftTime), &mfont, rcF, &format, &brush);
		//״̬
		const WCHAR* wStat[] = { L"�ȴ�" ,L"˼����" };
		const WCHAR* pstat1;
		const WCHAR* pstat2;
		
		pstat1 = wStat[m_map->getCurPlayer() == m_player[0]->getPlayerInt()];
		pstat2 = wStat[m_map->getCurPlayer() == m_player[1]->getPlayerInt()];
		
		rcF = Gdiplus::RectF(30, Y1 + 185, 128, 25);
		g.DrawString(pstat1, lstrlenW(pstat1), &mfont, rcF, &format, &brush);
		rcF = Gdiplus::RectF(30, Y2 + 185, 128, 25);
		g.DrawString(pstat2, lstrlenW(pstat2), &mfont, rcF, &format, &brush);
	}

	Gdiplus::Graphics graphics(&m_bitBuf2);
	graphics.Clear(Gdiplus::Color::Black);					//ʹ��һ����͸������ɫ����������ͼƬ
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
	int step = (m_DrawRect.Height / 535.0) * 33;	//ע����������ͼƬ�Ĵ�С(����ͼƬ��Ҫ�޸��������)
	
	Gdiplus::Rect rcChess(ep.x, ep.y, step, step);
	Gdiplus::Image* img = m_chess[m_map->boardIndex(p.x, p.y)];
	graphics.DrawImage(img, rcChess);

	WCHAR num[10];
	wsprintfW(num, L"%d", index);
	Gdiplus::Font mfont(L"Arial",16);
	Gdiplus::PointF pf(ep.x+12-5*lstrlenW(num),ep.y+7);		//���Գ����Ĳ���
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
	static POSITION m_lastTipCirclePos = { -1,-1 };	//���һ��������ʾ��λ��
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


