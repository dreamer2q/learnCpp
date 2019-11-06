#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>

#include "auxiliary.h"
#include "algorithm.h"


#define N 10 // test array size

enum SELECTION {
	M_EXIT=0,M_BUCKET, M_BUBBLE, M_MERGE,M_QUICK,M_INSERT,M_COUNT,
	M_SHELL,
	M_MORE=9
};

void init() {
	hideCursor();
	setTitle("Sort Algorithms Teaching Demo");
	initConsole(_CONSOLE_COLUMNS_, _CONSOLE_LINES_);
	srand(time(NULL));
}

int menu() {
	cls();
	printC("\t\tSort Algorithms Demo\n", red);
	printLine('-', purple);

	printC("\t\t1. ", blue);
	printC("Bucket Sort\n", white);
	printC("\t\t2. ", blue);
	printC("Bubble Sort\n", white);
	printC("\t\t3. ", blue);
	printC("Merge  Sort\n", white);
	printC("\t\t4. ", blue);
	printC("Quick  Sort\n", white);
	printC("\t\t5. ", blue);
	printC("Insert Sort\n", white);
	printC("\t\t6. ", blue);
	printC("Shell  Sort\n", white);
	printC("\t\t7. ", blue);
	printC("Counting Sort\n", white);
	printC("\t\t______________\n", yellow);
	printC("\n\t\t9. ", blue);
	printC("More Detail\n", white);
	printC("\t\t0. ", blue);
	printC("Exit\n", white);
	printLine('-', purple);


	setPos(0, _CONSOLE_LINES_ - 4);
	printC("\t\tBy Jack Li\n\t\t",lightShadowGreen);
	printC(__DATE__, shadowGreen);
	printC("\n\tMore algorithms to be added", grey);
	//printC(__TIME__, lightBright);

	int opt;
	while (true) {
		opt = _getch() - '0';
		switch (opt) {
		case M_BUBBLE:
		case M_BUCKET:
		case M_MERGE:
		case M_QUICK:
		case M_INSERT:
		case M_SHELL:
		case M_COUNT:
		case M_MORE:
		case M_EXIT:return opt;

		default: // not handle
			continue;
		}
	}
}
void algorithmHandler(int select){
	int a[N];
	randomNumsGenerate(a, N); // important!

	if (select == M_BUBBLE) {  // !!! do not use switch here !!!
		bubbleSort(a, N);
	}
	else if (select == M_BUCKET) {
		bucketSort(a, N);
	}
	else if (select == M_MERGE) {
		mergeSort(a, N);
	}
	else if (select == M_QUICK) {
		cls();
		printN(a, N);
		quickSort(a,0, N-1);
		printN(a, N);
		printf("\n");

		randomNumsGenerate(a, N);
		printN(a, N);
		quickSort(a,0, N - 1);
		printN(a, N);
		printf("\n");

		randomNumsGenerate(a, N);
		printN(a, N);
		quickSort(a,0, N - 1);
		printN(a, N);
		_getch();
	}
	else if (select == M_INSERT) {
		cls();
		printN(a, N);
		insertSort1(a, N);
		printN(a, N);
		printf("\n");
		randomNumsGenerate(a, N);
		printN(a, N);
		insertSort2(a, N);
		printN(a, N);
		_getch();
	}
	else if (select == M_SHELL) {
		cls();
		printf("Shell Sort\n");
		printN(a, N);
		shellSort(a, N);
		printN(a, N);
		_getch();
	}
	else if (select == M_COUNT) {
		cls();
		printf("Counting Sort\n");
		printN(a, N);
		countingSort(a, N);
		printN(a, N);
		_getch();
	}
	else if (select == M_MORE) {
		// todo ...
		ShellExecute(NULL, NULL, TEXT("https://github.com/dreamer2q/learnCpp/tree/master/geekweek3"), NULL, NULL, 1);
	}
	else {
		// not handle
	}
}
void bye() {
	//todo

	_getch();
}
int main(){
	init();
	int ret;
	while ((ret = menu()) != M_EXIT) {
		algorithmHandler(ret);
	}
	bye();
	return 0;
}
