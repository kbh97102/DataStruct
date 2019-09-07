#include "sort.h"





void show(int *base) {
	for (int i = 0; i < MAX; i++) {
		printf("%d ", base[i]);
	}
}
void swap(int *base, int index1, int index2) {
	int temp;

	temp = base[index1];
	base[index1] = base[index2];
	base[index2] = temp;
}
void QuickSort(int *base, int start, int end) {
	int pivot = start; //pivot�� ����, �迭 ù ������ ����
	int low = start + 1;
	int high = end;
	int temp; // �ӽ�����

	if (start >= end) {
		return;
	}
	while (low <= high) { // ������������ �ݺ�
		while (base[low] <= base[pivot]) {
			low++;
		}
		while (base[high] >= base[pivot] && high > start) {
			high--;
		}
		if (low > high) { // �������� �ǹ��� ��ü
			//swap(base, high, pivot);
			temp = base[high];
			base[high] = base[pivot];
			base[pivot] = temp;
		}
		else { //�������� ������ �� ���� ����
			//swap(base, high, low);
			temp = base[high];
			base[high] = base[low];
			base[low] = temp;
		}
	}

	
	QuickSort(base, start, high - 1);
	QuickSort(base, high + 1, end);
}
void Merge(int *base, int start, int middle, int end) {

	int low = start;
	int mid = middle + 1;
	int nowINdex = start;
	//�ϴ� �� �ɰ� ����
	//���� ������� �迭�� ����
	while (low <= middle && mid <= end) {
		if (base[low] <= base[mid]) {
			sorted[nowINdex++] = base[low++];
		}
		else {
			sorted[nowINdex++] = base[mid++];
		}
	}
	//���� ������ ����
	if (low > middle) {
		for (int i = mid; i <= end; i++) {
			sorted[nowINdex++] = base[i];
		}
	}
	else {
		for (int i = low; i <= middle; i++) {
			sorted[nowINdex++] = base[i];
		}
	}
	// ���ĵ� �迭�� ����
	for (int i = 0; i <= end; i++) {
		base[i] = sorted[i];
	}
}
void MergeSort(int *base, int start, int end){
	int middle;
	if (start < end) {
		int middle = (start + end) / 2;
		MergeSort(base, start, middle);
		MergeSort(base, middle + 1, end);
		Merge(base, start, middle, end);
	}
}

void HeapSort(int *base) {
	for (int i = 1; i < MAX; i++) {
		int c = i;
		do {
			int root = (c - 1) / 2; //Ư�������� �θ�
			if (base[root] < base[c]) {
				swap(base, root, c);
			}
			c = root; //��� �θ���� �̵�
		} while (c != 0);
	}// �������� ����

	//ũ�⸦ �ٿ����� �ݺ������� �� , ����

	for (int i = MAX - 1; i >= 0; i--) {
		swap(base, 0, i); //���� ū ���� �� �ڷ�
		int root = 0;
		int c = 1;
		do {
			c = 2 * root + 1; //c�� root �� �ڽ�
			//�ڽ� �� �� ū �� ã��
			if (base[c] < base[c + 1] && c < i - 1) {
				c++;
			}
			if (base[root] < base[c] && c < i) {
				swap(base, root, c);
			}
			root = c;
		} while (c < i);
	}
}
int main() {
	

	//QuickSort(test, 0, MAX-1);
	//MergeSort(test, 0, MAX - 1); 
	HeapSort(test);
	show(test);
	
}