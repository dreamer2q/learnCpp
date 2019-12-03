#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
/*非阻塞函数监听键盘输入*/

/* definition */

#define WIDTH 30
#define LENGTH 30
#define INITLENGTH 3
/*
#define FOOD "●"
#define BODY "★"
#define BLNK "■"
#define WALL "□"*/

/* structure  */
enum{
	//Keyboard codes
	KB_UP		=	72,
	KB_DOWN		=	80,
	KB_LEFT		=	75,
	KB_RIGHT	=	77,
	KB_SPACR	=	32,
	KB_ESC		=	27,
	//OBJECT codes
	BLNK		=	0,
	WALL		=	1,
	BODY		=	2,
	FOOD		=	3

};
struct {
	int color;
	char* c;
} C[4] = {
	{2,"■"},
	{4,"□"},
	{6,"★"},
	{4,"●"}
};


/*functions*/

void setPos(int x,int y);
void setColor(int c);
void drawP(int i,int j);
void hideCursor(); 
void drawMap();
void gFOOD();
void initConsole();
void face();
void startGame();
void initPannel();
void gScore(int,int,int);

/*global */
int g_map[LENGTH][WIDTH]; /* BLNK = 0 WALL = 1 BODY = 2 FOOD = 3 */
struct{
	int x;
	int y;
} g_body[LENGTH*WIDTH],*pHead,*pTail; 

void initEnv(){
	//init console
	initConsole(80,30);
	hideCursor();
	srand((unsigned)time(NULL));
	
	//init map data
	int i,j;
	for (i=0;i<LENGTH;i++){
		for(j=0;j<WIDTH;j++){
			if (j==0||j==WIDTH-1||
				i==0||i==LENGTH-1){
	
				g_map[i][j] = WALL;		
			}else{
				g_map[i][j] = BLNK;
			}
		}
	}
	
	//init body data
	g_body[0].x = WIDTH/2;
	g_body[0].y = LENGTH/2;
	g_body[1].x = WIDTH/2-1;
	g_body[1].y = LENGTH/2;
	g_body[2].x = WIDTH/2-2;
	g_body[2].y = LENGTH/2;
	pTail = &g_body[0];
	pHead = &g_body[INITLENGTH-1];
	for(i=0;i<INITLENGTH;i++){
		g_map[g_body[i].x][g_body[i].y] = BODY;
	}
	
	//init FOOD
	gFOOD();
	drawMap();
	
	return ;
}


//**************main***************入口函数 
int main(int argc, char *argv[])
{
	face();
	char ch;
	while ((ch=getch())!='q'){
		if(ch == '1'){
			startGame();
			face();
		}
		if(ch == '2'){
			system("cls");
			MessageBox(NULL,"本程序精工学习与交流使用。如果发现地图有问题，请将输入发改成英文输入。","码客社",MB_OK);
			face();
		}
	}
	
	return 0;
}

void startGame(){
	
	initEnv();
	// 这里是游戏逻辑循环。
	int score=0,level=1,count=0,sp=400;
	gScore(32,11,score);
	gScore(32,9,level);
	initPannel();
	
	char ch=KB_LEFT;
	static int prev_ch;
	while (1){
		if(kbhit())
		{
			ch =getch();
		}
		if (ch + prev_ch == 152){
			ch = prev_ch;	
		}
		int nextX=pHead->x,nextY=pHead->y;
		switch(ch){
			case KB_UP:{
				nextY--;
				break;
			}
			case KB_DOWN:{
				nextY++;
				break;	
			}
			case KB_LEFT:{
				nextX--;
				break;
			}
			case KB_RIGHT:{
				nextX++;
				break;
			}
			default:{
				continue;
			}
		}
		
		switch(g_map[nextX][nextY]){
			case WALL:case BODY:{			//dead!
				//you died.
				MessageBox(NULL,"Game over,you lose!","码客社",MB_OK);
				return ;
			}
			case FOOD:{
				//you ate a food
				pHead 		=	 g_body + (++pHead - g_body)%(LENGTH*WIDTH);
				pHead->x	=	 nextX;
				pHead->y	=	 nextY;
				g_map[nextX][nextY] = BODY;
				drawP(nextX,nextY);
				gFOOD();
				
				count++;
				score+=10;
				setColor(1);
				gScore(32,11,score);
				if(count==10 && sp>50){
					count-=10;
					sp-=50;
					level++;
					setColor(1);
					gScore(32,9,level);
				}
				break;
			}
			case BLNK:{
				//you snake
				pHead 		=	 g_body + (++pHead - g_body)%(LENGTH*WIDTH);
				pHead->x	=	 nextX;
				pHead->y	=	 nextY;
				g_map[nextX][nextY] = BODY;
				drawP(nextX,nextY);
				g_map[pTail->x][pTail->y] = BLNK;
				drawP(pTail->x,pTail->y);
				pTail = g_body + (++pTail - g_body)%(LENGTH*WIDTH);
				break;
			}
			default:{
				//there must be error if program runs here.
				return ;
			}
		}
		
		prev_ch = ch;
			
		Sleep(sp);
	}
	return ;
}


void face(){
	initConsole(130,30);
	system("title C语言控制台游戏---贪吃蛇-码客社demo");
	setColor(9);
	

	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("　　　　　　　　　■■■　　　　　　　　　　　　　　　　　　　　■■　　　　　　　　　　　　　■■■　　　　　　■■　　　　　　■\n");
	printf("　　　　　　　　■■■■■　　　　　　　　　　　　　　　　　　　■■■　　　　　　　　　　　　■■■　　　　　■■■■　　　　　■\n");
	printf("　　　　　　　　■■■■■■　　　　　　　　　　　　　　　　　　■■■　　　　　　　　　　　　■■■　　　　　　■■■　　　　　■\n");
	printf("　　　　　　　■■■　■■■■　　　　　　　　■■■■■■■　■■■　　　　■■■　　　　　　■■■　　■■■■■■■■■■■　■\n");
	printf("　　　　　■■■■■■■■■■■■　　　　　　■■■■■■■　■■■■■■■■■■　　　■■■■■■■■■■■■■■■■■■■　■\n");
	printf("　　　■■■■■　■■■　■■■■■■■■　　■■　　■■　■■■■■■■■■■■　　　■■■■■■■■■■　　　　　　■■■　■\n");
	printf("　■■■■■■■■■■■■■■■■■■■■　　■■　　■■■■■■　　　　　　　　　　　■■　■■　■■■■　　　　　　■■■　■\n");
	printf("　　■■■■■■■■■■■■■■　■■■　　　■■　　■■■■■■■■■■■■　　　　　■■　■■　■■■■■■■　　　■■■　■\n");
	printf("　　　　　　　　　　　　■■■　　　　　　　　■■　　■■■■■■■■■■■■　　　　　■■　■■　■■　　■■■　　　　　　　■\n");
	printf("　　　　　　　　　　　■■■■　　　　　　　　■■　　■■　　■■■■■■■■　　　　　■■　■■　■■　　■■　　　■■■　　■\n");
	printf("　　　　　■■■■■■■■■■■■■　　　　　■■　　■■　　　　　■■■■　　　　　　■■■■■■■■■　■■　■■■■■　　■\n");
	printf("　　　　　■■■■■■■■■■■■■　　　　　■■　　■■　　　　■■■■　　　　　　　■■■■■■■■■　■■■■■■　　　　■\n");
	printf("　　　　　■■　　　■■　　　■■　　　　　　■■■■■■　　　■■■■　　　　　　　　■■　■■　■■■　■■■■■　　　　　■\n");
	printf("　　　　　■■　　■■■　　　■■■　　　　　■■■■■■■　　■■■　　　　　　　　　■■　■■　■■■　■■■　　　　　　　■\n");
	printf("　　　　　■■　　■■■　■　■■■　　　　　■■　　■■■　■■■　　　　　■■　　　　　　■■　■■■　■■　　　　　　　　■\n");
	printf("　　　　　■■　■■■　■■■■■　　　　　　■■　　■■■　■■　　　　　　■■■　　　■■■■■■■■■■■　　　　■■■　■\n");
	printf("　　　　　■■■■■■　■■■■■■　　　　　■■　　　　　■■■■■■■■■■■　　■■■■■■■■■■■■■■■■■■■■　■\n");
	printf("　　　■■■■■■■　　　　■■■■■　　　　　　　　　　　　■■■■■■■■■■　　　■■■　　　　■　　■■■■■■■■　　■\n");
	printf("　　　■■■■■　　　　　　　　■■　　　　　　　　　　　　　　■■■■■■■　　　　　　　　　　　　　　　　■■■■■■　　　■\n");
	printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

	
	
	setColor(4);
	setPos(25,10);
	printf("--------------------\n");
	setPos(25,11);
	printf("|    1.开始游戏     |\n");
	setPos(25,12);
	printf("|    2.关于游戏     |\n");
	setPos(25,13);
	printf("|    Q.退出游戏     |\n");
	setPos(25,14);
	printf("--------------------\n");
	
	setPos(0,30); 
	return ;
}

void initPannel(){
	setColor(8);
	setPos(32,4); 
	printf("码客社");
	setPos(32,8);
	printf("Level");
	setPos(32,10);
	printf("Score"); 
}
void gScore(int x,int y,int s){
	setColor(4);
	setPos(x,y);
	printf("%d",s);
	return ;
}

void gFOOD(){

	int seed = rand()%(WIDTH*(LENGTH-1))+WIDTH;
	int y = seed/WIDTH;
	int x = seed%WIDTH;
	if (g_map[x][y] == BLNK){
		g_map[x][y] = FOOD;
		drawP(x,y);
	}else{
		gFOOD();
	}
	return ;
}

void drawMap(){
	int i,j;
	for (i=0;i<LENGTH;i++){
		for(j=0;j<WIDTH;j++){
			drawP(i,j);
		}
	}
	return;
}

void drawP(int i,int j){
	setPos(i,j);
	setColor(C[g_map[i][j]].color);
	printf("%s",C[g_map[i][j]].c);
	return ;
}

void setPos(int x,int y){
	COORD cd;
	cd.X = x*2;
	cd.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cd);
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
	HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hd,c);
	return ;
}

void initConsole(int width,int height){
	char cmd[100];
	sprintf(cmd,"mode con cols=%d lines=%d",width,height);
	system(cmd);
	return ;
}

void hideCursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cur_info;
	GetConsoleCursorInfo(handle,&cur_info);
	cur_info.bVisible = FALSE;
	SetConsoleCursorInfo(handle,&cur_info);
	return;
}


