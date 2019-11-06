
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <conio.h>

#include "auxiliary.h"


void pBubbleSort() {
	printf("���Ӷ�a=O(N^2) �ȶ�\n");
	_getch();
}
void pBucketSort() {
	printf("���Ӷ�a=O(N) �ȶ�\n");
	_getch();
}

void shellSort(int* a, int n) {

	for (int gap = n / 2; gap > 0; gap /= 2) {
		
		for (int i = gap; i < n; i++) {

			int j = i;
			int cur = a[j];
			while (j - gap >= 0 && cur < a[j - gap]) {
				a[j] = a[j - gap];
				j -= gap;
			}
			a[j] = cur;
		}
	}
}


void selectionSort(int* a, int n) {

	for (int i = 0; i < n - 1; i++) {
		int min = i;
		for (int j = i+1; j < n; j++) {
			if (a[min] > a[j]) {
				min = j;
			}
		}
		if (i != min) {
			int t = a[min];
			a[min] = a[i];
			a[i] = t;
		}
	}
}
void insertSort1(int* a, int n) { //based on array
	int* ret = (int*)malloc(sizeof(int) * n);
	if (ret == NULL) {
		fprintf(stderr, "Malloc failed\n");
		return;			//shit! how could it go wrong?!/@?
	}
	memcpy(ret, a, sizeof(int) * n);
	memset(a, 0,sizeof(int)*n);
	int length = 0;
	for (int i = 0; i < n; i++) {
		int index = 0;
		for (int j = 0; j < length; j++) {
			if (ret[i] >= a[j]) {
				index++;
			}
		}
		for (int j = n - 1; j > index; j--) {
			a[j] = a[j - 1];
		}
		a[index] = ret[i];
		length++;
	}
	free(ret);
}

void insertSort2(int *a,int n) { //based on Linked list tidy and nice
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

int* _merge(int *left,int nleft,int *right,int nright){
	
	int *mleft = (int*)malloc(sizeof(int)*nleft);
	int *mright = (int*)malloc(sizeof(int)*nright);
	int *ml=mleft,*mr = mright;
	memcpy(mleft,left,sizeof(int)*nleft);
	memcpy(mright,right,sizeof(int)*nright);
	int *ret = left;
		
	while(nleft > 0 && nright > 0){
		if (*mleft <= *mright){
			*ret = *mleft;
			mleft++;
			nleft--;
		}else{
			*ret = *mright;
			mright++;
			nright--;
		}
		ret++;
	}
	while(nleft>0){
		*ret = *mleft;
		mleft++;
		nleft--;
		ret++;
	}
	while(nright>0){
		*ret = *mright;
		mright++;
		nright--;
		ret++;
	}
	free(ml);
	free(mr);
	return left;
}
int* _mergeSort(int *a, int n){
	static int indexy = 1;
	if(n<=1){
		return a;
	}
	int mid = n/2;
	
	_getch();
	printf("\nSort:");indexy+=2;
	setColor(red);
	printN(a,n);
	setColor(white);
	_getch();
	printf("L&R:");indexy++; _getch();
	printN(a,mid,1);
	_getch();
	printN(a+mid,n-mid);
	//_getch();
	
	int *ml = _mergeSort(a,mid);
	int *mr = _mergeSort(a+mid,n-mid);
	
	printf("Return:");indexy++; _getch();
	int *ret = _merge(ml,mid,mr,n-mid);

	setColor(green);
	printN(ml,n);
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
	printC("\t\tMerge Sort\n",red);
	int *ret = _mergeSort(a, n);
	setColor(green);
	printN(a, n);
	printC("���Ӷ�a=O(NlogN) �ȶ�\n",yellow);
	_getch();
	return ret;
}


void bubbleSort(int *a,int n){
	
	cls();

	static int index = 0;
	printf("\t\tBubble Sort\n");
	//printN(a,n);
	index++;
	
	for (int i=0;i<n-1;i++){
		for (int j=0;j<n-i-1;j++){
			
			printf("[ ");
			for(int z=0;z<n;z++){
				if(z==j||z==j+1){
					setColor(red);
				}else if(z>n-i-1){
					setColor(green);
				}else{
					setColor(white);
				}
				printf("%2d ",a[z]);
			}
			setColor(white);
			printf("]\n");
			setPos(3+3*j,2);
			printC("I__I",blue);
			if(a[j]>a[j+1]){
				int tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
			}
			_getch();
			clearLine(2);
			clearLine(1);
		}
	}

	printf("[ ");setColor(green);
	for (int z = 0; z < n; z++) {
		printf("%2d ", a[z]);
	}
	setColor(white);printf("]\n");

	setColor(yellow);
	setPos(0, 2);
	pBubbleSort();
	setColor(white);
}


void bucketSort(int* a, int n) {
	Array bucket[10] = { 0 };  //assume the value is no more than 100
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
		printC("I",red);
		setPos(2 + i * 4, 0); setColor(black); printf("%2d", a[i]); setColor(white);
		if (bucket[index] == NULL) {
			bucket[index] = makeArray(); //assume no error occurs
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
				setPos(14+j*3, 2 + i);
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
	pBucketSort();
	setColor(white);
}

void quickSort(int* a, int left, int right) {
	if (left < right) {
		int l = left;
		int r = right;
		int k = a[left];
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
		quickSort(a, left, l - 1);
		quickSort(a, l + 1, right);
	}
}

