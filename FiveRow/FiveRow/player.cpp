#include "PLAYER.h"

PLAYER::PLAYER(PCWSTR imgPath,MAP* map)
{
	//WCHAR currDir[512] = { 0 };
	//GetCurrentDirectory(512, currDir);
	//lstrcatW(currDir, L"/");
	//lstrcatW(currDir, imgPath);
	//m_playerPortrait = new Gdiplus::Image(currDir);
	m_playerPortrait = new Gdiplus::Image(imgPath);
	m_map = map;
	reset(15 * 60 * 1000);
}

PLAYER::~PLAYER()
{
	//delete m_playerPortrait;
}

void PLAYER::reset(DWORD total)
{
	m_TotalTime = total;
	m_LeftTime = total;
	m_ElapsTime = 0;
	m_isRecording = false;
}

void PLAYER::startRecodingTime()
{
	m_StartTime = GetTickCount64();
	m_isRecording = true;
}

void PLAYER::endRecordingTime()
{
	m_ElapsTime += GetTickCount64() - m_StartTime;
	m_isRecording = false;
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
	if (m_isRecording) {
		m_LeftTime =  m_TotalTime - m_ElapsTime - (GetTickCount64() - m_StartTime);
	}
	return m_LeftTime;
}

Gdiplus::Image* PLAYER::getPlayerPortrait()
{
	return m_playerPortrait;
}

int PLAYER::getPlayerInt()
{
	return m_playerInt;
}

void PLAYER::setPlayerInt(int playerInt)
{
	m_playerInt = playerInt;
}

void formatTime(DWORD time, LPWSTR lpResult)
{
	if (time > 60 * 1000) {
		wsprintfW(lpResult, L"%02d:%02d", time / (60*1000), (time / 1000) % 60);
	}
	else {
		wsprintfW(lpResult, L"%02ds", time / 1000);
	}
}
