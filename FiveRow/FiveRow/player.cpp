#include "PLAYER.h"

PLAYER::PLAYER(PCWSTR imgPath,MAP* map)
{
	m_playerPortrait = new Gdiplus::Image(imgPath);
	m_map = map;
	reset(15 * 60 * 1000);
}

PLAYER::~PLAYER()
{
	delete m_playerPortrait;
}

void PLAYER::reset(DWORD total)
{
	m_TotalTime = total;
	m_ClapsTime = 0;
}

void PLAYER::startRecodingTime()
{
	m_StartTime = GetTickCount64();
}

void PLAYER::endRecordingTime()
{
	m_ClapsTime += GetTickCount64() - m_StartTime;
}

LPCWSTR PLAYER::getPlayerName()
{
	return m_PlayerName;
}

void PLAYER::setPlayerName(LPCWSTR name)
{
	if (!m_PlayerName) {
		delete m_PlayerName;
	}
	m_PlayerName = new WCHAR[lstrlenW(name) + 1];
	lstrcpyW(m_PlayerName, name);
}

DWORD PLAYER::getLeftTime()
{
	return m_TotalTime - m_ClapsTime - (GetTickCount64() - m_StartTime);
}

Gdiplus::Image* PLAYER::getPlayerPortrait()
{
	return m_playerPortrait;
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
