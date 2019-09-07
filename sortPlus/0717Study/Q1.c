#include"sort.h"

void swap(int *base, int index1, int index2) {
	int temp;
	temp = base[index1];
	base[index1] = base[index2];
	base[index2] = temp;
}
void view(int *base, int count) {
	
	for (int i = 0; i < count; i++) {
		printf("%d ", base[i]);
	}
	printf("\n");
}
void bubbleSort(int *start, int count) {  //���������� �յڸ� �ٲ㳪��, ������ ���
	for (int i = count; i >1 ; i--) {
		for (int j = 1; j < count; j++) {
			if (start[j - 1] > start[j]) {
				swap(start, j - 1, j);
			}
		}
	}

	view(start, 10);
}
void selectionSort(int *base, int count) { //�ִ밪�� ã�� �� ��ġ����, ������ ���
	int max_index;
	for (int i = count; i > 1; i--) {
		max_index = 0;
		for (int j = 1; j < i; j++) {
			if (base[max_index] < base[j]) { // �ִ밪 ��ġ
				max_index = j;
			}
		}
		swap(base, max_index, i - 1);
	}
	view(base, 10);
}
void insertionSort(int *base, int count) { //������ ���� �������� ����, �����߾ȵ�

	for (int i = 1; i < count; i++) {
		for (int j = i; j > 0; j--) {
			if (base[j - 1] > base[j]) {
				swap(base, j - 1, j);
			}
			//else break;
		}
	}
	view(base, count);
}
void merge(int *base, int left, int mid, int right) {
	int base_left, base_mid, base_now;
	base_left = left;
	base_mid = mid+1;
	base_now = left;

	while (base_left <= mid && base_mid <= right) { //���� ���ĵ� base �պ�
		if (base[base_left] <= base[base_mid]) {
			mergeSorted[base_now++] = base[base_left++];
		}
		else {
			mergeSorted[base_now++] = base[base_mid++];
		}
	}

	if (base_left > mid) { //�����ִ� ������ �ϰ� ����
		for (int i = base_mid; i <= right; i++) {
			mergeSorted[base_now++] = base[i];
		}
	}
	else {
		for (int i = base_left; i <= mid; i++) {
			mergeSorted[base_now++] = base[i];
		}
	}

	for (int i = left; i <= right; i++) {
		base[i] = mergeSorted[i];
	}
}
void mergeSort(int *base, int left, int right) {
	int mid;

	if (left < right) {
		mid = (left + right) / 2;
		mergeSort(base, left, mid);
		mergeSort(base, mid + 1, right);
		merge(base, left, mid, right);
	}
}

void heapSort(int *base, int count) {
	for (int i = 1; i < count; i++) {
		int c = i;
		do {
			int root = (c - 1) / 2; //������ ������ �θ� ������
			if (base[root] < base[c]) {// �θ� �ڽĺ��� ������ ��ġ�� ����
				int temp = base[root];
				base[root] = base[c];
				base[c] = temp;
			}
			c = root;
		} while (c != 0);
	}  // �̱����� ���� heap������ �ٲ�
	for (int i = count - 1; i >= 0; i--) { // ũ�⸦ �ٿ����� �ݺ������� ���� ����
		int temp = base[0]; //�Ǿտ��ִ� ���� ����ū��! �׷��� �� �ڷκ���
		base[0] = base[i];
		base[i] = temp;
		int root = 0; 
		int c = 1;
		do {
			c = 2 * root + 1; //c�� ��Ʈ�� �ڽ�
			if (base[c] < base[c + 1] && c < i - 1) { // �ڽĵ鰣�� ũ��� c�� ���� c+1�� ������
				c++;
			}
			if (base[root] < base[c] && c < i) { // ��Ʈ���� �ڽ��� ��ũ�� ����
				int temp = base[root];
				base[root] = base[c];
				base[c] = temp;
			}
			root = c;
		} while (c < i);
	}
}


int partition(int *base, int start, int end) {
	int pivot = base[end];
	int i;
	int index =start;
	for (i = start; i < end; i++) {
		if (base[i] <= pivot) {
			swap(base, i, index);
			index++;
		}
	}
	
	swap(base, index, end);
	return index;
}
void quick(int  *base, int start, int end) {
	int index;

	if (start < end) {
		index = partition(base, start, end);
		quick(base, start, index-1);
		quick(base, index + 1, end);
	}
	else {
		return;
	}
}
int main() {
	int test[10] = { 9,8,6,5,7,3,2,4,10,1 };
	//bubbleSort(test, 10);
	//selectionSort(test, 10);
	//insertionSort(test, 10);
	//mergeSort(test, 10);
	//quickSort(test, 10);
	//mergeSort(test, 0, 9);
	//heapSort(test, 10);
	//view(test, 10);
	quick(test, 0, 9);
	view(test, 10);
}