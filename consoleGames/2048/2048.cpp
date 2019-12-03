


//2048 С��Ϸ
// 2019/9  Jack Li

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <math.h>
#include <time.h>

#define WIDTH 4   //����2048�ĵ�ͼ��С�������޸Ŀ�Ч�������
#define HEIGHT WIDTH

int _maps[WIDTH][HEIGHT]; //�����Ǻ������ݣ���š�����



int showMenu();
void showAbout();
void startGame();
void gameLoop();
void initMaps();
void printMaps();
bool addNumber();
void setColor(int color);
void setPos(int x, int y);
void hideCursor();
void rotate(int maps[HEIGHT][WIDTH]);
void moveUp();
void moveDown();
void moveLeft();
void moveRight();

int main() {

	while (1) {
		int rVal = showMenu();
		switch (rVal)
		{
		case 1: //start game
			startGame();
			break;

		case 2: //show about
			showAbout();
			break;

		case 0: //exit
			return 0;
			break;

		default: //do nothing
			break;
		}
	}
	return 0;
}

int showMenu() {  //���ǲ˵�
	hideCursor();

	setColor(3);
	system("cls");
	system("mode con cols=40 lines=20");
	printf(" -------------2048---------------\n");
	printf("|	1.Start Game		|\n");
	printf("|	2.About			|\n");
	printf("|	0.Exit			|\n");
	printf(" --------------------------------\n");


	char r = _getch();
	return r - '0';
}

void initMaps() {  //��ӡ��ͼ
	system("cls");
	system("mode con cols=40 lines=20");

	for (int i = 0; i < HEIGHT; ++i) {
		printf("---------------------------------\n");
		for (int j = 0; j < WIDTH - 1; ++j) {
			printf("|	|	|	|	|\n");
		}
	}
	printf("---------------------------------\n");
	return;
}
void printMaps() {
	for (int y = 1; y <= HEIGHT; ++y) {
		for (int x = 1; x <= WIDTH; ++x) {
			setPos(x, y);
			printf("    ");
			setPos(x, y);
			int c = 0;
			
			switch (_maps[y - 1][x - 1]) { //ѡ�����ֵ���ɫ
			case 0:c = 8; break;
			case 2:c = 7; break;
			case 4:c = 1; break;
			case 8:c = 2; break;
			case 16:c = 6; break;
			case 32:c = 13; break;
			case 64:c = 12; break;
			case 128:c = 11; break;
			case 256:c = 10; break;
			case 512:c = 15; break;
			case 1024:c = 4; break;
			case 2048:c = 5; break;
			default:c = 1;
			}

			setColor(c);
			if (_maps[y - 1][x - 1]) {
				printf("%d", _maps[y - 1][x - 1]);
			}
			else {
				printf("    ");
			}

		}
	}
	return;
}

void startGame() {
	initMaps();
	gameLoop();
	MessageBox(NULL, TEXT("I am sorry to tell you that you lose!"), TEXT("ʧ��"), MB_OK);
}
void initData() {
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			_maps[y][x] = 0;
		}
	}
	time_t t;
	srand((unsigned)time(&t));
}
bool addNumber() {
	int count = 0;  //�жϵ�ͼ�Ƿ��ܷ����µ�������������ٷ�������˵��û��·�����ˣ�����Ϸ������
					//ͬʱ������Խ�����Ϸ�����ļ��㣬������û��Ū��
	for (int y=0; y < HEIGHT; ++y){
		for (int x=0; x < WIDTH; ++x) {
			count += _maps[y][x] ? 1 : 0;
		}
	}
	if (count == WIDTH * HEIGHT) {
		return false;
	}
	while (true) {
		int r = rand() % 16;
		int y = r / 4;
		int x = r % 4;
		if (!_maps[y][x]) {
			_maps[y][x] = rand() % 2 ? 2 : 4;
			return true;
		}
	}
}
void gameLoop() {
	initData();
	addNumber();
	addNumber();
	printMaps();

	char key;
	while(key = _getch()){
		//up :72 down:80 left:75 right:77
		switch (key)
		{
		case -32:continue; //��֪��Ϊ�λ���� -32 �ļ����룬���ｫ�����Σ�����Ӱ�졣

		case 72: //up
			moveUp();
			break;

		case 80: //down
			moveDown();
			break;

		case 75: //left
			moveLeft();
			break;
		case 77: //right
			moveRight();
			break;
		
		default:
			continue;
		}
		if (!addNumber()) {
			//������Ϸ������
			return;
		}
		printMaps();
	}
}

void moveLine(int *a,int s) {  //�����������ƶ�һ��λ�ã�s�����ƶ�����ʼλ�á�
	for (; s < WIDTH - 1; ++s) {
		a[s] = a[s + 1];
	}
	a[s] = 0;
	return;
}
void moveLeft() {

	/*
		������������Ϸ�ĺ��Ĳ���
		������д�Ĳ��ã��߼����ң�������������Ĵ������д�Ĳ���������ˡ�

		***2048�ѵ��������ֵĺϲ�
			˼·��
			ֻ�������ߺϲ��Ĵ��룬�������������ͨ���������ת����������ʱ�뷽����תһ��������֮��������ϲ����ٽ���ת��
			����ԭ����ʵ��������������������ƶ����ϲ���

	*/

	for (int y = 0; y < HEIGHT; ++y) {
		if (!(_maps[y][0] + _maps[y][1] + _maps[y][2] + _maps[y][3])) { //�ж���һ���Ƿ������ݣ�û�о����������������˵�ͼ�Ĵ�С
			continue;
		}
		for (int tmp = 0; tmp < WIDTH; ++tmp) { //�����Ū�˲���Ҫ��ѭ����Ŀ����ȷ��������ȫ���ƶ������
			for (int i = 0; i < WIDTH; ++i) {
				if (!_maps[y][i]) {
					moveLine(_maps[y], i);
				}
			}
		}
		for (int i = 0; i < WIDTH-1 ; ++i) {  //�����Ǻϲ��Ĵ��룬ǰ���ǡ�����ȫ����ߡ�
			if (!_maps[y][i]) {
				break;
			}
			if (_maps[y][i] == _maps[y][i + 1]) {
				_maps[y][i] += _maps[y][i + 1];
				moveLine(_maps[y], i+1);
			}
		}
	}
}
void moveUp() {
	rotate(_maps);
	rotate(_maps);
	rotate(_maps);
	moveLeft();
	rotate(_maps);
}
void moveDown() {
	rotate(_maps);
	moveLeft();
	rotate(_maps);
	rotate(_maps);
	rotate(_maps);
}
void moveRight() {
	rotate(_maps);
	rotate(_maps);
	moveLeft();
	rotate(_maps);
	rotate(_maps);
}
void rotate(int a[HEIGHT][WIDTH]) {  //������˳ʱ����ת90��
	int tmp[HEIGHT][WIDTH];
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			tmp[i][j] = a[i][j];
		}
	}
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			a[i][j] = tmp[HEIGHT - j -1][i];
		}
	}
	return;
}

void showAbout() {

	MessageBox(NULL, TEXT("���д���д�����������������������~+����#����"),TEXT("ABOUT"),MB_OK);
	return;
}

void setColor(int color) {  //�����ַ���ɫ
	/*
	��Ӧ����ɫ����
	1. 0 = ��ɫ       8 = ��ɫ
	1 = ��ɫ       9 = ����ɫ
	2 = ��ɫ       10 = ����ɫ
	3 = ǳ��ɫ     11 = ��ǳ��ɫ
	4 = ��ɫ       12 = ����ɫ
	5 = ��ɫ       13 = ����ɫ
	6 = ��ɫ       14 = ����ɫ
	7 = ��ɫ       15 = ����ɫ
	*/

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoleHandle, color);
	return;
}
void setPos(int x, int y) {  //���ù�������
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = x*8-5;
	coord.Y = y*4-2;
	SetConsoleCursorPosition(consoleHandle, coord);
	return;
}
void hideCursor() {  //������̨�Ĺ�����أ���������
	HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(hd, &info);
	info.bVisible = false;
	SetConsoleCursorInfo(hd, &info);
	return;
}



