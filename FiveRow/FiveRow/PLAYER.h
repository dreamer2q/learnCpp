#pragma once

#include "MAP.h"

void formatTime(DWORD time,LPWSTR lpResult);

class PLAYER
{
public:
	PLAYER() = delete;
	PLAYER(PCWSTR imgPath,MAP* map);
	~PLAYER();
	
	void reset(DWORD total);
	void startRecodingTime();
	void endRecordingTime();
	LPCWSTR getPlayerName();
	void setPlayerName(LPCWSTR name);
	DWORD getLeftTime();
	Gdiplus::Image* getPlayerPortrait();
	
	virtual void play(POSITION p) = 0;
	virtual int getPlayerInt() = 0;

protected:
	MAP* m_map;
private:
	bool m_isRecording;
	DWORD m_StartTime;
	DWORD m_TotalTime;
	DWORD m_ClapsTime;
	DWORD m_LeftTime;
	LPWSTR m_PlayerName;
	Gdiplus::Image *m_playerPortrait = NULL;
};


