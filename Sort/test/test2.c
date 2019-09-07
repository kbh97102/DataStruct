#include "test.h"


void swap(int *base, int index1, int index2) {
	int temp;

	temp = base[index1];
	base[index1] = base[index2];
	base[index2] = temp;
}

void quickSort(int *base, int start, int end) {
	int pivot = start;
	int low = start + 1;
	int high = end;


	if (start >= end) {
		return;
	}
	while (low <= high) {
		while (base[low] <= base[pivot]) {
			low++;
		}
		while (base[high] >= base[pivot]) {
			high--;
		}
		if (low > high) {
			swap(base, high, pivot);
		}
		else {
			swap(base, low, high);
		}
	}
	quickSort(base, start, high-1);
	quickSort(base, high + 1, end);
}

void merge(int *base, int start, int middle, int end) {
	int low = start;
	int mid = middle + 1;
	int now_index = start;

	while (low <= middle || mid <= end) {
		if (base[low] < base[mid]) {
			sorted[now_index++] = base[low++];
		}
		else {
			sorted[now_index++] = base[mid++];
		}
	}
	if (low > middle) {
		for (int i = mid; i <= end; i++) {
			sorted[now_index++] = base[i];
		}
	}
	else {
		for (int i = low; i <= middle; i++) {
			sorted[now_index++] = base[i];
		}
	}

	for (int i = start; i <= end; i++) {
		base[i] = sorted[i];
	}
}
void mergeSort(int *base, int start, int end) {
	int mid;
	if (start < end) {
		mid = (start + end) / 2;
		mergeSort(base, start, mid);
		mergeSort(base, mid + 1, end);
		merge(base, start, mid, end);
	}
}

void heapSort(int *base) {
	for (int i = 0; i < MAX; i++) {
		int c = i;
		do {
			int root = (c - 1) / 2;
			if (base[root] < base[c]) {
				swap(base, root, c);
			}
			c = root;
		} while (c !=0);
	}

	for (int i = MAX - 1; i >= 0; i--) {
		swap(base, 0, i);
		int c = 1;
		int root = 0;
		do {
			c = root * 2 + 1;
			if (base[c] < base[c++] && c < i - 1) {
				c++;
			}
			if (base[root] < base[c] && c < i) {
				swap(base, root, c);
			}
			root = c;
		} while (c < i);
	}
}