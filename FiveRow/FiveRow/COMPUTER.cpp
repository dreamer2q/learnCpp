#include "COMPUTER.h"
#include <stdio.h>


COMPUTER::COMPUTER(PCWSTR imgPath, MAP* map):PLAYER(imgPath, map)
{
	if (!loadEngine()) {
		MessageBox(NULL, TEXT("Load Engine Error"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(-1);
	}
}

void COMPUTER::play(POSITION p)
{
	if (m_isThinking) {
		return;
	}
	auto func = [&](POSITION pos)->void {
		this->turn(pos);
	};
	std::thread thr(func, p);
	thr.detach();
}

int COMPUTER::getPlayerInt()
{
	return ::COMPUTER;
}

void COMPUTER::turn(POSITION p)
{
	startRecodingTime();
	char cmd[128] = { 0 };
	sprintf_s(cmd, "turn %d,%d\n", p.x, p.y);
	sendCommand(cmd);
	m_isThinking = true;
	m_lastPos = getXY();
	m_isThinking = false;
	m_callback(m_lastPos);
	setInfo(INFO_TIME_LEFT, getLeftTime());
	endRecordingTime();
}

bool COMPUTER::isThinking()
{
	return m_isThinking;
}

void COMPUTER::playFirstStep()
{
	startRecodingTime();
	char cmd[128] = { 0 };
	sprintf_s(cmd, "begin\n");
	sendCommand(cmd);
	m_isThinking = true;
	m_lastPos = getXY();
	m_isThinking = false;
	m_callback(m_lastPos);
	endRecordingTime();
}

POSITION COMPUTER::getLastPos()
{
	return m_lastPos;
}

void COMPUTER::takeBack(POSITION p)
{
	char cmd[128];
	sprintf_s(cmd, "takeback %d,%d\n", p.x, p.y);
	sendCommand(cmd);
	receiveResult(cmd, 128);
}

void COMPUTER::setLevel(int level)
{
	int maxNode = 1000;
	int maxDepth = 50;
	int timeoutTurn = 2000;
	int timeoutMatch = 15 * 60 * 1000;
	int timeIncrement = 0;
	int timeLeft = timeoutMatch;
	switch (level)
	{
	case 1:
		//default level
		break;
	case 2:
		timeoutTurn = 10000;
		maxNode <<= 1;
		maxDepth = 100;
		break;
	case 3:
		timeoutTurn = 20000;
		maxNode <<= 2;
		maxDepth = 150;
		break;
	case 4:
		timeoutTurn = 30000;
		maxNode <<= 3;
		maxDepth = 200;
		break;
	}
	setInfo(INFO_MAX_DEPTH, maxDepth);
	setInfo(INFO_MAX_NODE, maxNode);
	setInfo(INFO_TIMEOUT_MATCH, timeoutMatch);
	setInfo(INFO_TIMEOUT_TURN, timeoutTurn);
	setInfo(INFO_TIME_LEFT, timeLeft);
	setInfo(INFO_TIME_INCREMENT, timeIncrement);
}

void COMPUTER::setInfo(EngineInfo info, int value)
{
	char cmd[512] = { 0 };
	switch (info)
	{
	case INFO_MAX_DEPTH:
		wsprintfA(cmd, "INFO max_depth %d\n", value);
		break;
	case INFO_MAX_NODE:
		wsprintfA(cmd, "INFO max_node %d\n", value);
		break;
	case INFO_TIMEOUT_MATCH:
		wsprintfA(cmd, "INFO timeout_match %d\n", value);
		break;
	case INFO_TIMEOUT_TURN:
		wsprintfA(cmd, "INFO timeout_turn %d\n", value);
		break;
	case INFO_TIME_LEFT:
		wsprintfA(cmd, "INFO time_left %d\n", value);
		break;
	case INFO_TIME_INCREMENT:
		wsprintfA(cmd, "INFO time_increment %d\n", value);
		break;
	}
	sendCommand(cmd);
}

void COMPUTER::setCallback(COMPUTER_CALLBACK callback)
{
	COMPUTER::m_callback = callback;
}

void COMPUTER::beforeStart()
{
	initBrain();
}

bool COMPUTER::loadEngine()
{
	HANDLE hOutWr;
	HANDLE hInRd;
	SECURITY_ATTRIBUTES sa;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = true;

	if (!CreatePipe(&hInRd, &hInWr, &sa, 0)) {
		MessageBoxA(NULL, "Error on createPipe()", "ERROR", MB_ICONWARNING | MB_OK);
		return false;
	}
	if (!CreatePipe(&hOutRd, &hOutWr, &sa, 0)) {
		MessageBoxA(NULL, "Error on createPipe()", "ERROR", MB_ICONWARNING | MB_OK);
		return false;
	}

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdInput = hInRd;
	si.hStdOutput = hOutWr;
	si.hStdError = hOutWr;
	si.wShowWindow = SWP_HIDEWINDOW;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	if (!CreateProcess(m_pbrain, NULL, NULL, NULL, true, NULL, NULL, NULL, &si, &pi)) {
		MessageBoxA(NULL, "CreateProcess Error", "ERROR", MB_ICONWARNING | MB_OK);
		return false;
	}
	return true;
}

void COMPUTER::initBrain()
{
	char buf[512] = { 0 };
	sendCommand("start 15\n");
	receiveResult(buf, 512);
}

bool COMPUTER::parseXY(char* cmd, POSITION* p)
{
	char* comma = strstr(cmd, ",");
	int x=-1, y=-1;
	int length = strlen(cmd);
	if (comma) {
		if (length > 6) {
			comma -= 2;
		}
		else {
			comma = cmd;
		}
		sscanf_s(comma, "%d,%d", &x, &y);
		sprintf_s(cmd, 64, "ParseXY-> %d,%d\n", x, y);
		OutputDebugStringA(cmd); //For debug
		*p = POSITION{ x,y };
	}
	else {
		return false;
	}
	return true;
}

void COMPUTER::updateThinkingStatus(bool status)
{
	m_isThinking = status;
}

POSITION COMPUTER::getXY()
{
	POSITION p = POSITION{ -1,-1 };

	while (1) {
		char result[512] = { 0 };
		receiveResult(result, 512);
		if (parseXY(result, &p)) {
			break;
		}
	}
	return p;
}

DWORD COMPUTER::sendCommand(const char* cmd)
{
	DWORD nWritten;
	OutputDebugStringA("SendCommand\n");
	OutputDebugStringA(cmd);
	OutputDebugStringA("------------------\n");
	if (!WriteFile(hInWr, cmd, strlen(cmd) * sizeof(char), &nWritten, NULL)) {
		return -1;
	}
	return nWritten;
}

int COMPUTER::receiveResult(char* ret, int size)
{
	DWORD nRead;
	if (!ReadFile(hOutRd, ret, size, &nRead, NULL)) {
		OutputDebugStringA("ReadFile failed");
		return -1;
	}
	OutputDebugStringA("ReceiveResult\n");
	OutputDebugStringA(ret);
	OutputDebugStringA("------------------\n");
	return nRead;
}

