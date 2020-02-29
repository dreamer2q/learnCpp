#pragma once

typedef struct {
	int x, y;
} POSITION;

typedef struct {
	POSITION p;
	int score;
} MOVE;

typedef struct{
	int n;
	int score;
	const char* t;
} EvaluteMap;
