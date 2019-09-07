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
	int pivot = start; //pivot은 기준, 배열 첫 값으로 설정
	int low = start + 1;
	int high = end;
	int temp; // 임시저장

	if (start >= end) {
		return;
	}
	while (low <= high) { // 엇갈릴때까지 반복
		while (base[low] <= base[pivot]) {
			low++;
		}
		while (base[high] >= base[pivot] && high > start) {
			high--;
		}
		if (low > high) { // 엇갈리면 피벗과 교체
			//swap(base, high, pivot);
			temp = base[high];
			base[high] = base[pivot];
			base[pivot] = temp;
		}
		else { //엇갈리지 않으면 두 값을 변경
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
	//일단 다 쪼갠 상태
	//작은 순서대로 배열에 삽입
	while (low <= middle && mid <= end) {
		if (base[low] <= base[mid]) {
			sorted[nowINdex++] = base[low++];
		}
		else {
			sorted[nowINdex++] = base[mid++];
		}
	}
	//남은 데이터 삽입
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
	// 정렬된 배열을 삽입
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
			int root = (c - 1) / 2; //특정원소의 부모
			if (base[root] < base[c]) {
				swap(base, root, c);
			}
			c = root; //계속 부모노드로 이동
		} while (c != 0);
	}// 힙구조로 만듬

	//크기를 줄여가며 반복적으로 힙 , 정렬

	for (int i = MAX - 1; i >= 0; i--) {
		swap(base, 0, i); //가장 큰 값을 맨 뒤로
		int root = 0;
		int c = 1;
		do {
			c = 2 * root + 1; //c는 root 의 자식
			//자식 중 더 큰 값 찾기
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