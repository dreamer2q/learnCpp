#pragma once

#include "ui_map.h"
#include "AI.h"
#include "brain.h"

class GAME{
public:
	void init();
	int startPersonVsPerson();
	int startPersonVsAI();
	void setAiPFisrt();
	void setPlayFirst();
	//void startNetPk();
	GAME(int width,int height);
	~GAME();

private:
	MAP* map;
	AI *ai;
	BRAIN* brain;
	int m_width, m_height;
	int playerAI, playerPerson;
	bool m_AiFirst = false;
};

