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
				int ret = ai->searchBestPos(&x, &y);

				TCHAR s[100];
				wsprintf(s, _T("Score is %d\nPos:%d,%d\n"), ret, x, y);
				MessageBox(GetHWnd(), s, _T("INFO"), MB_OK);

				map->putChess(x, y);
			}

			int winner = map->hasWinner();
			if (winner) {
				TCHAR s[100];
				wsprintf(s, _T("Winner is %s\nDo you want to restart?"), winner == 1 ? _T("BLACK") : _T("WHITE"));
				int ret = MessageBox(GetHWnd(), s, _T("WINNER"), MB_YESNO | MB_ICONQUESTION);
				if (IDYES == ret) {
					map->init();
					ai->init();
					map->drawMap();
				}
				else {
					exit(0);
				}
			}
		}
	}
	return 0;
}

void GAME::init() {
	map->init();
	ai->init();
}

GAME::GAME(int width, int height){
	m_width = width;
	m_height = height;
	initgraph(width, height);
	playerAI = 1;
	playerPerson = 2;
	map = new MAP(0, 0, height, height);
	ai = new AI(playerPerson, playerAI,map->getMap());
}

GAME::~GAME(){
	delete map;
	closegraph();
}
