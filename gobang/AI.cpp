#include "AI.h"

#include <memory.h>
#include <string.h>


int AI::searchBestPos(int* x, int* y){

	int bestX, bestY;
	int score = -1;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (m_map[i][j]) {
				continue;
			}
			int tmpScore = evalutePos(i, j);
			if (tmpScore > score) {
				score = tmpScore;
				bestX = i;
				bestY = j;
			}
		}
	}
	*x = bestX;
	*y = bestY;
	return score;
}

void AI::init(){
	memset(m_map, 0, sizeof(m_map));

	static const char* scoreMatch[] = {
		"00000","+0000+",
		"+000++","++000+",
		"+00+0+","+0+00+",
		"0000+","+0000",
		"00+00","0+000",
		"000+0","++00++",
		"++0+0+","+0+0++",
		"+++0++","++0+++"
	};
	int scores[] = {
		50000,4320,
		720,720,
		720,720,
		720,720,
		720,720,
		720,120,
		120,120,
		20,20
	};
	for (int i = 0; i < 16; i++) {
		m_evaluteMap[i] = EvaluteMap{
			(int)strlen(scoreMatch[i]),
			scores[i],
			scoreMatch[i]
		};
	}
}

void AI::putchess(int x, int y, int player){
	m_map[x][y] = player;
}

void AI::unputchess(int x, int y){
	m_map[x][y] = 0;
}

void AI::setMap(MAP* m){
	this->map = m;
}

int AI::getAiRole(){
	return m_ai;
}

AI::AI(int player, int ai) {
	m_player = player;
	m_ai = ai;
}

int AI::evalutePos(int x, int y){
	
	int score = 0;
	m_map[x][y] = m_player;

	char c[3];
	c[0] = '+';
	c[m_ai] = '0';
	c[m_player] = 'A';

	for (int z = 0; z < 4; z++) {
		int dx, dy;
		switch(z){
		case 0:
			dx = 1;
			dy = 0;
			break;
		case 1:
			dx = 0;
			dy = 1;
			break;
		case 2:
			dx = 1;
			dy = 1;
			break;
		case 3:
			dx = -1;
			dy = 1;
			break;
		default:
			//sth went wrong...
			break;
		}
		char t[10] = { 0 };
		for (int i = -4; i < 5; i++) {
			int tx = x + i * dx;
			int ty = y + i * dy;
			int index = 0;
			if (tx >= 0 && tx < 15 && ty >= 0 && ty < 15) {
				t[index++] = c[m_map[tx][ty]];
			}
		}
		for (int i = 0; i < 16; i++) {
			const char *ret = strstr(m_evaluteMap[i].t, t);
			if (ret) {
				score += m_evaluteMap[i].score;
				break;
			}
		}
		
	}

	m_map[x][y] = 0;
	return score;
}

