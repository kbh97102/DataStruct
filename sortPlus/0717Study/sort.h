#include <stdio.h>
#include <string.h>


int mergeSorted[10];

void bubbleSort(int *base, int count);
void selectionSort(int *base, int count);
void insertionSort(int *base, int count);
void mergeSort(int *base, int left, int right);
void merge(int *base, int left, int mid, int right);
void heapSort(int *base, int count);
void quickSort(int *base, int count);


void swap(int *base, int index1, int index2);
void view(int *base, int count);


