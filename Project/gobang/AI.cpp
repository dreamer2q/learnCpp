#include "AI.h"

#include <memory.h>
#include <string.h>
#include <stdio.h>

#define MAX_SCORE ( 10000000)
#define MIN_SCORE (-10000000)


void AI::play(){
	if (map->getWinner()) {
		return;
	}
	memset(&abResult, 0, sizeof(abResult));
	int ret = abEvalute(m_depth,MIN_SCORE,MAX_SCORE,m_ai);
	if (abResult.score) {
		map->putChess(abResult.p.x, abResult.p.y);
	}
	else {
		//sth went wrong...
		map->putChess(0, 0);
	}

	//TCHAR s[100];
	//wsprintf(s, L"abResult:%d\nPos( %d, %d)", abResult.score, abResult.p.x, abResult.p.y);
	//MessageBox(GetHWnd(), s, TEXT("DEBUG"), MB_OK | MB_ICONINFORMATION);
}

void AI::init(){
	//memset(m_map, 0, sizeof(m_map));
	m_depth = 4;
	memset(boardScores, 0, sizeof(boardScores));
	memset(prePosScores, 0, sizeof(prePosScores));

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

void AI::setMap(MAP* m){
	this->map = m;
}

int AI::getRole(){
	return m_ai;
}

AI::AI(int player, int ai, int(&map)[15][15]):m_map(map) {
	m_player = player;
	m_ai = ai;
}

int AI::evalutePos(int x, int y,int player){
	int score = 0;

	char c[3];
	c[0] = '+';
	c[player] = '0';
	c[player == m_player ? m_ai:m_player] = 'A';

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
				if (tx == x && ty == y) {
					t[index++] = c[player];
				}
				else {
					t[index++] = c[m_map[tx][ty]];
				}
			}
		}
		if (index < 5) {
			continue;
		}
		score += evaluteLine(t);
	}
	return score;
}

int AI::evaluteLine(char* line) {
	int score = 0;
	int length = strlen(line);
	if (length < 5) {
		return 0;
	}
	for (int i = 0; i < 16; i++) {                                                                            
		int n = m_evaluteMap[i].n;
		const char* t = m_evaluteMap[i].t;
		for (int j = 0; j < length - n;j++) {
			if (!strncmp(t, line + j, n)) {
				score += m_evaluteMap[i].score;
				j += n;
			}
		}
	}
	return score;
}

int AI::abEvalute(int depth, int alpha, int beta,int player){
	
	int score1 = evaluteBoard(player);
	int score2 = evaluteBoard(player == m_ai ? m_player : m_ai);
	
	if (score1 >= 50000) {
		return MAX_SCORE - 1000 - (m_depth - depth);
	}
	if (score2 >= 50000) {
		return MIN_SCORE + 1000 + (m_depth - depth);
	}
	
	if (depth == 0) {
		return score1 - score2;
	}

	POSITION moves[15 * 15];
	int moveLength = generatePossiblePositions(moves,player);
	for (int i = 0; i < moveLength; i++) {
		int x = moves[i].x;
		int y = moves[i].y;
		m_map[x][y] = player;
		updateScore(moves[i]);

		int val = -abEvalute(depth - 1, -beta, -alpha, player == m_ai ? m_player : m_ai);

		updateScore(moves[i]); 
		m_map[x][y] = 0;
		if (val >= beta) {
			return beta;

		}
		if (val > alpha) {
			alpha = val;
			if (depth == m_depth) {
				abResult = MOVE{ moves[i],val };
			}
		}
	}
	return alpha;
}

int AI::evaluteBoard(int player){
	int score = 0;
	if (player == m_ai) {
		score = boardScores[0];
	}
	else {
		score = boardScores[1];
	}
	return score;
}

bool isOnlyOne(POSITION *p,int index,POSITION pos) {
	for (int i = 0; i < index; i++) {
		if (p[i].x == pos.x && p[i].y == pos.y) {
			return false;
		}
	}
	return true;
}

int _cmp(const void* a, const void* b) {
	return -((MOVE*)a)->score + ((MOVE*)b)->score;
}

int AI::generatePossiblePositions(POSITION* p,int player){
	int index = 0;
	MOVE m[15 * 15];
	memset(m, 0, sizeof(m));
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (m_map[i][j]) {
				for (int z = -1; z <= 1; z++) {
					for (int k = -1; k <= 1; k++) {
						if (i + z >= 0 && i + z < 15 && j + k >= 0 && j + k < 15) {
							if (!m_map[i + z][j + k]) {
								POSITION pos{ i+z,j+k };
								if (isOnlyOne(p,index,pos)) {
									m[index].p = pos;
									//m_map[pos.x][pos.y] = player;
									m[index].score = evalutePos(pos.x, pos.y, m_ai) + evalutePos(pos.x, pos.y,m_player);
									//m_map[pos.x][pos.y] = 0;
									//m[index].score = evalutePos(pos.x, pos.y, player);
									index++;
								}
							}
						}
					}
				}
			}
		}
	}
	qsort(m, index, sizeof(MOVE), _cmp);
	for (int i = 0; i < index; i++) {
		p[i] = m[i].p;
	}
	return index;
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

void AI::updateScore(POSITION p){

	int score1 = 0;   //score for AI
	int score2 = 0;	  //score for player
	char t1[20] = { 0 };
	char t2[20] = { 0 };
	char c1[3] = { '+',m_ai == 1 ? '0' : 'A',m_ai == 1 ? 'A' : '0' };				// 1 = ai
	char c2[3] = { '+',m_player == 1 ? '0' : 'A',m_player == 1 ? 'A' : '0' };		// 2 = player

	int x = p.x, y = p.y;
	for (int i = 0; i < 15; i++) { /*  -- */
		t1[i] = c1[m_map[i][y]];
		t2[i] = c2[m_map[i][y]];
	}
	score1 += evaluteLine(t1);
	score2 += evaluteLine(t2);
	memset(t1, 0, sizeof(t1));
	memset(t2, 0, sizeof(t2));

	for (int i = 0; i < 15; i++) {  /* | */
		t1[i] = c1[m_map[x][i]];
		t2[i] = c2[m_map[x][i]];
	}
	score1 += evaluteLine(t1);
	score2 += evaluteLine(t2);
	memset(t1, 0, sizeof(t1));
	memset(t2, 0, sizeof(t2));

	for (int i = x - min(x, y), j = y - min(x, y), index = 0; i < 15 && j < 15; i++, j++, index++) {  /* \ */
		t1[index] = c1[m_map[i][j]];
		t2[index] = c2[m_map[i][j]];
	}
	score1 += evaluteLine(t1);
	score2 += evaluteLine(t2);
	memset(t1, 0, sizeof(t1));
	memset(t2, 0, sizeof(t2));

	for (int i = x + min(y, 14 - x), j = y - min(y, 14 - x), index = 0; i >= 0 && i < 15 && j >= 0 && j < 15; i--, j++, index++) { /* / */
		t1[index] = c1[m_map[i][j]];
		t2[index] = c2[m_map[i][j]];
	}
	score1 += evaluteLine(t1);
	score2 += evaluteLine(t2);
	
	boardScores[0] -= prePosScores[0];
	boardScores[1] -= prePosScores[1];
	prePosScores[0] = score1;
	prePosScores[1] = score2;
	boardScores[0] += prePosScores[0];
	boardScores[1] += prePosScores[1];

	return;
}

