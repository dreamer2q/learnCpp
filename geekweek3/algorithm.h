
#ifndef __algorithm__
#define __algorithm__



/*
##�鲢����Merge Sort��
�鲢�����ǽ����ڹ鲢�����ϵ�һ����Ч�������㷨��
���㷨�ǲ��÷��η���Divide and Conquer����һ���ǳ����͵�Ӧ�á�
��������������кϲ����õ���ȫ��������У�����ʹÿ��������������ʹ�����жμ�����
�������������ϲ���һ���������Ϊ2-·�鲢�� 
##�㷨����
�ѳ���Ϊn���������зֳ���������Ϊn/2�������У�
�������������зֱ���ù鲢����
����������õ������кϲ���һ�����յ��������С�
*/



int* mergeSort(int* a, int n);
void bubbleSort(int *a,int n);
void bucketSort(int* a, int n);
void quickSort(int* a, int left, int right);

#endif