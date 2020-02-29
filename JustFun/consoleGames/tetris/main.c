#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>

/* definitions */
#define WIDTH 17
#define HEIGHT 30

/* enum */
enum{
	//Game code
	L=3,J,I,O,W,Z,S,
	//Map records
	BLNK=0,WALL=2,TRIS=1,
	//Keyboard codes
	KB_UP		=	72,
	KB_DOWN		=	80,
	KB_LEFT		=	75,
	KB_RIGHT	=	77,
	KB_SPACR	=	32,
	KB_ESC		=	27,
};


/* structure */
typedef struct {
	int x;
	int y;
	int bar[4][4];
	int num;
	int rotate;
	int color;
} TETRIS;

struct {
	int color;
	char *c;
} mapCC[3] = {		//□■ 
		{2,"  "},
		{1,"■"},
		{4,"□"},
};

/* global variable */
int score=-10,level=5;
int g_map[WIDTH][HEIGHT];
int g_Bars[7][4][4]=
{	{ 					/* L,J,I,O,W,Z,S,*/
			{0,1,0,0},
			{0,1,0,0},
			{0,1,1,0}, 
			{0,0,0,0}
		},{
			{0,1,0,0},
			{0,1,0,0},
			{1,1,0,0}, 
			{0,0,0,0}	
		},{
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0}, 
			{0,0,0,0}	
		},{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0}, 
			{0,0,0,0}	
		},{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,1,0}, 
			{0,0,0,0}	
		},{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,1,0}, 
			{0,0,0,0}	
		},{
			{0,0,0,0},
			{0,1,1,0},
			{1,1,0,0}, 
			{0,0,0,0}	
		}				
};


/* functions */
void initEnv();
void initGame();
void startGame();
void pauseGame();
void continueGame();
void endGame();
int loadMenu(); 
//more details 
void drawMap();
void drawTetris(TETRIS *t);
void eraseTetris(TETRIS *t);
int isCrashed(TETRIS *t);
int  generateTetris(TETRIS *t);
int rotateTetris(TETRIS *t);
int moveTetris(TETRIS *t,int drection);
int dropTetris(TETRIS *t);
void fixTetris(TETRIS *t);
void showNextTetris(TETRIS *t);
int eraseLine();
int addScore();
void cpyBar(int first[4][4],int second[4][4]);
//console function
void setConsoleSize(int w,int h);
void setTitle(char *t);
void setPos(int x,int y);
void setColor(int c);
void drawP(int x,int y,int c,char* str);
void hideCursor();

//----------------------------------------dividing line--------------------------------------------- 
int main(int argc, char *argv[])
{
	while(loadMenu()){
		startGame();	
	}
	
	return 0;
}

int loadMenu(){
	
	setConsoleSize(30,15);
	setColor(9);
	setPos(2,2);
	printf("C语言Tetris");
	setPos(2,3);
	setColor(2); 
	printf("--------------");
	setPos(2,4);
	setColor(5);
	printf("1.Start Game");
	setPos(2,5);
	printf("2.About");
	setPos(2,6);
	printf("q.Exit");
	setPos(2,7);
	setColor(2);
	printf("---------------");
	setColor(4);
	setPos(2,9);
	printf("Copyright：Jiyan Senior High School CodingClub");
	char cmd;
	while((cmd = getch())!= 'q'){
		switch(cmd){
			case '2':
				MessageBox(NULL,"Defaults occurs occasionally.\nIt would be appreciated if you could help.Thx","CodingClub",MB_OK);
			break;
			case '1':return TRUE;
			
			}
	} 
	return TRUE;	
}

void startGame(){
	initGame();
	
	TETRIS tetris,next_tetris;
	generateTetris(&tetris);
	generateTetris(&next_tetris);
	drawTetris(&tetris);
	showNextTetris(&next_tetris);
	
	char cmd;
	int flag=FALSE;
	while(1){
		if(kbhit()){
			cmd = getch();	
			setPos(WIDTH+3,20);
			printf("%03d",cmd);
			switch(cmd){
				case KB_UP:{
					tetris.rotate = 1;
					eraseTetris(&tetris);
					rotateTetris(&tetris);
					drawTetris(&tetris);
					continue;
				}
				case KB_DOWN:{
					flag = TRUE; 
					//continue
					break;
				}
				case KB_LEFT:{				//moveTetris
					eraseTetris(&tetris);
					moveTetris(&tetris,-1);
					drawTetris(&tetris);
					continue;
				}
				case KB_RIGHT:{				//moveTetris
					eraseTetris(&tetris);
					moveTetris(&tetris,1);
					drawTetris(&tetris);	
					continue;
				}
				case KB_SPACR:{
					//pause or continue
					break;
				}
				case KB_ESC:{
				
					//?
					break;
				}
				case -32:{ //在win10里面按下一个键的时候总会出现-32代码。在这里将其避免。 
					continue;
				}
				default:
				{
					//stop.
					break;
				}
			}
		
		}
		
		eraseTetris(&tetris);
		if(dropTetris(&tetris)){
			fixTetris(&tetris);
			drawTetris(&tetris);
			eraseLine() && addScore();
			memcpy(&tetris,&next_tetris,sizeof(TETRIS));//copy tetris...
			generateTetris(&next_tetris);
			showNextTetris(&next_tetris);
		}else{
			drawTetris(&tetris);
		}
		if (flag == TRUE){  //acceleration
			flag = FALSE;
			continue;
		}
		Sleep(550 - 50*level);
	}
	return ;
}

void initGame(){
	setConsoleSize(2*WIDTH+20,HEIGHT);
	hideCursor();
	initEnv();
	drawMap();
}

void initEnv(){
	
	//set border of map 
	int i,j;
	for (i=0;i<WIDTH;i++){
		for(j=0;j<HEIGHT;j++){
			if (i==0||i==WIDTH-1||j==0||j==HEIGHT-1){
				g_map[i][j] = WALL;
			}else{
				g_map[i][j] = BLNK;
			}
		}
	}
	
	setPos(WIDTH+2,2);
	setColor(9);
	printf("Next");
	setPos(WIDTH+2,8);
	setColor(2);
	printf("LEVEL");
	setPos(WIDTH+2,10);
	printf("Sores");
	addScore();
	
	srand((unsigned)time(NULL));
	
	return ;
}

void showNextTetris(TETRIS *t){
	
	int i,j;
	for (i=0;i<4;i++){
		for (j=0;j<4;j++){
			setPos(WIDTH+2+i,3+j);
			printf("  ");
		}
	}
	int tmpX,tmpY;
	tmpX = t->x;tmpY = t->y;
	t->x = WIDTH+2; t->y = 3;
	drawTetris(t);
	t->x = tmpX;t->y = tmpY;
	return ;
}


void fixTetris(TETRIS *t){
	int i,j;
	for (i=0;i<4;i++){
		for (j=0;j<4;j++){
			if (t->bar[i][j] == TRIS){
				g_map[t->x + i][t->y + j] = TRIS;		
			}
		}
	}
}

int eraseLine(){
	int i,j;
	for (j=HEIGHT-1;j>0;j--){
		for (i=1;i<WIDTH;i++){
			if (g_map[i][j] != TRIS	){
				break;
			}
		}
		if (i==WIDTH-1){	
			int k;
			for (k=j;k>1;k--){
				for (i=1;i<WIDTH;i++){
					g_map[i][k] = g_map[i][k-1];
				}
			}
			drawMap();
			return TRUE;
		}
	}
	return FALSE;;	
}

int addScore(){
	score += 10;
	level = score/500 + 1;
	if (level > 10 ){
		level = 10;
	}
	setPos(WIDTH+2,9);
	setColor(4);
	printf("%d",level);
	setPos(WIDTH+2,11);
	printf("%d",score);
	return score;
}

int dropTetris(TETRIS *t){
	
	int i,j;
	for (i=0;i<4;i++){
		for (j=3;j>=0;j--){
			if (t->bar[i][j] == TRIS){
				if (g_map[t->x+i][t->y+j+1] == TRIS || g_map[t->x+i][t->y+j+1] == WALL){
						return 1; //fixed
				}
			break;
			}
		}
	}
	++t->y;
	return 0;
}

int moveTetris(TETRIS* t, int drection) {
	int i, j;
	for (j = 0; j < 4; j++) {
		if (drection == -1) {
			for (i = 0; i < 4; i++) {
				if (t->bar[i][j] == TRIS) {
					if (g_map[t->x + i + drection][t->y + j] == TRIS || g_map[t->x + i + drection][t->y + j] == WALL) {
						return 1; //can't move
					}
					break;
				}
			}
		}
		else if (drection == 1) {
			for (i = 3; i >= 0; i--) {
				if (t->bar[i][j] == TRIS) {
					if (g_map[t->x + i + drection][t->y + j] == TRIS || g_map[t->x + i + drection][t->y + j] == WALL) {
						return 1; //fixed
					}
					break;
				}
			}
		}
		else {
			MessageBox(NULL, "出错了", "Metris", MB_OK);
			exit(-1);
		}
	}
	t->x = t->x + drection;
	return 0;
}

void drawMap(){
	int i,j;
	for (i=0;i<WIDTH;i++){
		for (j=0;j<HEIGHT;j++){
			setColor(mapCC[g_map[i][j]].color);
			setPos(i,j);
			printf("%s",mapCC[g_map[i][j]].c);
		}
	}
	return ;	
}

int generateTetris(TETRIS *t){
	int r = rand()%(7);
	t->num	=	r;
	t->color=   r+2;
	t->x	=	WIDTH/2;
	t->y	=	1;
	cpyBar(t->bar,g_Bars[r]);
	t->rotate = rand()%(4);
	int i,j,tmp[4][4];
	while (t->rotate>0){
		for (i=0;i<4;i++){
			for (j=0;j<4;j++){
				tmp[i][j] = t->bar[i][j];
			}
		}
		for (i=0;i<4;i++){
			for (j=0;j<4;j++){
				t->bar[i][j] = tmp[3-j][i];
			}
		}
	--t->rotate;
	}
	t->y	=	(t->bar[0][0]==BLNK&&t->bar[1][0]==BLNK&&
				t->bar[2][0]==BLNK&&t->bar[3][0]==BLNK)?--t->y:t->y;
	t->y	=	(t->bar[0][1]==BLNK&&t->bar[1][1]==BLNK&&
				t->bar[2][1]==BLNK&&t->bar[3][1]==BLNK)?--t->y:t->y;
	return 0;
}

int isCrashed(TETRIS *t){
	int i,j;
	for (i=0;i<4;i++){
		for	(j=0;j<4;j++){
			if (t->bar[i][j] != BLNK && g_map[t->x + i][t->y + j] != BLNK){
				return TRUE;
			}
		}
	}
	return FALSE;
}

void eraseTetris(TETRIS *t){
	int i,j;
	for (i=0;i<4;i++){
		for (j=0;j<4;j++){
			if (t->bar[i][j] == TRIS){
				drawP(t->x+i,t->y+j,mapCC[BLNK].color,mapCC[BLNK].c);
			}
		}
	}
}

int rotateTetris(TETRIS *t){
	while (t->rotate<0){
		t->rotate += 4;
	}
	while ( t->rotate > 0){
		int i,j,tmp[4][4];
		for (i=0;i<4;i++){
			for (j=0;j<4;j++){
				tmp[i][j] = t->bar[i][j];
			}
		}
		for (i=0;i<4;i++){
			for (j=0;j<4;j++){
				t->bar[i][j] = tmp[3-j][i];
			}
		}
		if(isCrashed(t)){
			for (i=0;i<4;i++){
				for (j=0;j<4;j++){
					t->bar[i][j] = tmp[i][j];
				}
			}
			return -1;
		}
		t->rotate--;
	}
	return 0;
}

void drawTetris(TETRIS *t){
	int i,j;
	for (i=0;i<4;i++){
		for (j=0;j<4;j++){
			if (t->bar[i][j] == TRIS){
				drawP(t->x+i,t->y+j,t->color,mapCC[TRIS].c);
			}
		}
	}
}



void cpyBar(int first[4][4],int second[4][4]){
	int i,j;
	for (i=0;i<4;i++){
		for (j=0;j<4;j++){
			first[i][j] = second[i][j];
		}
	}
	return ;
}


void drawP(int x,int y,int c,char* str){
	setPos(x,y);
	setColor(c);
	printf("%s",str);
	return ;
}


void setPos(int x,int y){
	COORD coord;
	coord.X = x*2;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
	return ;
}

void setColor(int c){
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
	return ;
}

void setTitle(char *t){
	char cmd[100]; 
	sprintf(cmd,"title %s",t);
	system(cmd);
	return ;
}

void setConsoleSize(int w,int h){
	char cmd[100];
	sprintf(cmd,"mode con cols=%d lines=%d",w,h);
	system(cmd);
	return ;
}

void hideCursor(){
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);
	info.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);
	return ;
}
