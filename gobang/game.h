#pragma once

#include "ui_map.h"

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
	int m_width, m_height;
};

