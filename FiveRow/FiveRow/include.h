
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
#define COMPUTER_MAIN_TIMER 11101

enum {
	EMPTY = 0,
	WHITE,
	BLACK
};

enum {
	PLAYER = 0,
	PLAYER2,
	COMPUTER,
	NOBODY
};

enum {
	PLAYER_PLAYER = 0,
	PLAYER_AI
};

enum {	
	PLAYER_FIRST = 1,
	COMPUTER_FIRST
};

typedef enum {
	INFO_TIMEOUT_TURN,
	INFO_TIMEOUT_MATCH,
	INFO_TIME_LEFT,
	INFO_MAX_NODE,
	INFO_MAX_DEPTH,
	INFO_TIME_INCREMENT
} EngineInfo;

typedef struct {
	int firstToPlay;
	int level;
	int mode;
	bool bkMusic;
	bool bkEffect;
} SETTING;


typedef struct {
	int x;
	int y;
} POSITION;

#include "resource.h"




bool isInMap(int x, int y);
bool isInMap(POSITION p);


#endif // ! __INCLUDE_H__