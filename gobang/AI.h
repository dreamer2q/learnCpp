#pragma once

#include "ui_map.h"
#include "auxiliary.h"

class AI{
public:
	void init();
	void play();
	
	void setMap(class MAP *m);
	int getRole();

	AI(int player,int ai,int (&map)[15][15]);
	int evalutePos(int x, int y, int player);

private:
	
	int evaluteLine(char* line);
	int abEvalute(int depth, int alpha, int beta,int player);
	MOVE abResult;
	int evaluteBoard(int player);
	int generatePossiblePositions(POSITION* p,int player);
	const char* isMatched(const char* searchStr, const char* subStr);

	void updateScore(POSITION p);

	EvaluteMap m_evaluteMap[16] = {0};
	
	int (&m_map)[15][15];
	int m_player;
	int m_ai;
	int m_depth;

	int scoreAll[2];
	int scores[2];

	class MAP* map;
};

