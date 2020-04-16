
#include <conio.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "auxiliary.h"
#include "malgorithm.h"

void radixSort(int* a, int n) {
    int max = getMaxIn(a, n);
    int digits = 1;
    while (max /= 10) {
        digits++;
    }

    for (int i = 0; i < digits; i++) {
        cls();
        setColor(white + i);
        printN(a, n);
        printf("\n");
        for (int j = 0; j < 10; j++) {
            for (int z = 0; z < digits; z++) {
                if (z == i) {
                    printf("_");
                } else {
                    printf("%d", j);
                }
            }
            printf(" <= \n");
        }

        Array arr[10];
        for (int j = 0; j < 10; j++) {
            arr[j] = makeArray();
        }
        for (int j = 0; j < n; j++) {
            int index = (a[j] % _pow(10, i + 1)) / _pow(10, i);
            setColor(green);
            setPos(j * 4 + 3 - i, 1);
            printf("I");

            insertElementByOrder(arr[index], a[j]);
            int length = getArrayLength(arr[index]);
            setColor(green);
            setPos(6, index + 2);
            for (int z = 0; z < length; z++) {
                printf("%2d ", getArrayAt(arr[index], z));
            }
            _getch();
        }
        int index = 0;
        setPos(0, 13);
        setColor(red);
        printf("Output(%d/%d) => [ ", i + 1, digits);
        setColor(green);
        for (int j = 0; j < 10; j++) {
            int length = getArrayLength(arr[j]);
            for (int z = 0; z < length; z++) {
                a[index++] = getArrayAt(arr[j], z);
                printf("%2d ", a[index - 1]);
                _getch();
            }
            deleteArray(arr[j]);
        }
        setColor(red);
        printf("]");
        _getch();
    }
    printf("复杂度a=O(N*k) 稳定\n");
    _getch();
}

void buildMaxHeap(int* a, int n) {
    for (int i = n / 2; i >= 0; i--) {
        heapify(a, n, i);
    }
}
void heapify(int* a, int n, int node) {
    int l = node * 2 + 1;
    int r = node * 2 + 2;
    int max = node;
    if (l < n && a[l] > a[max]) {
        max = l;
    }
    if (r < n && a[r] > a[max]) {
        max = r;
    }
    if (max != node) {
        swap(a, max, node);
        heapify(a, n, max);
    }
}

void heapSort(int* a, int n) {
    initConsole(80, 40);
    setColor(red);
    printN(a, n);

    showHeap(a, n, 0, 2, 40);
    _getch();
    buildMaxHeap(a, n);
    showHeap(a, n, 0, 2, 40);
    _getch();

    for (int i = n - 1; i > 0; --i) {
        swap(a, 0, i);
        heapify(a, i, 0);
        showHeap(a, n, 0, 2, 40);
        setPos(0, 0);
        printN(a, n);
        _getch();
    }

    setPos(0, 13);
    printf("复杂度a=O(NlogN) 不稳定\n");
    _getch();
    initConsole(_CONSOLE_COLUMNS_, _CONSOLE_LINES_);
}

void countingSort(int* a, int n) {
    cls();
    int max = getMaxIn(a, n);
    max++;  // ensure there is enough space

    printN(a, n);
    printf("\n");

    int* pos = (int*)malloc(sizeof(int) * max);
    bool flag = true;
    for (int i = 0, j = 0; i <= max; i++) {
        if (isInArray(i, a, n)) {
            printf("[ %2d ] => 0\n", i);
            flag = true;
            pos[i] = j++;
        } else if (flag) {
            printf("...\n");
            flag = false;
            j++;
        }
    }
    _getch();

    int* ret = (int*)malloc(sizeof(int) * max);
    memset(ret, 0, sizeof(int) * max);
    if (NULL == ret) {
        fprintf(stderr, "Malloc Error");
        return;
    }

    for (int i = 0; i < n; i++) {
        ret[a[i]]++;
        setPos(4 * i + 3, 1);
        printf("I");
        setPos(10, pos[a[i]] + 2);
        printf("%d", ret[a[i]]);
        _getch();
    }
    int index = 0;
    for (int i = 0; i < max; i++) {
        while (ret[i] > 0) {
            a[index] = i;
            ret[i]--;
            index++;
        }
    }
    free(ret);

    setPos(0, pos[max - 1] + 5);
    setColor(green);
    printN(a, n);
    printf("复杂度a=O(N+k) 稳定\n");
    setColor(white);
    _getch();
    free(pos);
}

void shellSort(int* a, int n) {
    cls();
    initConsole(80, 40);
    printf("Starting ShellSort\n");

    for (int gap = n / 2; gap > 0; gap /= 2) {
        printf("Divide into groups with gap = %d\n", gap);
        printN(a, n);
        for (int i = gap; i < n; i++) {
            int j = i;
            int cur = a[j];
            printf("process %2d => result => ", cur);
            while (j - gap >= 0 && cur < a[j - gap]) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = cur;
            printN(a, n);
        }
        printf("Next divide\n\n");
    }
    printf("\nFinished");
    printN(a, n);
    setColor(green);
    printf("复杂度a=O(N^1.3) 不稳定\n");
    setColor(white);
    _getch();
    initConsole(_CONSOLE_COLUMNS_, _CONSOLE_LINES_);
}

void selectionSort(int* a, int n) {
    cls();
    setColor(red);
    printN(a, n);
    setColor(white);
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (a[min] > a[j]) {
                min = j;
            }
        }
        printf("[ ");
        for (int j = 0; j < n; j++) {
            setColor(j < i ? green : white);
            if (j == min) {
                setColor(red);
            }
            printf("%2d ", a[j]);
        }
        setColor(white);
        printf("]\n");
        if (i != min) {
            int t = a[min];
            a[min] = a[i];
            a[i] = t;
        }
    }
    setColor(green);
    printN(a, n);
    printf("复杂度a=O(N^2) 不稳定\n");
    setColor(white);
    _getch();
}
void insertSort1(int* a, int n) {  //based on array
    cls();
    int* ret = (int*)malloc(sizeof(int) * n);
    if (ret == NULL) {
        fprintf(stderr, "Malloc failed\n");
        return;  //shit! how could it go wrong?!/@?
    }
    memcpy(ret, a, sizeof(int) * n);
    memset(a, 0, sizeof(int) * n);  //here assume that no number is less than zero Or it will go wrong.

    printN(ret, n);
    printf("[  ]\n");
    int length = 0;
    for (int i = 0; i < n; i++) {
        int index = 0;
        for (int j = 0; j < length; j++) {
            if (ret[i] >= a[j]) {
                index++;
            }
        }
        setColor(blue);
        printf("%2d", ret[i]);
        setColor(white);
        printf(" => [ ");
        for (int j = 0; j <= index; j++) {
            if (j == index) {
                setColor(red);
                printf(" _ ");
            } else {
                setColor(green);
                printf("%2d ", a[j]);
            }
        }

        for (int j = n - 1; j > index; j--) {
            a[j] = a[j - 1];
        }
        a[index] = ret[i];
        length++;
        setColor(green);
        for (int j = index + 1; j < length; j++) {
            printf("%2d ", a[j]);
        }
        setColor(white);
        printf("]\n");
    }
    free(ret);

    setColor(green);
    printN(a, n);
    printf("复杂度a=O(N^2) 稳定\n");
    _getch();
}
void insertSort2(int* a, int n) {  //based on Linked list tidy and nice
    Array ret = makeArray();
    for (int i = 0; i < n; i++) {
        insertElementByOrder(ret, a[i]);
    }
    int length = getArrayLength(ret);
    for (int i = 0; i < length; i++) {
        a[i] = getArrayAt(ret, i);
    }
    deleteArray(ret);
}

int* _merge(int* left, int nleft, int* right, int nright) {
    int* mleft = (int*)malloc(sizeof(int) * nleft);
    int* mright = (int*)malloc(sizeof(int) * nright);
    int *ml = mleft, *mr = mright;
    memcpy(mleft, left, sizeof(int) * nleft);
    memcpy(mright, right, sizeof(int) * nright);
    int* ret = left;

    while (nleft > 0 && nright > 0) {
        if (*mleft <= *mright) {
            *ret = *mleft;
            mleft++;
            nleft--;
        } else {
            *ret = *mright;
            mright++;
            nright--;
        }
        ret++;
    }
    while (nleft > 0) {
        *ret = *mleft;
        mleft++;
        nleft--;
        ret++;
    }
    while (nright > 0) {
        *ret = *mright;
        mright++;
        nright--;
        ret++;
    }
    free(ml);
    free(mr);
    return left;
}
int* _mergeSort(int* a, int n) {
    static int indexy = 1;
    if (n <= 1) {
        return a;
    }
    int mid = n / 2;

    _getch();
    printf("\nSort:");
    indexy += 2;
    setColor(red);
    printN(a, n);
    setColor(white);
    _getch();
    printf("L&R:");
    indexy++;
    _getch();
    printN(a, mid, 1);
    _getch();
    printN(a + mid, n - mid);
    //_getch();

    int* ml = _mergeSort(a, mid);
    int* mr = _mergeSort(a + mid, n - mid);

    printf("Return:");
    indexy++;
    _getch();
    int* ret = _merge(ml, mid, mr, n - mid);

    setColor(green);
    printN(ml, n);
    setColor(white);

    _getch();

    clearLine(--indexy);
    clearLine(--indexy);
    clearLine(--indexy);
    clearLine(--indexy);

    return ret;
}
int* mergeSort(int* a, int n) {
    cls();
    printC("\t\tMerge Sort\n", red);
    int* ret = _mergeSort(a, n);
    setColor(green);
    printN(a, n);
    printC("复杂度a=O(NlogN) 稳定\n", yellow);
    _getch();
    return ret;
}

void bubbleSort(int* a, int n) {
    cls();

    static int index = 0;
    printf("\t\tBubble Sort\n");
    //printN(a,n);
    index++;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            printf("[ ");
            for (int z = 0; z < n; z++) {
                if (z == j || z == j + 1) {
                    setColor(red);
                } else if (z > n - i - 1) {
                    setColor(green);
                } else {
                    setColor(white);
                }
                printf("%2d ", a[z]);
            }
            setColor(white);
            printf("]\n");
            setPos(3 + 3 * j, 2);
            printC("I__I", blue);
            if (a[j] > a[j + 1]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
            _getch();
            clearLine(2);
            clearLine(1);
        }
    }

    printf("[ ");
    setColor(green);
    for (int z = 0; z < n; z++) {
        printf("%2d ", a[z]);
    }
    setColor(white);
    printf("]\n");

    setColor(yellow);
    setPos(0, 2);
    printf("复杂度a=O(N^2) 稳定\n");
    _getch();
    setColor(white);
}

void bucketSort(int* a, int n) {
    Array bucket[10] = {0};  //assume the value is no more than 100
    cls();
    printN(a, n);

    for (int i = 0; i < 10; i++) {
        setPos(0, 2 + i);
        printf("Bucket[%d] = none\n", i);
    }
    _getch();
    for (int i = 0; i < n; i++) {
        int index = a[i] / 10;
        clearLine(1);
        setPos(3 + i * 4, 1);
        printC("I", red);
        setPos(2 + i * 4, 0);
        setColor(black);
        printf("%2d", a[i]);
        setColor(white);
        if (bucket[index] == NULL) {
            bucket[index] = makeArray();  //assume no error occurs
        }
        insertElementByOrder(bucket[index], a[i]);
        clearLine(index + 2);
        printf("Bucket[%d] = [ ", index);
        setColor(green);
        int length = getArrayLength(bucket[index]);
        for (int j = 0; j < length; j++) {
            printf("%2d ", getArrayAt(bucket[index], j));
        }
        setColor(white);
        printf("]");
        _getch();
    }

    setPos(0, 14);
    printf("[ ");
    int index = 0;
    for (int i = 0; i < 10; i++) {
        if (bucket[i] != NULL) {
            int length = getArrayLength(bucket[i]);
            for (int j = 0; j < length; j++) {
                a[index++] = getArrayAt(bucket[i], j);
                setPos(14 + j * 3, 2 + i);
                setColor(black);
                printf("%2d", a[index - 1]);
                setPos(-1 + index * 3, 14);
                setColor(green);
                printf("%2d, ", a[index - 1]);
                setColor(white);
                _getch();
            }
            deleteArray(bucket[i]);  //remember to give back what we have asked
        }
    }
    printf("\b\b ]");
    setPos(0, 16);
    setColor(yellow);
    printf("复杂度a=O(N) 稳定\n");
    _getch();
    setColor(white);
}

void quickSort(int* a, int left, int right) {
    if (left < right) {
        setColor(lightShadowGreen);
        printf("Start QuickSort => ");
        printN(a + left, right - left + 1);

        int l = left;
        int r = right;
        int k = a[left];
        setColor(green);
        printf("\tNumbers less than ");
        setColor(red);
        printf("%d", k);
        setColor(green);
        printf(" are moved to the left of it\n");
        while (l < r) {
            while (l < r && k < a[r]) {
                r--;
            }
            if (l < r) {
                a[l] = a[r];
                l++;
            }
            while (l < r && a[l] <= k) {
                l++;
            }
            if (l < r) {
                a[r] = a[l];
                r--;
            }
        }
        a[l] = k;
        setColor(green);
        printf("\tMove result [ ");
        for (int i = 0; i < right - left + 1; i++) {
            if ((a + left)[i] == k) {
                setColor(red);
                printf("%2d ", k);
                setColor(white);
            } else {
                printf("%2d ", (a + left)[i]);
            }
        }
        printf("]\n");
        quickSort(a, left, l - 1);
        quickSort(a, l + 1, right);

        printf("End => ");
        printN(a + left, right - left + 1);
    }
    _getch();
}
