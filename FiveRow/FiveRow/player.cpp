#include "PLAYER.h"

PLAYER::PLAYER()
{
	m_StartTime = GetTickCount();
}

PLAYER::PLAYER(DWORD totalTime):PLAYER()
{
	
	m_TotalTime = totalTime;
}

PLAYER::~PLAYER()
{

}

void PLAYER::updateTime()
{
	m_LeftTime = m_TotalTime - (GetTickCount() - m_StartTime);
}

DWORD PLAYER::getLeftTime()
{
	updateTime();
	return m_LeftTime;
}

void formatTime(DWORD time, LPWSTR lpResult)
{
	if (time > 60 * 1000) {
		wsprintfW(lpResult, L"%02d:%02d", time / 1000000, time / 1000);
	}
	else {
		wsprintfW(lpResult, L"%02ds", time / 1000);
	}
}
