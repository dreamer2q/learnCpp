#include "COMPUTER.h"
#include <stdio.h>


COMPUTER::COMPUTER()
{
	if (!loadEngine()) {
		MessageBox(NULL, TEXT("Load Engine Error"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(-1);
	}
}

POSITION COMPUTER::play()
{
	if (!isThinking()) {
		return getLastPos();
	}
	else {
		return POSITION{ -1,-1 };
	}
}

void COMPUTER::OnLButtonDown(POSITION p)
{

	auto func = [&](POSITION pos)->void {
		this->turn(pos);
	};
	std::thread thr(func,p);
	thr.detach();

	//sendTurn(p);
}

int COMPUTER::getPlayerInt()
{
	return ::COMPUTER;
}

void COMPUTER::turn(POSITION p)
{
	char cmd[128] = { 0 };
	char result[512] = { 0 };
	sprintf_s(cmd, "turn %d,%d\n", p.x, p.y);
	sendCommand(cmd);
	m_isThinking = true;
	m_lastPos = getXY();
	m_isThinking = false;
}

bool COMPUTER::isThinking()
{
	return m_isThinking;
}

POSITION COMPUTER::firstStep()
{
	char cmd[128] = { 0 };
	sprintf_s(cmd, "begin\n");
	sendCommand(cmd);
	return getXY();
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
	char command[512] = { 0 };
	if (level == 1)
	{
		sprintf_s(command, "INFO timeout_turn %d\n", timeoutturn);
		sendCommand(command);
		sprintf_s(command, "INFO timeout_match %d\n", timeoutmatch);
		sendCommand(command);
		sprintf_s(command, "INFO time_left %d\n", timeoutmatch);
		sendCommand(command);
		sprintf_s(command, "INFO max_node %d\n", maxnode); //now it should not be -1
		sendCommand(command);
		sprintf_s(command, "INFO max_depth %d\n", maxdepth);
		sendCommand(command);
		sprintf_s(command, "INFO time_increment %d\n", increment);
		sendCommand(command);
	}
	else
	{
		switch (level)
		{
		case 0:
			sprintf_s(command, "INFO max_node %d\n", -1);
			sendCommand(command);
			break;
		case 2:
			sprintf_s(command, "INFO max_node %d\n", 10000);
			sendCommand(command);
			break;
		case 3:
			sprintf_s(command, "INFO max_node %d\n", 20000);
			sendCommand(command);
			break;
		case 4:
			sprintf_s(command, "INFO max_node %d\n", 30000); //if the speed is 500k, then it will take at most 60s
			sendCommand(command);
			break;
		case 5:
			sprintf_s(command, "INFO max_node %d\n", 60000);
			sendCommand(command);
			break;
		case 6:
			sprintf_s(command, "INFO max_node %d\n", 120000);
			sendCommand(command);
			break;
		case 7:
			sprintf_s(command, "INFO max_node %d\n", 240000);
			sendCommand(command);
			break;
		case 8:
			sprintf_s(command, "INFO max_node %d\n", 1920000);
			sendCommand(command);
			break;
		case 9:
			sprintf_s(command, "INFO max_node %d\n", 38400000);
			sendCommand(command);
			break;
		case 10:
			sprintf_s(command, "INFO max_node %d\n", 500000000);
			sendCommand(command);
			break;
		}
		timeoutmatch = 100000000;
		timeoutturn = 2000000;
		increment = 0;
		sprintf_s(command, "INFO timeout_match %d\n", timeoutmatch);
		sendCommand(command);
		sprintf_s(command, "INFO time_left %d\n", timeoutmatch);
		sendCommand(command);
		sprintf_s(command, "INFO timeout_turn %d\n", timeoutturn);
		sendCommand(command);
		sprintf_s(command, "INFO max_depth %d\n", MAPWIDTH*MAPWIDTH);
		sendCommand(command);
		sprintf_s(command, "INFO time_increment %d\n", increment);
		sendCommand(command);
	}
	//receiveResult(command, 512);
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

void COMPUTER::sendTurn(POSITION p)
{
	char cmd[128] = { 0 };
	char result[512] = { 0 };
	sprintf_s(cmd, "turn %d,%d\n", p.x, p.y);
	sendCommand(cmd);
	m_isThinking = true;
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

