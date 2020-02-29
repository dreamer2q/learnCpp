#pragma once

#include "include.h"
#include "MAP.h"
#include "PERSON.h"
#include "COMPUTER.h"

//画图类,类名可能导致误解。设计时没有考虑到，暂不考虑更变。
//画图类，实现游戏的所有画图操作。
class UI_BOARD
{
public:
	//共有成员函数声明
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
	//私有成员函数声明
	void drawChess(POSITION p, int index, Gdiplus::Graphics& graphics);
	void drawMapChess(Gdiplus::Graphics& graphics);
	Gdiplus::Graphics& drawTransparent(Gdiplus::Graphics& g, Gdiplus::Image* img, float alpha, int x, int y, Gdiplus::Rect& rc);
	POSITION encodeXY(POSITION p);
	
	//一下是私有成员变量定义
	Gdiplus::Image* m_bkBord;		//棋盘
	Gdiplus::Image* m_bkImg;		//背景图片
	Gdiplus::Image* m_chess[3];		//棋子
	Gdiplus::Rect m_DrawRect;		//整个绘图区域
	Gdiplus::Rect m_DrawPlayerRc;	//Player绘图区域
	Gdiplus::Bitmap m_bitBuf;		//棋盘位图缓存，与整个绘图区域一样大
	Gdiplus::Bitmap m_bitBuf2;		//Player位图缓存
	
	class PLAYER* m_player[2];		//玩家信息
	int m_Sep;						//棋盘间隔
	class MAP* m_map;				//棋盘的数据
	float m_boardAlpha;				//棋盘透明度，默认0.8
};

