#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "auxiliary.h"
#include "algorithm.h"



int main(){
	
	int a[10];
	
	randonNumsGenerate(a,10);
	printN(a,10);
	//cls();
	
	//bubbleSort(a,10);
	//mergeSort(a,10);
	bucketSort(a, 10);

	printN(a,10);
	
	return 0;
} 


