#include "ui_map.h"

void MAP::init(){
	memset(&m_map, 0, sizeof(m_map));
	memset(movements, 0, sizeof(movements));
	m_index_move = 0;
	m_winner = 0;
	curPlayer = 0;
}

void MAP::drawMap() { 	//size 15x15 = 225
	SetWorkingImage(m_img);

	drawBackground();
	drawOuterBorder();
	setlinestyle(0, 1);
	for (int i = 0; i < 15; i++) {
		line(40, 40 + i * gap, m_height - 42, 40 + i * gap);
		line(40 + i * gap, 40, 40 + i * gap, m_height - 42);
	}
	drawMapBlackDots();

	

	updateImg();
}

void MAP::putChess(int rows, int lines){
	if (inMap(rows,lines)) {
		if (m_map[rows][lines] == 0) {
			m_map[rows][lines] = getCurPlayer();

			movements[m_index_move++] = POSITION{ rows,lines };
			drawChess(rows, lines);
			updateImg();
			nextPlayer();

			updateWinner();
		}
	}
}

void MAP::unputChess(int rows, int lines){
	if (inMap(rows, lines)) {
		if (m_map[rows][lines] != 0) {
			m_map[rows][lines] = 0;
			clearChess(rows, lines);
			curPlayer--;
			updateImg();
		}
	}
}

void MAP::putChessRect(int rows, int lines){
	putimage(m_x, m_y, m_img);
	setfillcolor(BLACK);
	setorigin(10, 10);
	line(20 + rows * gap, 25 + lines * gap, 25 + rows * gap, 25 + lines * gap);
	line(35 + rows * gap, 25 + lines * gap, 40 + rows * gap, 25 + lines * gap);
	line(20 + rows * gap, 35 + lines * gap, 25 + rows * gap, 35 + lines * gap);
	line(35 + rows * gap, 35 + lines * gap, 40 + rows * gap, 35 + lines * gap);
	
	line(25 + rows * gap, 20 + lines * gap, 25 + rows * gap, 25 + lines * gap);
	line(35 + rows * gap, 20 + lines * gap, 35 + rows * gap, 25 + lines * gap);
	line(25 + rows * gap, 35 + lines * gap, 25 + rows * gap, 40 + lines * gap);
	line(35 + rows * gap, 35 + lines * gap, 35 + rows * gap, 40 + lines * gap);
	setorigin(0, 0);
}

void MAP::unputChessRect(){
	putimage(m_x, m_y, m_img);
}

void MAP::setAI(AI* p){
	m_ai = p;
}

int MAP::getCurPlayer(){
	return curPlayer % 2 ? 1 : 2;
}

int MAP::getWinner(){
	return m_winner;
}

POSITION MAP::getLastPosition(){
	return movements[m_index_move - 1];
}

void MAP::nextPlayer() {
	curPlayer++;
}

int MAP::hasWinner(){

	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (checkLines(i, j)) {
				return m_map[i][j];
			}
		}
	}

	if (isMapFull()) {
		return -1;
	}
	return 0;
}

RECT MAP::getRectText(int index){
	POSITION p = movements[index];
	return RECT{ 40 + p.x * gap - gap / 3,40 + p.y * gap - gap / 4,40 + p.x * gap + gap / 3,40 + p.y * gap + gap / 3 };
}

void MAP::takeBack(){
	if (m_index_move > 1) {
		POSITION pos1 = movements[--m_index_move];
		POSITION pos2 = movements[--m_index_move];
		unputChess(pos1.x, pos1.y);
		unputChess(pos2.x, pos2.y);
	}
}

int MAP::getCurIndexMove(){
	return m_index_move;
}

int(&MAP::getMap())[15][15]{
	return m_map;
}

bool MAP::isMapFull(){
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (m_map[i][j] == 0) {
				return false;
			}
		}
	}
	return true;
}

bool MAP::checkLines(int x,int y){
	int player = m_map[x][y];
	if (!player) {
		return false;
	}
	for (int i = 1; i < 5; i++) {
		if (x+i < 15 && player == m_map[x+i][y]) {
			if (i == 4) {
				return true;
			}
		}
		else {
			break;
		}
	}
	for (int i = 1; i < 5; i++) {
		if (y + i < 15 && player == m_map[x][y+i]) {
			if (i == 4) {
				return true;
			}
		}
		else {
			break;
		}
	}
	for (int i = 1; i < 5; i++) {
		if (y + i < 15 && x + i < 15 && player == m_map[x+i][y + i]) {
			if (i == 4) {
				return true;
			}
		}
		else {
			break;
		}
	}
	for (int i = 1; i < 5; i++) {
		if (0 < y - i && x + i < 15 && player == m_map[x + i][y - i]) {
			if (i == 4) {
				return true;
			}
		}
		else {
			break;
		}
	}
	return false;
}

void MAP::updateWinner(){
	m_winner = hasWinner();
}

MAP::MAP(int x, int y, int width, int height){
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_img = new IMAGE(width, height);
	m_pt = new IMAGE();
	loadimage(m_pt, L"map.png", m_width, m_height, true);
	gap = (m_height - 40) / 15;
}

MAP::~MAP() {
	delete m_img;
}

int MAP::getMapAt(int x, int y){
	return m_map[x][y];
}

bool MAP::inMap(int row, int line){
	return row >= 0 && row < 15 && line >= 0 && line < 15;
}

void MAP::drawChess(int x, int y){
	SetWorkingImage(m_img);
	setfillcolor(curPlayer % 2 ?  WHITE : BLACK);
	
	setfillstyle(BS_SOLID);
	fillcircle(40 + x * gap, 40 + y * gap, gap / 3);

	RECT recText = getRectText(curPlayer);
	settextcolor(RED);
	WCHAR num[10] = { 0 };
	wsprintf(num,L"%d",curPlayer+1);
	drawtext(num, &recText, DT_CENTER);
	
	if (curPlayer > 0) {
		settextcolor(curPlayer % 2 ? WHITE : BLACK);
		recText = getRectText(curPlayer - 1);
		wsprintf(num, L"%d", curPlayer );
		drawtext(num, &recText, DT_CENTER);
	}

	SetWorkingImage();
}

void MAP::clearChess(int x,int y){
	SetWorkingImage(m_img);
	setfillstyle(BS_DIBPATTERN, NULL, m_pt);
	solidrectangle(40 - gap / 3 + x * gap, 40 - gap / 3 + y * gap, 40 + gap / 3 + x * gap, 40 + gap / 3 + y * gap);
	setlinecolor(BLACK);
	setlinestyle(BS_SOLID);
	setorigin(40, 40);
	if (x == 0) {
		line(x * gap, y * gap, gap / 3 + x * gap, y * gap);
	}
	else if (x == 14) {
		line(-gap / 3 + x * gap, y * gap,  x * gap, y * gap);
	}
	else {
		line( - gap / 3 + x * gap,   y * gap,   gap / 3 + x * gap,  y * gap);
	}
	if (y == 0) {
		line(x * gap,  y * gap, x * gap, gap / 3 + y * gap);
	}
	else if (y == 14) {
		line(x * gap, -gap / 3 + y * gap, x * gap,  y * gap);
	}
	else {
		line(  x * gap,  - gap / 3 + y * gap, x * gap, gap / 3 + y * gap);
	}
	setorigin(0, 0);
	drawMapBlackDots();
}

void MAP::updateImg(){
	SetWorkingImage();
	putimage(m_x, m_y, m_img);
}

void MAP::drawMapBlackDots(){
	setfillstyle(BS_SOLID);
	setfillcolor(BLACK);
	int a[] = { 3,3,11,11,7 };
	int b[] = { 3,11,3,11,7 };
	for (int i = 0; i < 5; i++) {
		if (m_map[a[i]][b[i]] == 0) {
			fillcircle(40 + a[i] * gap, 40 + b[i] * gap, 3);
		}
	}
}

void MAP::drawBackground(){
	setfillstyle(BS_DIBPATTERN, NULL, m_pt);
	solidrectangle(0, 0, m_width - 0, m_height - 0);
}

void MAP::drawOuterBorder() {
	setlinecolor(BLACK);
	setlinestyle(0, 2);
	rectangle(10, 10, m_height - 10, m_height - 10);

	char t[] = "123456789ABCDEF";
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);

	RECT ct;
	for (int i = 0; i < 15; i++) {
		ct = RECT{ 35 + i * gap, 13,45 + i * gap ,30 };
		drawtext(t[i], &ct, DT_CENTER);
		ct = RECT{ 15 ,30 + i * gap, 30, 45 + i * gap };
		drawtext(t[i], &ct, DT_CENTER);
	}
}
