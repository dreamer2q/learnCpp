#pragma once

#include "PLAYER.h"

class PERSON:public PLAYER
{
public:
	POSITION play() override;
	void OnLButtonDown(POSITION p) override;
	int getPlayerInt() override;

private:
	POSITION m_OnLButtonDownPosition;
};

