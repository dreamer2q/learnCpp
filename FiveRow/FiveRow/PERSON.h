#pragma once

#include "PLAYER.h"

class PERSON:public PLAYER
{
public:
	PERSON(PCWSTR imgPath, MAP* map):PLAYER(imgPath,map){};

	void play(POSITION p) override;
	//void OnLButtonDown(POSITION p) override;
	int getPlayerInt() override;

private:
	//POSITION m_OnLButtonDownPosition;
};

