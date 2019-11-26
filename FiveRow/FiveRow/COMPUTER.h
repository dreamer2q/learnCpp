#pragma once
#include "PLAYER.h"

class COMPUTER : public PLAYER
{
public:
	COMPUTER();
	//~COMPUTER();

	void beforeStart();

	POSITION play() override;
	void OnLButtonDown(POSITION p) override;
	int getPlayerInt() override;

	void takeBack(POSITION p);
	void setLevel(int level);

	//
	//void setLevel(int level);
	//POSITION begin();
	//POSITION turn(int x, int y);
	//bool playChess(int x, int y);

private:
	bool loadEngine();
	void initBrain();
	void sendTurn(POSITION p);
	bool parseXY(char* cmd, POSITION* p);
	POSITION getXY();
	DWORD sendCommand(const char* cmd);
	int receiveResult(char* ret, int size);


	const WCHAR* m_pbrain = L"brain/pbrain.exe";
	HANDLE hOutRd;
	HANDLE hInWr;


	int timeoutturn = 10000;
	int timeoutmatch = 2000000;
	int maxdepth = 100;
	int maxnode = 1000000000;
	int increment = 0;
};

