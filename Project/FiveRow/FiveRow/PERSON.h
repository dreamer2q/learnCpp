#pragma once

#include "PLAYER.h"

/*
����࣬�̳�PLAYER��

ʵ����ҵĲ���
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

