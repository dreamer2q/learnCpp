
#pragma once

#ifndef  __INCLUDE_H__
#define __INCLUDE_H__


#include <windows.h>
#include <ObjIdl.h>
#include <gdiplus.h>

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
	NOBODY = 0,
	PLAYER,
	COMPUTER
};

enum {
	PLAYER_PLAYER = 0,
	PLAYER_AI
};

enum {	
	PLAYER_FIRST = 1,
	COMPUTER_FIRST
};

typedef struct {
	int x;
	int y;
} POSITION;

#include "resource.h"




bool isInMap(int x, int y);
bool isInMap(POSITION p);


#endif // ! __INCLUDE_H__