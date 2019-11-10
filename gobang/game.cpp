#include "game.h"
#include <conio.h>


int GAME::startPersonVsPerson(){

	map->drawMap();
	while (true) {
		MOUSEMSG msg;
		char ch;
		if (_kbhit()) {
			ch = _getch();
			//todo....
		}
		if (MouseHit()) {
			msg = GetMouseMsg();
			map->triggerMouseEvent(&msg);
			int winner = map->hasWinner();
			if (winner) {
				TCHAR s[100];
				wsprintf(s, _T("Winner is %s"), winner == 1 ? _T("BLACK") : _T("WHITE"));
				MessageBox(GetHWnd(), s, _T("WINNER"), MB_OK);
				map->init();
				map->drawMap();
			}
		}
	}
	return 0;
}
int GAME::startPersonVsAI() {

	map->setAI(ai);
	map->drawMap();
	while (true) {
		MOUSEMSG msg;
		char ch;
		if (_kbhit()) {
			ch = _getch();
			//todo....
		}
		if (MouseHit()) {
			msg = GetMouseMsg();
			map->triggerMouseEvent(&msg);

			if (map->getCurPlayer() == playerAI) {
				int x, y;
				ai->searchBestPos(&x, &y);
				map->putChess(x, y);
			}

			int winner = map->hasWinner();
			if (winner) {
				TCHAR s[100];
				wsprintf(s, _T("Winner is %s"), winner == 1 ? _T("BLACK") : _T("WHITE"));
				MessageBox(GetHWnd(), s, _T("WINNER"), MB_OK);
				map->init();
				map->drawMap();
			}
		}
	}
	return 0;
}

void GAME::init() {
	map->init();
	ai->init();
	playerAI = 1;
	playerPerson = 2;
}

GAME::GAME(int width, int height){
	m_width = width;
	m_height = height;
	initgraph(width, height);
	map = new MAP(0, 0, height, height);
	ai = new AI(playerPerson, playerAI);
}

GAME::~GAME(){
	delete map;
	closegraph();
}
