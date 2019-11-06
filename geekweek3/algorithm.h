
#ifndef __algorithm__
#define __algorithm__



/*
##归并排序（Merge Sort）
归并排序是建立在归并操作上的一种有效的排序算法。
该算法是采用分治法（Divide and Conquer）的一个非常典型的应用。
将已有序的子序列合并，得到完全有序的序列；即先使每个子序列有序，再使子序列段间有序。
若将两个有序表合并成一个有序表，称为2-路归并。 
##算法描述
把长度为n的输入序列分成两个长度为n/2的子序列；
对这两个子序列分别采用归并排序；
将两个排序好的子序列合并成一个最终的排序序列。
*/



int* mergeSort(int* a, int n);
void bubbleSort(int *a,int n);
void bucketSort(int* a, int n);
void quickSort(int* a, int left, int right);
void insertSort1(int* a, int n); //array
void insertSort2(int* a, int n); //linked list
void selectionSort(int* a, int n);
void shellSort(int* a, int n);
void countingSort(int* a, int n);

#endif