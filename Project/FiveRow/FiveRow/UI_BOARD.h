#pragma once

#include "include.h"
#include "MAP.h"
#include "PERSON.h"
#include "COMPUTER.h"

//��ͼ��,�������ܵ�����⡣���ʱû�п��ǵ����ݲ����Ǹ��䡣
//��ͼ�࣬ʵ����Ϸ�����л�ͼ������
class UI_BOARD
{
public:
	//���г�Ա��������
	UI_BOARD(Gdiplus::Rect& rc);
	~UI_BOARD();

	void draw(HDC hdc);
	void drawMap(HDC hdc);
	void drawTipCircle(HDC hdc,POSITION p);
	void drawStart(HDC hdc);

	void updateBoard();
	void updateInfo();
	void drawInfo(HDC hdc);
	void setPlayer(class PLAYER* p1,class PLAYER* p2);
	void setMap(class MAP* map);
	void setBoardTransparent(float alpha);
private:
	//˽�г�Ա��������
	void drawChess(POSITION p, int index, Gdiplus::Graphics& graphics);
	void drawMapChess(Gdiplus::Graphics& graphics);
	Gdiplus::Graphics& drawTransparent(Gdiplus::Graphics& g, Gdiplus::Image* img, float alpha, int x, int y, Gdiplus::Rect& rc);
	POSITION encodeXY(POSITION p);
	
	//һ����˽�г�Ա��������
	Gdiplus::Image* m_bkBord;		//����
	Gdiplus::Image* m_bkImg;		//����ͼƬ
	Gdiplus::Image* m_chess[3];		//����
	Gdiplus::Rect m_DrawRect;		//������ͼ����
	Gdiplus::Rect m_DrawPlayerRc;	//Player��ͼ����
	Gdiplus::Bitmap m_bitBuf;		//����λͼ���棬��������ͼ����һ����
	Gdiplus::Bitmap m_bitBuf2;		//Playerλͼ����
	
	class PLAYER* m_player[2];		//�����Ϣ
	int m_Sep;						//���̼��
	class MAP* m_map;				//���̵�����
	float m_boardAlpha;				//����͸���ȣ�Ĭ��0.8
};

