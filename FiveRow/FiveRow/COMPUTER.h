#pragma once
#include "PLAYER.h"

#include <thread>

class COMPUTER : public PLAYER
{
public:
	COMPUTER();
	//~COMPUTER();

	void beforeStart();

	POSITION play() override;
	void OnLButtonDown(POSITION p) override;
	int getPlayerInt() override;

	void turn(POSITION p);
	bool isThinking();
	POSITION firstStep();
	POSITION getLastPos();
	void takeBack(POSITION p);
	void setLevel(int level);

	//
	//void setLevel(int level);
	//
	//POSITION turn(int x, int y);
	//bool playChess(int x, int y);

private:
	bool loadEngine();
	void initBrain();
	void sendTurn(POSITION p);
	bool parseXY(char* cmd, POSITION* p);
	void updateThinkingStatus(bool status);
	POSITION getXY();
	DWORD sendCommand(const char* cmd);
	int receiveResult(char* ret, int size);


	const WCHAR* m_pbrain = L"brain/pbrain.exe";
	HANDLE hOutRd;
	HANDLE hInWr;
	
	bool m_isThinking = false;
	POSITION m_lastPos{ -1,-1 };

	int timeoutturn = 1000;
	int timeoutmatch = 2000000;
	int maxdepth = 100;
	int maxnode = 1000000000;
	int increment = 0;
};

