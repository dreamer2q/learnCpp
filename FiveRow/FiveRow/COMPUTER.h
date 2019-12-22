#pragma once
#include "PLAYER.h"

#include <thread>

//�ص�������������Cpp�汾
using  COMPUTER_CALLBACK = void(*)(POSITION);
/*
//��һ������������C���԰汾
typedef void (*COMPUTER_CALLBACK)(POSITION)
*/

/*
COMPUTER�࣬�̳�PLAYER��

ʵ�ֶ���Ϸ���棨���ģ��Ĳ��������ɴ����ṩAI��ɫ

*/
class COMPUTER : public PLAYER
{
public:
	COMPUTER(PCWSTR imgPath, MAP* map);
	~COMPUTER();

	void beforeStart();

	void play(POSITION p) override;					//ʵ�ֻ����麯��

	void playFirstStep();
	POSITION getLastPos();
	void turn(POSITION p);
	bool isThinking();
	void takeBack(POSITION p);
	void setLevel(int level);
	void setInfo(EngineInfo info,int value);
	void setCallback(COMPUTER_CALLBACK callback);
	void loadHalf();
	COMPUTER_CALLBACK m_callback;					//�ص�����������AI˼���Ľ��
private:
	bool loadEngine();
	void initBrain();
	bool parseXY(char* cmd, POSITION* p);
	void updateThinkingStatus(bool status);
	POSITION getXY();
	DWORD sendCommand(const char* cmd);
	int receiveResult(char* ret, int size);

	const WCHAR* m_pbrain = L"brain/pbrain.exe";		//�����λ��
	HANDLE hOutRd;
	HANDLE hInWr;
	
	bool m_isThinking = false;
	POSITION m_lastPos{ -1,-1 };
};

