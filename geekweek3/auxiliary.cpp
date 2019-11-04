
#include "auxiliary.h"

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
void randonNumsGenerate(int *a,int n){
	srand(time(NULL));
	const int max = 99;
	const int min = 1;
	for(int i=0;i<n;i++){
		*a = rand() % (max-min+1)+min;
		a++;
	}
}

void clearLine(int y){
	setPos(0,y);
	for(int i=0;i<80;i++){
		putchar(' ');
	}
	setPos(0,y);
}

void printC(const char *s,int c){
	setColor(c);
	printf("%s",s);	
	setColor(white);
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
	while (root!=NULL && root->next != NULL) {
		length++;
		root = root->next;
	}
	return length;
}


