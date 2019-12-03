#include "MAP.h"

#include <stdio.h>

void MAP::init()
{
	m_CurMoveIndex = -1;
	m_CurPlayer = NOBODY;
	m_GameStatus = 0;
	memset(m_Moves, 0, sizeof(m_Moves));
	memset(m_Board, 0, sizeof(m_Board));
}

void MAP::setFirstPlayer(int player)
{
	m_FirstPlayer = player;
	m_CurPlayer = player;
}

int MAP::getFirstPlayer()
{
	return m_FirstPlayer;
}

void MAP::setMode(int mode)
{
	m_GameMode = mode;
	if (SHOWCHESS == mode) {
		//init for showing steps
		m_BoardTotalIndex = m_CurMoveIndex + 1;
		m_CurMoveIndex = -1;
		m_CurPlayer = m_FirstPlayer;
	}
}

int MAP::getMode()
{
	return m_GameMode;
}

bool MAP::putChess(POSITION p)
{
	return putChess(p, getCurPlayer());
}

bool MAP::putChess(POSITION p, int player)
{
	if (isEmpty(p)) {
		boardIndex(p) = (player==m_FirstPlayer?BLACK:WHITE);
		nextPlayer();
		addMove(p);
		updateGameStatus();
		return true;
	}
	return false;
}

POSITION MAP::takeBack()
{
	POSITION p = delMove();
	boardIndex(p) = EMPTY;
	nextPlayer();
	return p;
}

int MAP::getCurPlayer()
{
	return m_CurPlayer;
}

bool MAP::isInBoard(POSITION p)
{
	return p.x>=0 && p.x<MAPWIDTH && p.y>=0 && p.y<MAPWIDTH;
}

bool MAP::isEmpty(POSITION p)
{
	if (isInBoard(p)) {
		return !m_Board[p.x][p.y];
	}
	return false;
}

int& MAP::boardIndex(POSITION p)
{
	return m_Board[p.x][p.y];
}

void MAP::nextPlayer()
{
	if (m_CurPlayer == PLAYER) {
		m_CurPlayer = (m_GameMode == PLAYER_PLAYER ? PLAYER2 : COMPUTER);
	}
	else {
		m_CurPlayer = PLAYER;
	}
}

void MAP::addMove(POSITION p)
{
	m_Moves[++m_CurMoveIndex] = p;
}

bool MAP::checkPos(POSITION p)
{
	int player = boardIndex(p);
	int sum[4];
	memset(sum, 0, sizeof(sum));
	if (!player) {
		return false;
	}
	for (int i = 0; i < 5; i++) {
		if (p.x + i < MAPWIDTH) {
			sum[0] += (boardIndex(p.x + i, p.y)==player);
		}
		if (p.y + i < MAPWIDTH) {
			sum[1] += (boardIndex(p.x, p.y + i)==player);
		}
		if (p.x + i < MAPWIDTH && p.y < MAPWIDTH) {
			sum[2] += (boardIndex(p.x + i, p.y + i)==player);
		}
		if (p.x + i < MAPWIDTH && p.y - i >= 0) {
			sum[3] += (boardIndex(p.x + i, p.y - i)==player);
		}
	}
	for (int i = 0; i < 4; i++) {
		if (sum[i] == 5) {
			return true;
		}
	}
	return false;
}

void MAP::updateGameStatus()
{
	int sumSteps = getSumSteps();
	
	if (sumSteps < MAPWIDTH * MAPWIDTH) {
		m_GameStatus = 0;
		for (int i = 0; i < sumSteps; i++) {
			if (checkPos(m_Moves[i])) {
				m_GameStatus = boardIndex(m_Moves[i]);
				break;
			}
		}
	}
	else {
		m_GameStatus = -1; //draw
	}
}

POSITION MAP::delMove()
{
	return m_Moves[m_CurMoveIndex--];
}

int MAP::boardIndex(int x, int y)
{
	return m_Board[x][y];
}

POSITION MAP::moveIndex(int index)
{
	return m_Moves[index];
}

int MAP::getSumSteps()
{
	return m_CurMoveIndex + 1;
}

POSITION MAP::getLastPos()
{
	if (m_CurMoveIndex >= 0) {
		return m_Moves[m_CurMoveIndex];
	}
	return POSITION{ -1,-1 };
}

int MAP::hasWinner()
{
	return m_GameStatus;
}

bool MAP::next()
{
	if (SHOWCHESS == m_GameMode && m_CurMoveIndex < m_BoardTotalIndex) {
		m_CurMoveIndex++;
		return true;
	}
	return false;
}

bool MAP::prev()
{
	if (SHOWCHESS == m_GameMode && m_CurMoveIndex > -1) {
		m_CurMoveIndex--;
		return true;
	}
	return false;
}

bool MAP::loadBoredFromFile(const char* filename)
{
	FILE *fin;
	fin = fopen(filename, "r");
	if (!fin) {
		return false;
	}
	init();
	int firstPlayer = 0;
	if (EOF == fscanf(fin, "%d", &firstPlayer)) {
		fclose(fin);
		return false;
	}
	setFirstPlayer(firstPlayer);
	int x, y;
	while (EOF != fscanf(fin, "%d,%d", &x,&y) && !hasWinner())
	{
		putChess(POSITION{ x,y });
	}
	fclose(fin);
	return true;
}

bool MAP::saveBoredToFile(const char* filename)
{
	FILE* fout;
	fout = fopen(filename, "w");
	if (!fout) {
		return false;
	}
	if (EOF == fprintf(fout, "%d\n", getFirstPlayer())) {
		fclose(fout);
		return false;
	}
	for (int i = 0; i < getSumSteps(); i++) {
		fprintf(fout, "%d,%d\n", m_Moves[i].x, m_Moves[i].y);
	}
	fclose(fout);
	return true;
}
