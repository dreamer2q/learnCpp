#include "AI.h"

#include <memory.h>
#include <string.h>


int AI::searchBestPos(int* x, int* y){

	int bestX, bestY;
	int score = 0;
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
	//memset(m_map, 0, sizeof(m_map));

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

//void AI::putchess(int x, int y, int player){
//	m_map[x][y] = player;
//}

//void AI::unputchess(int x, int y){
//	m_map[x][y] = 0;
//}

//void AI::setMap(MAP* m){
//	this->map = m;
//}

int AI::getRole(){
	return m_ai;
}

AI::AI(int player, int ai, int(&map)[15][15]):m_map(map) {
	m_player = player;
	m_ai = ai;
}

int AI::evalutePos(int x, int y){
	
	int score = 0;
	m_map[x][y] = m_ai;

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
		int index = 0;
		for (int i = -4; i < 5; i++) {
			int tx = x + i * dx;
			int ty = y + i * dy;
	
			if (tx >= 0 && tx < 15 && ty >= 0 && ty < 15) {
				t[index++] = c[m_map[tx][ty]];
			}
		}
		if (index < 5) {
			continue;
		}
		for (int i = 0; i < 16; i++) {
			const char* ret = isMatched(m_evaluteMap[i].t, t);
			if (ret) {
				score += m_evaluteMap[i].score;
				break;
			}
		}
	}
	m_map[x][y] = 0;
	return score;
}

int AI::evaluteLine(char* line) {
	int score = 0;
	if (strlen(line) < 5) {
		return 0;
	}
	for (int i = 0; i < 16; i++) {
		if (isMatched(line,m_evaluteMap[i].t)){
			score += m_evaluteMap[i].score;
		}
	}
	return score;
}

int AI::evaluteBoard(int player){

	int score = 0;
	char c[3];
	c[0] = '+';
	c[player] = '0';
	c[player == m_ai?m_player:m_ai] = 'A';

	for (int i = 0; i < 15; i++) {
		char t[16] = { 0 };
		for (int j = 0; j < 15; j++) {		/* -- */
			t[j] = c[m_map[i][j]];
		}
		score += evaluteLine(t);
		memset(t, 0, sizeof(t));
		for (int j = 0; j < 15; j++) {		/* | */
			t[j] = c[m_map[j][i]];
		}
		score += evaluteLine(t);
		memset(t, 0, sizeof(t));
		for (int j = 0,x=i,y=0,index=0; j < 15; j++,x++,y++) {		/* \ */
			if (x < 15 && y < 15) {
				t[index++] = c[m_map[x][y]];
			}
		}
		score += evaluteLine(t);
		memset(t, 0, sizeof(t));
		for (int j = 0, x = 0, y = i, index = 0; j < 15; j++, x++, y++) {		/* \ */
			if (x < 15 && y < 15) {
				t[index++] = c[m_map[x][y]];
			}
		}
		if (i != 0) { //skip 
			score += evaluteLine(t);
		}
		memset(t, 0, sizeof(t));
		for (int j = 0, x = 14 - i, y = 0, index = 0; j < 15; j++, x--, y++) {		/* / */
			if (x >= 0 && x < 15 && y < 15 && y >= 0) {
				t[index++] = c[m_map[x][y]];
			}
		}
		score += evaluteLine(t);
		memset(t, 0, sizeof(t));
		for (int j = 0, x = 14, y = i, index = 0; j < 15; j++, x--, y++) {		/* / */
			if (x >= 0 && x < 15 && y < 15 && y >= 0) {
				t[index++] = c[m_map[x][y]];
			}
		}
		if (i != 0) { //skip 
			score += evaluteLine(t);
		}
	}
	return score;
}

const char* AI::isMatched(const char* searchStr, const char* subStr){
	const char* ret = NULL;
	int searchLength = strlen(searchStr);
	int subLength = strlen(subStr);
	if (searchLength < subLength) {
		ret = strstr(subStr, searchStr);
	}
	else {
		ret = strstr(searchStr, subStr);
	}
	return ret;
}

