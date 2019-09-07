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
	int temp;

	if (start >= end) {
		return;
	}

	while (low <= high){
		while (base[low] <= base[pivot]) {
			low++;
		}
		while (base[high] >= base[pivot] && high > start) {
			high--;
		}
		if (low >= high) {
			temp = base[high];
			base[high] = base[pivot];
			base[pivot] = temp;
		}
		else {
			temp = base[high];
			base[high] = base[low];
			base[low] = temp;
		}
	}

	quickSort(base, start, high - 1);
	quickSort(base, high + 1, end);
}

void merge(int *base, int start, int middle, int end) {
	int low = start;
	int mid = middle + 1;
	int nowIndex = start;
	while (low <= middle && mid <= end) {
		if (base[low] <= base[mid]) {
			sorted[nowIndex++] = base[low++];
		}
		else {
			sorted[nowIndex++] = base[mid++];
		}
	}
	if (low > middle) {
		for (int y = mid; y <= end; y++) {
			sorted[nowIndex++] = base[y];
		}
	}
	else {
		for (int y = low; y <= middle; y++) {
			sorted[nowIndex++] = base[y];
		}
	}

	for (int y = start; y <= end; y++) {
		base[y] = sorted[y];
	}
}
void mergeSort(int *base, int start, int end) {
	int middle;
	if (start < end) {
		middle = (start + end) / 2;
		mergeSort(base, start, middle);
		mergeSort(base, middle + 1, end);
		merge(base, start, middle, end);
	}
}

void heapSort(int *base) {
	for (int i = 1; i < MAX; i++) {
		int c = i;
		do {
			int root = (c - 1) / 2;
			if (base[c] > base[root]) {
				swap(base, c, root);
			}
			c = root;
		} while (c != 0);
	}

	for (int i = MAX - 1; i >= 0; i--) {
		swap(base, 0, i);
		int c = 1;
		int root = 0;
		do {
			c = root * 2 + 1;
			if (base[c] < base[c + 1] && c < i - 1) {
				c++;
			}
			if (base[c] > base[root] && c < i) {
				swap(base, c, root);
			}
			root = c;
		} while (c < i);
	}
}

int main() {
	int test[MAX] = { 1,10,3,6,2,5,4,7,8,9 };

	//quickSort(test, 0, MAX - 1);
	//mergeSort(test, 0, MAX - 1);
	heapSort(test);
	for (int i = 0; i < MAX; i++) {
		printf("%d ", test[i]);
	}
}