#pragma once

#ifndef __algorithm__
#define __algorithm__



/*
##�鲢����Merge Sort��
�鲢�����ǽ����ڹ鲢�����ϵ�һ����Ч�������㷨��
���㷨�ǲ��÷��η���Divide and Conquer����һ���ǳ����͵�Ӧ�á�
��������������кϲ����õ���ȫ��������У�����ʹÿ��������������ʹ�����жμ�����
��������������ϲ���һ�����������Ϊ2-·�鲢�� 
##�㷨����
�ѳ���Ϊn���������зֳ���������Ϊn/2�������У�
�������������зֱ���ù鲢����
����������õ������кϲ���һ�����յ��������С�
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
void radixSort(int* a, int n);
void heapSort(int* a, int n);
void buildMaxHeap(int* a, int n);
void heapify(int* a, int n, int node);
void heapSort(int* a, int n);
#endif