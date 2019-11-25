#pragma once

#include "ui_map.h"
#include "AI.h"
#include "brain.h"

class GAME {
public:
	void init();
	int startPersonVsPerson();
	int startPersonVsAI();
	void setAiPFisrt();
	void setPlayFirst();
	//void startNetPk();
	GAME(int width, int height);
	~GAME();

private:
	bool isInMapRect(int x, int y);
	void processMapRect(MOUSEMSG *msg);
	void processWinner();

	MAP* map;
	AI *ai;
	BRAIN* brain;

	int m_width, m_height;
	int m_gap;
	int playerAI, playerPerson;
	bool m_AiFirst = false;
};

