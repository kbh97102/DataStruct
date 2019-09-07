#include <stdio.h>

#define MAX 10


void swap(int *base, int index1, int index2);
void quickSort(int *base, int start, int end);
void merge(int *base, int start, int middle, int end);
void mergeSort(int *base, int start, int end);
void heapSort(int *base);

int sorted[MAX] = { 0, };