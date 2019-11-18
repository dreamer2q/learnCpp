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
	对应的颜色码表：
	1. 0 = 黑色       8 = 灰色
	1 = 蓝色       9 = 淡蓝色
	2 = 绿色       10 = 淡绿色
	3 = 浅绿色     11 = 淡浅绿色
	4 = 红色       12 = 淡红色
	5 = 紫色       13 = 淡紫色
	6 = 黄色       14 = 淡黄色
	7 = 白色       15 = 亮白色
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
