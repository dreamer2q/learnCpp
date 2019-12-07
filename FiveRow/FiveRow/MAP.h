#pragma once

#include "include.h"

class MAP
{
public:
	MAP() = default;
	//~MAP();

	void init();
	void setFirstPlayer(int player);
	int getFirstPlayer();
	void setMode(int mode);
	int getMode();
	bool putChess(POSITION p);
	bool putChess(POSITION p, int player);
	POSITION takeBack();
	int getCurPlayer();
	int boardIndex(int x, int y);
	POSITION moveIndex(int index);
	int getSumSteps();
	int getTotalIndex();
	POSITION getLastPos();
	int hasWinner();

	bool isEmpty(POSITION p);
	bool next();
	bool prev();
	bool loadBoardFromFile(const char* filename);
	bool saveBoardToFile(const char* filename,int mode);

private:
	bool isInBoard(POSITION p);
	int& boardIndex(POSITION p);
	void nextPlayer();
	void addMove(POSITION p);
	bool checkPos(POSITION p);
	void updateGameStatus();
	POSITION delMove();

	POSITION m_Moves[MAPWIDTH * MAPWIDTH];
	int m_GameMode = NOTSTARTED;
	int m_CurMoveIndex = -1;
	int m_BoardTotalIndex = 0;
	int m_Board[MAPWIDTH][MAPWIDTH] = { 0 };
	int m_CurPlayer = NOBODY;
	int m_FirstPlayer = NOBODY;
	int m_GameStatus = 0;  // -1 draw 0 inGame 1 WHITE wins 2 BLACK wins
};


