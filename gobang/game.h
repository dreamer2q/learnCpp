#pragma once

#include "ui_map.h"
#include "AI.h"

class GAME{
public:
	void init();
	int startPersonVsPerson();
	int startPersonVsAI();
	//void startNetPk();
	GAME(int width,int height);
	~GAME();

private:
	MAP* map;
	AI *ai;
	int m_width, m_height;
	int playerAI, playerPerson;
};

