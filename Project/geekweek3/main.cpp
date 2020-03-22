#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "auxiliary.h"
#include "malgorithm.h"

#define N 10  // test array size

enum SELECTION {
    M_SELECT = '0',
    M_BUCKET,
    M_BUBBLE,
    M_MERGE,
    M_QUICK,
    M_INSERT,
    M_SHELL,
    M_COUNT,
    M_RADIX,
    M_HEAP,
    M_MORE = 'm',
    M_EXIT = 'q'
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

    printC("\t\t0. ", blue);
    printC("Selection Sort\n", white);
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
    printC("\t\t8. ", blue);
    printC("Radix Sort\n", white);
    printC("\t\t9. ", blue);
    printC("Heap Sort\n", white);
    printC("\t\t______________\n", yellow);
    printC("\n\t\tm. ", blue);
    printC("More Detail\n", white);
    printC("\t\tq. ", blue);
    printC("Exit\n", white);
    printLine('-', purple);

    setPos(0, _CONSOLE_LINES_ - 4);
    printC("\t\tBy Jack Li\n\t\t", lightShadowGreen);
    printC(__DATE__, shadowGreen);
    printC("\n\tMore algorithms to be added", grey);
    //printC(__TIME__, lightBright);

    int opt;
    while (true) {
        opt = _getch();
        switch (opt) {
            case M_SELECT:
            case M_BUBBLE:
            case M_BUCKET:
            case M_MERGE:
            case M_QUICK:
            case M_INSERT:
            case M_SHELL:
            case M_COUNT:
            case M_RADIX:
            case M_MORE:
            case M_HEAP:
            case M_EXIT:
                return opt;

            default:  // not handle
                continue;
        }
    }
}
void algorithmHandler(int select) {
    int a[N];                  //stack may not have enough space if N is very large
    randomNumsGenerate(a, N);  // important!
    if (select == M_SELECT) {
        selectionSort(a, N);
    } else if (select == M_BUBBLE) {  // !!! do not use switch here !!!
        bubbleSort(a, N);
    } else if (select == M_BUCKET) {
        bucketSort(a, N);
    } else if (select == M_MERGE) {
        mergeSort(a, N);
    } else if (select == M_QUICK) {
        cls();
        initConsole(80, 60);
        quickSort(a, 0, N - 1);
        setColor(green);
        printf("���Ӷ�a=O(NlogN) ���ȶ�\n");
        setColor(white);
        _getch();
        initConsole(_CONSOLE_COLUMNS_, _CONSOLE_LINES_);

    } else if (select == M_INSERT) {
        insertSort1(a, N);
        //insertSort2(a, N);  //this one used a linked list
    } else if (select == M_SHELL) {
        cls();
        shellSort(a, N);
        _getch();
    } else if (select == M_COUNT) {
        countingSort(a, N);
    } else if (select == M_RADIX) {
        radixSort(a, N);
    } else if (select == M_MORE) {
        // here open my github reposition where I have written detailed information about those algorithms with false code
        ShellExecute(NULL, NULL, TEXT("https://github.com/dreamer2q/learnCpp/tree/master/geekweek3"), NULL, NULL, 1);
    } else if (select == M_HEAP) {
        heapSort(a, N);
    }
}

int main() {
    init();
    int ret;
    while ((ret = menu()) != M_EXIT) {  //the main loop, loop forever if ......
        algorithmHandler(ret);
    }
    bye();
    return 0;
}
