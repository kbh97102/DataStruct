#include <stdio.h>


#define MAX 10

void show(int *base);
void swap(int *base, int index1, int index2);

void QuickSort(int *base, int low, int high);
void Merge(int *base, int start, int middle, int end);
void MergeSort(int *base, int start, int end);
void HeapSort(int *base);


int test[MAX] = { 1,10,5,8,7,6,4,3,2,9 };
int sorted[MAX] = { 0, };