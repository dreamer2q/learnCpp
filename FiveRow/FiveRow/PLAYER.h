#pragma once

#include "MAP.h"

//类的辅助函数
void formatTime(DWORD time,LPWSTR lpResult);

/*
这是游戏角色的基类：

提取了游戏角色的基础属性
	角色名称
	角色ID
	角色头像

实现通用方法
	记录角色的思考时间
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
	MAP* m_map;		//继承使用
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


