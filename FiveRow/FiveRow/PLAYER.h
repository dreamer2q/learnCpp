#pragma once
#include "include.h"

void formatTime(DWORD time,LPWSTR lpResult);

class PLAYER
{
public:
	PLAYER();
	PLAYER(DWORD totalTime);
	
	~PLAYER();
	
	void updateTime();
	DWORD getLeftTime();
	
	virtual POSITION play() = 0;
	virtual void OnLButtonDown(POSITION p) = 0;
	virtual int getPlayerInt() = 0;

private:
	DWORD m_StartTime;
	DWORD m_TotalTime;
	DWORD m_LeftTime;
};


