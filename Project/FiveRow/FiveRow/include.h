
#pragma once

#ifndef  __INCLUDE_H__
#define __INCLUDE_H__

#include <windows.h>
#include <ObjIdl.h>
#include <gdiplus.h>
#include <MMSystem.h>

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"Gdiplus.lib")

#define MAXSTR 256
#define WIN_WIDTH 820
#define WIN_HEIGHT 663
#define MAPWIDTH 15

//Æå×Ó
enum {
	DRAW = -1,
	EMPTY = 0,
	WHITE,
	BLACK
};

//Player ID
enum {
	PLAYER = 0,
	PLAYER2,
	COMPUTER,		//Do not modify this, otherwise code won't work properly!
	NOBODY
};
//Game Mode
enum {
	PLAYER_PLAYER = 0,
	PLAYER_AI,
	SHOWCHESS,
	CREATECHESS,
	LOADHALF,
	NOTSTARTED,
	ENDGAME
};
//firstToMove
enum {	
	PLAYER_FIRST = 1,
	COMPUTER_FIRST
};
//COMPUTER SETTING
typedef enum {
	INFO_TIMEOUT_TURN,
	INFO_TIMEOUT_MATCH,
	INFO_TIME_LEFT,
	INFO_MAX_NODE,
	INFO_MAX_DEPTH,
	INFO_TIME_INCREMENT
} EngineInfo;
//Global
typedef struct {
	int level;
	int mode;
	int modeCreate;				//used when mode is CREATECHESS
	bool bkMusic;
	bool bkEffect;
} SETTING;
//Config File
typedef struct {
	WCHAR ConfigFile[MAXSTR];
	WCHAR Players[COMPUTER + 1][MAXSTR];		//COMPUTER represent 2, COMPUTER must not be modified£¡
} CONFIG;

typedef struct POSITION_TAG{
	int x;
	int y;
	bool operator==(const POSITION_TAG& p) {
		return this->x == p.x && this->y == p.y;
	};
} POSITION;


#include "resource.h"

//¸¨Öúº¯Êý
bool isInMap(int x, int y);
bool isInMap(POSITION p);
bool isFileExist(LPCWSTR filename);
bool isFileExistN(LPCWSTR filename,int size, int N);
int WstrRcat(LPWSTR dest, LPCWSTR source);
int WstrRcatN(LPWSTR destN, int size, int N, LPCWSTR source);

#endif  // ! __INCLUDE_H__