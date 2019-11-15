#include "brain.h"

BRAIN::BRAIN(int ai, int player, int(&map)[15][15]): m_map(map){
	m_ai = ai;
	m_player = player;
	if (!loadEngine()) {
		MessageBoxA(NULL, "Load Engine failed", "ERROR", MB_OK | MB_ICONERROR);
		exit(-1);
	}
}

void BRAIN::init(){
	initMap();
}

void BRAIN::setLevel(int level){
	char cmd[128] = { 0 };
	sprintf_s(cmd, "info timeout_turn %d\n", level * 1000);
	sendCommand(cmd);
}

POSITION BRAIN::begin(){
	sendCommand("begin\n");

	return getXY();
}

bool BRAIN::playChess(int x, int y){
	char cmd[128] = { 0 };
	sprintf_s(cmd, "play %d,%d\n", x, y);
	sendCommand(cmd);
	receiveResult(cmd,128);
	return true;
}

void BRAIN::takeBack(int x, int y){
	char cmd[128];
	sprintf_s(cmd, "takeback %d,%d\n", x, y);
	sendCommand(cmd);
	receiveResult(cmd, 128);
}

POSITION BRAIN::turn(int x, int y){
	char cmd[128] = { 0 };
	char result[512] = { 0 };
	sprintf_s(cmd, "turn %d,%d\n", x, y);	
	sendCommand(cmd);

	return getXY();
}

bool BRAIN::loadEngine(){

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
	si.wShowWindow = SWP_SHOWWINDOW;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	if (!CreateProcess(m_pbrain,NULL,NULL,NULL,true,NULL,NULL,NULL,&si,&pi)) {

		MessageBoxA(NULL, "CreateProcess Error", "ERROR", MB_ICONWARNING | MB_OK);
		return false;
	}

	return true;
}

bool BRAIN::initMap(){
	char buf[512] = { 0 };
	sendCommand("start 15\n");
	receiveResult(buf, 512);
	return true;
}

bool BRAIN::parseXY(char* cmd,POSITION *p){
	char* comma = strstr(cmd, ",");
	int x , y;
	if (comma) {
		sscanf_s(cmd, "%d,%d", &x, &y);
		sprintf_s(cmd,64, "ParseXY-> %d,%d\n", x, y);
		OutputDebugStringA(cmd); //For debug
		*p = POSITION{ x,y };
	}
	else {
		return false;
	}
	return true;
}

POSITION BRAIN::getXY(){
	
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

DWORD BRAIN::sendCommand(const char* cmd){
	DWORD nWritten;
	OutputDebugStringA("SendCommand\n");
	OutputDebugStringA(cmd);
	OutputDebugStringA("------------------\n");
	if (!WriteFile(hInWr, cmd, strlen(cmd) * sizeof(char), &nWritten, NULL)) {
		return -1;
	}
	return nWritten;
}

int BRAIN::receiveResult(char* ret, int size){
	
	DWORD nRead;// , nTotal = 0;
	//while (
	if(!ReadFile(hOutRd, ret, size, &nRead, NULL)) {
		//if (nRead != 0) {

		//}
		OutputDebugStringA("ReadFile failed");
		return -1;
	}
	OutputDebugStringA("ReceiveResult\n");

	
	//DWORD nAvail;
	//std::string result = "";
	//while (1) {
		//char buf[512] = { 0 };
		//PeekNamedPipe(hOutRd, NULL, 0, NULL, &nAvail, NULL);
		//if (nAvail != 0) {
			//ReadFile(hOutRd, buf, 512, &nRead, NULL);
			//nTotal += nRead;
			//result += buf;
			//OutputDebugStringA(buf);
		//}
		//else {
		//	break;
		//}
	//}
	//strcpy_s(ret,size, result.c_str());
	OutputDebugStringA(ret);
	OutputDebugStringA("------------------\n");
	//return nTotal;
	return nRead;
}

int BRAIN::receiveLine(char* ret, int size){
	
	return 0;
}

