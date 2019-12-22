#pragma once

#include "PLAYER.h"

/*
玩家类，继承PLAYER类

实现玩家的操作
*/
class PERSON:public PLAYER
{
public:
	PERSON(PCWSTR imgPath, MAP* map):PLAYER(imgPath,map){};

	void play(POSITION p) override;
	//void OnLButtonDown(POSITION p) override;

private:
	//POSITION m_OnLButtonDownPosition;
};

