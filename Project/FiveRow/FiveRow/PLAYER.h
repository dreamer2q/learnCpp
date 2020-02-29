#pragma once

#include "MAP.h"

//��ĸ�������
void formatTime(DWORD time,LPWSTR lpResult);

/*
������Ϸ��ɫ�Ļ��ࣺ

��ȡ����Ϸ��ɫ�Ļ�������
	��ɫ����
	��ɫID
	��ɫͷ��

ʵ��ͨ�÷���
	��¼��ɫ��˼��ʱ��
*/
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
	int getPlayerInt();
	void setPlayerInt(int playerInt);

protected:
	MAP* m_map;		//�̳�ʹ��
private:
	int m_playerInt;
	bool m_isRecording;
	DWORD m_StartTime;
	DWORD m_TotalTime;
	DWORD m_ElapsTime;
	DWORD m_LeftTime;
	LPWSTR m_PlayerName;
	Gdiplus::Image *m_playerPortrait = NULL;
};


