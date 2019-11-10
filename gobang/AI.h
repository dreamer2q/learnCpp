#pragma once

#include "ui_map.h"

class AI{
public:
	
	int searchBestPos(int *x, int *y);

	void init();
	void putchess(int x, int y,int player);
	void unputchess(int x, int y);
	void setMap(class MAP *m);
	int getAiRole();

	AI(int player,int ai);

private:
	int evalutePos(int x, int y);
	int evaluteLine(char* line);
	int evaluteBoard(int player);
	const char* isMatched(const char* searchStr, const char* subStr);

	typedef struct TagEvaluteMap {
		int n;
		int score;
		const char* t;
	} EvaluteMap;
	EvaluteMap m_evaluteMap[16] = {0};

	int m_map[15][15];
	int m_player;
	int m_ai;

	class MAP* map;
};

