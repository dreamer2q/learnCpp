#pragma once

#ifndef __AUXILIARY__
#define __AUXILIARY__

#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h> 

#define _CONSOLE_LINES_ 30
#define _CONSOLE_COLUMNS_ 60

enum Color{
	black = 0,blue,green,lightGreen,red,purple,yellow,white,grey,lightBlue,shadowGreen,lightShadowGreen,lightRed,lightPurple,lightYellow,lightBright
/*
	��Ӧ����ɫ���
	1. 0 = ��ɫ       8 = ��ɫ
	1 = ��ɫ       9 = ����ɫ
	2 = ��ɫ       10 = ����ɫ
	3 = ǳ��ɫ     11 = ��ǳ��ɫ
	4 = ��ɫ       12 = ����ɫ
	5 = ��ɫ       13 = ����ɫ
	6 = ��ɫ       14 = ����ɫ
	7 = ��ɫ       15 = ����ɫ
*/
};

typedef struct tagArray{
	struct tagArray *next;
	int value;	
} *Array;

Array makeArray();
Array insertElementByOrder(Array root,int value);
Array deleteArray(Array root);
int getArrayAt(Array root,int position);
int getArrayLength(Array root);

void setPos(int x,int y);
void setColor(int c);
void initConsole(int width,int height);
void hideCursor();
void printN(int *a,int n,int enter = 0);
void randomNumsGenerate(int *a,int n);
void cls();
void clearLine(int y);
void printC(const char *s,int c); 
void setTitle(const char* title);
void initConsole(int width, int height);
void printLine(char ch, int c);
int getMaxIn(int* a, int n);
int _pow(int base, int n);
void bye();
void startTimer();
ULONGLONG stopTimer();  //returns how long has passed measured in millisecond
bool isInArray(int i, int* a, int n);
void swap(int* a, int i, int j);
void showHeap(int* a, int n, int i, int y, int x);
#endif
