
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <conio.h>

#include "auxiliary.h"

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
int* mergeSort(int *a, int n){
	static int indexy = 0;
	if(n<=1){
		return a;
	}
	int mid = n/2;
	
	printf("Sorting:");indexy++;
	printN(a,n);
	
	printf("Divide into L&R:");indexy++;
	printN(a,mid,1);printN(a+mid,n-mid);
	_getch();
	
	int *ml = mergeSort(a,mid);
	int *mr = mergeSort(a+mid,n-mid);
	
	printf("Merging L&R:");indexy++;
	int *ret = _merge(ml,mid,mr,n-mid);
	printN(ml,n);
	_getch();

	clearLine(--indexy);
	clearLine(--indexy);
	clearLine(--indexy);
	
	return ret;
}
void pMergeSort(){
	
	printf("复杂度a=O(NlogN) 稳定\n");
}

void bubbleSort(int *a,int n){
	
	static int index = 0;
	printf("Sorting:");printN(a,n);index++;
	
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
}

void pBubbleSort(){
	printf("复杂度a=O(N^2) 稳定\n");	
}


void bucketSort(int* a, int n) {
	Array bucket[10] = { 0 };  //assume the value is no more than 100
	for (int i = 0; i < n; i++) {
		int index = a[i] / 10;
		if (bucket[index] == NULL) {
			bucket[index] = makeArray(); //assume no error occurs
		}
		insertElementByOrder(bucket[index], a[i]);
	}

	int index = 0;
	for (int i = 0; i < n; i++) {
		if (bucket[i] != NULL) {
			int length = getArrayLength(bucket[i]);
			for (int j = 0; j < length; j++) {
				a[index++] = getArrayAt(bucket[i], j);
			}
			deleteArray(bucket[i]);  //remember to give back what we have asked
		}
	}

}

