#include "MAP.h"

void MAP::init()
{
	m_CurMoveIndex = -1;
	m_CurPlayer = NOBODY;
	memset(m_Moves, 0, sizeof(m_Moves));
	memset(m_Board, 0, sizeof(m_Board));
}

void MAP::setFirstPlayer(int player)
{
	m_FirstPlayer = player;
	m_CurPlayer = player;
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
	boardIndex(p) = NOBODY;
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
	if (m_CurPlayer == NOBODY) {
		m_CurPlayer = m_FirstPlayer;
	}
	else if (m_CurPlayer == PLAYER) {
		m_CurPlayer = COMPUTER;
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
