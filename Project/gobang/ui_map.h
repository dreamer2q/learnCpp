#pragma once

#include <easyx.h>

#include "AI.h"
#include "auxiliary.h"
#include "brain.h"

class Player {



};

class MAP {

public:
	void init();
	void drawMap();
	void putChess(int rows,int lines);
	void unputChess(int rows, int lines);
	void putChessRect(int rows,int lines);
	void unputChessRect();

	void setAI(class AI *p);
	void nextPlayer();
	int getCurPlayer();
	int getWinner();
	POSITION getLastPosition();
	void takeBack();
	int getCurIndexMove();
	int(&getMap())[15][15];

	MAP(int x,int y,int width, int height);
	~MAP();

	int getMapAt(int x, int y);
	bool inMap(int row, int line);
	void drawChess(int x, int y);
	void clearChess(int x, int y);
	void updateImg();
	void drawMapBlackDots();
	void drawBackground();
	void drawOuterBorder();
	bool isMapFull();
	bool checkLines(int x,int y);
	void updateWinner();
	int hasWinner(); // 0 no 1 black 2 white -1 draw
	RECT getRectText(int index);

private:
	POSITION movements[15 * 15];
	int m_winner;
	int m_index_move;
	int m_x, m_y;
	int m_width, m_height;
	int m_map[15][15] = { 0 }; // 1 = black 2 = white 0 = empty
	IMAGE* m_img;
	IMAGE* m_pt;

	int curPlayer = 0; // odd = black , even = white;
	int gap;

	class AI *m_ai;
};
