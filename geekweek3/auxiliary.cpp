
#include "auxiliary.h"

ULONGLONG _g_RecordingTimer_;  //applied when starTimer() is called

void setPos(int x,int y){
	COORD cd;
	cd.X = x;
	cd.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cd);
}

void setColor(int c){
	HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hd,c);
	return ;
}

void cls(){
	system("cls");
}

void setTitle(const char* title) {
	char buf[100];
	sprintf_s(buf, "title %s", title);
	system(buf);
}

void initConsole(int width,int height){
	char cmd[100];
	sprintf_s(cmd,"mode con cols=%d lines=%d",width,height);
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

void printN(int *a,int n,int enter){
	
	printf("[ ");
	for(int i=0;i<n;i++){
		printf("%2d, ",*a);
		a++;
	}
	printf("\b\b ]%c",enter == 0?'\n':' ');
	
}

void bye() {
	//todo
	MessageBoxA(NULL, "Unkonw Error!\nPress OK to restart your computer!", "ERROR", MB_OK | MB_ICONERROR);
	//_getch();
}

void randomNumsGenerate(int *a,int n){
	
	const int max = 99;
	const int min = 1;
	for(int i=0;i<n;i++){
		*a = rand() % (max-min+1)+min;
		a++;
	}
}

void clearLine(int y){
	setPos(0,y);
	for(int i=0;i<_CONSOLE_COLUMNS_;i++){
		putchar(' ');
	}
	setPos(0,y);
}
void printLine(char ch, int c) {
	setColor(c);
	for (int i = 0; i < _CONSOLE_COLUMNS_-1; i++) {
		putchar(ch);
	}
	putchar('\n');
	setColor(white);
}

void printC(const char *s,int c){
	setColor(c);
	printf("%s",s);	
	setColor(white);
}

int getMaxIn(int* a, int n) {
	int max = a[0];
	for (int i = 1; i < n; i++) {
		if (a[i] > max) {
			max = a[i];
		}
	}
	return max;
}

int _pow(int base, int n){
	int ret = 1;
	for (int i = 0; i < n; i++) {
		ret *= base;
	}
	return ret;
}

void startTimer(){
	_g_RecordingTimer_ = GetTickCount64();
}

ULONGLONG stopTimer(){
	return GetTickCount64() - _g_RecordingTimer_;
}

bool isInArray(int i, int* a, int n){
	for (int j = 0; j < n; j++) {
		if (i == a[j]) {
			return true;
		}
	}
	return false;
}

void swap(int* a, int i, int j){
	int tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}

void showHeap(int* a, int n,int i,int y,int x){
	//initConsole(80,40);
	static int times = 0;
	int l = i * 2 + 1;
	int r = i * 2 + 2;
	times++;
	if (i < n) {
		setPos(x, y);
		setColor(a[i] % 15 + 1);
		printf("%2d", a[i]);
	}
	if (l < n) {
		showHeap(a, n, l, y + 1 + times, x - 15/times);
	}
	if (r < n) {
		showHeap(a, n, r, y + 1 + times, x + 15/times);
	}
	times--;
}

Array makeArray(){
	Array ret = (Array)malloc(sizeof(struct tagArray));
	if (ret != NULL) {
		memset(ret, 0, sizeof(struct tagArray));
	}
	return ret;
}
Array insertElementByOrder(Array root, int value){
	if (root == NULL) {
		return NULL;
	}
	Array pos = root;
	while (root != NULL && root->value < value) {
		pos = root;
		root = root->next;
	}
	Array n = (Array)malloc(sizeof(struct tagArray));
	if (n == NULL) {
		return NULL;
	}
	n->value = value;
	n->next = root;
	pos->next = n;
	return n;
}
Array deleteArray(Array root) {
	while (root != NULL) {
		Array tmp = root->next;
		free(root);
		root = tmp;
	}
	return root;
}
int getArrayAt(Array root, int position) {
	if (position < 0 || position >= getArrayLength(root)) {
		return -1;
	}
	int p = 0;
	root = root->next;  //skip the root node
	while (p < position) {
		root = root->next;
		p++;
	}
	return root->value;
}
int getArrayLength(Array root){
	int length = 0;
	while (root != NULL && root->next != NULL) {
		length++;
		root = root->next;
	}
	return length;
}


