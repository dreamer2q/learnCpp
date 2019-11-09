#pragma once

#include <easyx.h>

class MAP {

public:
	void init();
	void drawMap();
	void putChess(int rows,int lines);
	void unputChess(int rows, int lines);
	void putChessRect(int rows,int lines);
	void unputChessRect();
	void triggerMouseEvent(MOUSEMSG *msg);
	void triggerKeyboardEvent(char c);
	int hasWinner(); // 0 no 1 black 2 white -1 draw
	
	MAP(int x,int y,int width, int height);
	~MAP();

private:
	bool inMap(int row, int line);
	void drawChess(int x, int y);
	void clearChess(int x, int y);
	void updateImg();
	void drawMapBlackDots();
	void drawBackground();
	void drawOuterBorder();
	bool isMapFull();
	bool checkLines(int x,int y);

	int m_x, m_y;
	int m_width, m_height;
	int m_map[15][15] = { 0 }; // 1 = black 2 = white 0 = empty
	IMAGE *m_img;
	IMAGE* m_pt;
	int curPlayer = 0; // odd = black , even = white;
	int gap;
};
