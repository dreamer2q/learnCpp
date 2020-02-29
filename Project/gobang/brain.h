#pragma once

#include <windows.h>
//#include <stdio.h>
#include <string>
#include "auxiliary.h"

class BRAIN{
public:
	BRAIN(int ai,int player,int (&map)[15][15]);
	void init();
	void setLevel(int level);
	POSITION begin();
	POSITION turn(int x, int y);
	bool playChess(int x,int y);
	void takeBack(int x, int y);

private:
	bool loadEngine();
	bool initMap();
	bool parseXY(char* cmd,POSITION *p);
	POSITION getXY();
	DWORD sendCommand(const char* cmd);
	int receiveResult(char* ret,int size);
	int receiveLine(char* ret, int size);
	const TCHAR* m_pbrain = L"pbrain.exe";

	HANDLE hOutRd;
	HANDLE hInWr;
	int m_ai;
	int m_player;
	
	int (&m_map)[15][15];
};

