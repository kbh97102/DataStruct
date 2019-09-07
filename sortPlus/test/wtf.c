void swap(int *base, int index1, int index2) {
	int temp;
	temp = base[index1];
	base[index1] = base[index2];
	base[index2] = temp;
}

void bubble(int *base, int count) {
	for (int i = count; i > 0; i--) {
		for (int j = 1; j < i; j++) {
			if (base[j - 1] > base[j]) {
				swap(base, j - 1, j);
			}
		}
	}
}
void select(int *base, int count) {
	int max;
	for (int i = count; i > 1; i--) {
		max = 0;
		for (int j = 1; j < i; j++) {
			if (base[max] < base[j]) {
				max = j;
			}
		}
		swap(base, max, i - 1);
	}
}
void insert(int *base, int count) {
	for (int i = 1; i < count; i++) {
		for (int j = i; j >= 0; j--) {
			if (base[j - 1] > base[j]) {
				swap(base, j - 1, j);
			}
		}
	}
}

int sorted[10];
void merge(int *base, int left, int mid, int right) {
	int base_left, base_mid, base_now;
	base_left = left;
	base_mid = mid + 1;
	base_now = left;

	if (base_left <= base_mid && base_mid <= right) {
		sorted[base_now++] = base[base_left++];
	}
	else {
		sorted[base_now++] = base[base_mid++];
	}

	if (base_left > mid) {
		for (int i = base_mid; i < right; i++)
			sorted[base_now++] = base[i];
	}
	else {
		for (int i = base_left; i < mid; i++) {
			sorted[base_left++] = base[i];
		}
	}

	for (int i = left; i < right; i++) {
		base[i] = sorted[i];
	}
}
void mergeSort(int *base, int left, int right) {
	int mid;

	if (right < left) {
		mid = (left + right) / 2;
		mergeSort(base, left, mid);
		mergeSort(base, mid + 1, right);
		merge(base, left, mid, right);
	}
}

void heap(int *base, int count) {
	for (int i = 1; i < count; i++) {
		int c = i;
		do {
			int root = (c - 1) / 2;
			if (base[root] < base[c]) {
				swap(base, root, c);
			}
			c = root;
		} while (c != 0);
	}
	for (int i = count-1; i >= 0; i--) {
		int c = 1;
		int root = 0;
		do {
			c = root * 2 + 1;
			if (base[c] < base[c + 1] && c < i - 1) {
				c++;
			}
			if (base[root] < base[c] && c < i) {
				swap(base, root, i);
			}
			root = c;
		} while (c < i);
	}
}

int partition(int *base, int start, int end) {
	int pivot = base[end];
	int i;
	int index = start;

	for (int i = start; i < end; i++) {
		if (base[i] <= pivot) {
			swap(base, i, index);
			index++;
		}
	}
	swap(base, index, end);
	return index;
}
void quick(int *base, int start, int end) {
	int index;

	if (start < end) {
		index = partition(base, start, end);
		quick(base, start, index-1);
		quick(base, index + 1, end);
	}
}