#pragma once
#include "PLAYER.h"

#include <thread>

//回调函数的声明，Cpp版本
using  COMPUTER_CALLBACK = void(*)(POSITION);
/*
//另一种声明方法，C语言版本
typedef void (*COMPUTER_CALLBACK)(POSITION)
*/

/*
COMPUTER类，继承PLAYER类

实现对游戏引擎（弈心）的操作，并由此来提供AI角色

*/
class COMPUTER : public PLAYER
{
public:
	COMPUTER(PCWSTR imgPath, MAP* map);
	~COMPUTER();

	void beforeStart();

	void play(POSITION p) override;					//实现基类虚函数

	void playFirstStep();
	POSITION getLastPos();
	void turn(POSITION p);
	bool isThinking();
	void takeBack(POSITION p);
	void setLevel(int level);
	void setInfo(EngineInfo info,int value);
	void setCallback(COMPUTER_CALLBACK callback);
	void loadHalf();
	COMPUTER_CALLBACK m_callback;					//回调函数，返回AI思考的结果
private:
	bool loadEngine();
	void initBrain();
	bool parseXY(char* cmd, POSITION* p);
	void updateThinkingStatus(bool status);
	POSITION getXY();
	DWORD sendCommand(const char* cmd);
	int receiveResult(char* ret, int size);

	const WCHAR* m_pbrain = L"brain/pbrain.exe";		//引擎的位置
	HANDLE hOutRd;
	HANDLE hInWr;
	
	bool m_isThinking = false;
	POSITION m_lastPos{ -1,-1 };
};

