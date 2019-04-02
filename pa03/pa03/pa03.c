#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define parent(x) (x-1)/2

int *RandomNumber(int N);
int *ReverseArr(int N);
void BubbleSort(int mode, int N, int c);
void SelectionSort(int mode, int N, int c);
void InsertionSort(int mode, int N, int c);
void MergeSort(int data[], int p, int r, int m, int c);
void Merge(int data[], int p, int q, int r, int m);
void QuickSort1(int arr[], int left, int right);
void QuickSort2(int arr[], int left, int right);
void QuickSort3(int arr[], int left, int right);
int Partition1(int list[], int left, int right);
int Partition2(int list[], int left, int right);
int Partition3(int list[], int left, int right);
int median_of_three(int arr[], int left, int right);
void Swap(int *arr, int a, int b);
void heap(int arr[], int N);
void HeapSort(int arr[], int N, int c);
int static compare(const void* first, const void* second);

int tmp[1000];
int tmp1[10000];
int tmp2[100000];
double ExeTime[9][6];
int pivot, low, high;
	
int main() {
	int arrsize[3] = { 1000,10000,100000 };
	int *test[33];
	int *q1test[33];
	int *q2test[33];
	int *q3test[33];
	int *heaptest[33];
	int *libtest[33];
	int sec = 1000;
	time_t start, end;

	char *algo[9] = { "Bubble","Selection","Insertion","Merge","Quick1","Quick2" ,"Quick3", "Heap", "Library" };

	for (int i = 0; i < 33; i++) {
		int q = i / 10;
		int r = i - 30;

		if (i < 30) {
			test[i] = RandomNumber(arrsize[q]);
			q1test[i] = RandomNumber(arrsize[q]);
			q2test[i] = RandomNumber(arrsize[q]);
			q3test[i] = RandomNumber(arrsize[q]);
			heaptest[i] = RandomNumber(arrsize[q]);
			libtest[i] = RandomNumber(arrsize[q]);
		}
		else {
			test[i] = ReverseArr(arrsize[r]);
			heaptest[i] = ReverseArr(arrsize[r]);
			libtest[i] = ReverseArr(arrsize[r]);
		}

		if (i < 30) {
			BubbleSort(0, arrsize[q], q);
			SelectionSort(0, arrsize[q], q);
			InsertionSort(0, arrsize[q], q);
			MergeSort(test[i], 0, arrsize[q] - 1, q, q);
			start = time(NULL);
			QuickSort1(q1test[i], 0, arrsize[q] - 1);
			end = time(NULL);
			ExeTime[4][q] += (int)(end - start);
			start = time(NULL);
			QuickSort2(q2test[i], 0, arrsize[q] - 1);
			end = time(NULL);
			ExeTime[6][q] += (int)(end - start);
			start = time(NULL);
			QuickSort3(q3test[i], 0, arrsize[q] - 1);
			end = time(NULL);
			ExeTime[5][q] += (int)(end - start);
			HeapSort(heaptest[i], arrsize[q], q);
			start = time(NULL);
			qsort(libtest[i], arrsize[q], sizeof(int), compare);
			end = time(NULL);
			ExeTime[8][q] += (int)(end - start);
		}
		else {
			BubbleSort(1, arrsize[r], q + r);
			SelectionSort(1, arrsize[r], q + r);
			InsertionSort(1, arrsize[r], q + r);
			MergeSort(test[i], 0, arrsize[r] - 1, r, q + r);
			HeapSort(heaptest[i], arrsize[r], q+r);
			start = time(NULL);
			qsort(libtest[i], arrsize[r], sizeof(int), compare);
			end = time(NULL);
			ExeTime[8][q+r] += (int)(end - start);
		}
	}
	printf("------------------------------------------------------------------------------------------\n");
	printf("		Random1000 Reverse1000 Random10000 Reverse10000 Random100000 Reverse100000\n");
	printf("------------------------------------------------------------------------------------------\n");

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 6; j++) {
			ExeTime[i][j] /= sec;
		}
	}
	for (int i = 0; i < 9; i++) {
		if (i != 1 && i != 2) {
			if (i == 4 || i == 5 || i == 6) {
				printf("%s	\t%lf   %s    %lf    %s     %lf     %s\n", algo[i], ExeTime[i][0] / 10, "Overflow", ExeTime[i][1] / 10, "Overflow", ExeTime[i][2] / 10, "Overflow");
			}
			else
				printf("%s	\t%lf   %lf    %lf    %lf     %lf     %lf\n", algo[i], ExeTime[i][0] / 10, ExeTime[i][3], ExeTime[i][1] / 10, ExeTime[i][4], ExeTime[i][2] / 10, ExeTime[i][5]);
		}
		else
			printf("%s	%lf   %lf    %lf    %lf     %lf     %lf\n", algo[i], ExeTime[i][0] / 10, ExeTime[i][3], ExeTime[i][1] / 10, ExeTime[i][4], ExeTime[i][2] / 10, ExeTime[i][5]);
	}

	return 0;
}

int *RandomNumber(int N) { //1부터 N까지의 정수들을 N까지 랜덤하게 생성
	int *arr = (int*)malloc(N * sizeof(int));

	for (int i = 0; i < N; i++)
		arr[i] = rand() % N;
	return arr;
}

int *ReverseArr(int N) {
	int *rarr = (int*)malloc(N * sizeof(int));

	for (int i = 0; i < N; i++)
		rarr[i] = N - i;

	return rarr;
}

void BubbleSort(int mode, int N, int c) {
	clock_t start, end;
	double result;
	int tmp;
	int *arr;

	if (mode == 0) arr = RandomNumber(N);
	else arr = ReverseArr(N);

	start = clock();

	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < N - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}

	end = clock();
	result = (double)(end - start);
	free(arr);
	ExeTime[0][c] += result;
}

void SelectionSort(int mode, int N, int c) {
	time_t start, end;
	int tmp;
	int result;
	int *arr;

	if (mode == 0) arr = RandomNumber(N);
	else arr = ReverseArr(N);
	start = time(NULL);

	for (int i = 0; i < N - 1; i++) {
		for (int j = i + 1; j < N; j++) {
			if (arr[i] > arr[j]) {
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}

	end = time(NULL);
	result = (int)(end - start);
	free(arr);
	ExeTime[1][c] += result;
}

void InsertionSort(int mode, int N, int c) {
	time_t start, end;
	int result;
	int key;
	int *arr;

	if (mode == 0) arr = RandomNumber(N);
	else arr = ReverseArr(N);
	start = time(NULL);

	for (int i = 1; i < N; i++) {
		key = arr[i];
		for (int j = i - 1; j >= 0; j--) {
			if (arr[j] > key)
				arr[j + 1] = arr[j];
			else break;
		}
	}

	end = time(NULL);
	result = (int)(end - start);
	free(arr);
	ExeTime[2][c] += result;
}

void MergeSort(int arr[], int p, int r, int m, int c) {
	time_t start, end;
	int result;
	int q;
	start = time(NULL);
	if (p < r) {
		q = (p + r) / 2;
		MergeSort(arr, p, q, m, c);
		MergeSort(arr, q + 1, r, m, c);
		Merge(arr, p, q, r, m);
	}
	end = time(NULL);
	result = (int)(end - start);
	ExeTime[3][c] += result;
}

void Merge(int arr[], int p, int q, int r, int m) {
	int i = p, j = q + 1, k = p;
	if (m == 0) {
		while (i <= q && j <= r) {
			if (arr[i] <= arr[j]) tmp[k++] = arr[i++];
			else tmp[k++] = arr[j++];
		}
		while (i <= q) tmp[k++] = arr[i++];
		while (j <= r) tmp[k++] = arr[j++];
		for (int a = p; a <= r; a++) arr[a] = tmp[a];
	}
	if (m == 1) {
		while (i <= q && j <= r) {
			if (arr[i] <= arr[j]) tmp1[k++] = arr[i++];
			else tmp1[k++] = arr[j++];
		}
		while (i <= q) tmp1[k++] = arr[i++];
		while (j <= r) tmp1[k++] = arr[j++];
		for (int a = p; a <= r; a++) arr[a] = tmp1[a];
	}
	if (m == 2) {
		while (i <= q && j <= r) {
			if (arr[i] <= arr[j]) tmp2[k++] = arr[i++];
			else tmp2[k++] = arr[j++];
		}
		while (i <= q) tmp2[k++] = arr[i++];
		while (j <= r) tmp2[k++] = arr[j++];
		for (int a = p; a <= r; a++) arr[a] = tmp2[a];
	}
}

int Partition1(int arr[], int first, int last) {
	pivot = arr[last];
	low = first;
	high = last - 1;

	while (low < high) {
		while (low < last && arr[low] <= pivot) low++;
		while (arr[high] > pivot) high--;

		if (low < high) Swap(arr, low, high);
	}

	if (arr[low] > arr[last]) Swap(arr, low, last);

	return low;
}

void QuickSort1(int arr[], int left, int right) {
	if (left < right) {
		int q = Partition1(arr, left, right);

		QuickSort1(arr, left, q - 1);
		QuickSort1(arr, q + 1, right);
	}
}

void Swap(int *arr, int a, int b) {
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

int Partition3(int arr[], int first, int last) {
	pivot = arr[rand() % (last + 1)];
	low = first;
	high = last - 1;

	while (low < high) {
		while (low < last && arr[low] <= pivot) low++;
		while (arr[high] > pivot) high--;

		if (low < high) Swap(arr, low, high);
	}

	if (arr[low] > arr[last]) Swap(arr, low, last);

	return low;
}

void QuickSort3(int arr[], int left, int right) {
	if (left < right) {
		int q = Partition3(arr, left, right);

		QuickSort1(arr, left, q - 1);
		QuickSort1(arr, q + 1, right);
	}
}

int Partition2(int arr[], int first, int last) {
	int median = median_of_three(arr, first, last);
	pivot = arr[median];
	low = first;
	high = last - 1;

	while (low < high) {
		while (low < last && arr[low] <= pivot) low++;
		while (arr[high] > pivot) high--;

		if (low < high) Swap(arr, low, high);
	}

	if (arr[low] > arr[last]) Swap(arr, low, last);

	return low;
}

void QuickSort2(int arr[], int left, int right) {
	if (left < right) {
		int q = Partition2(arr, left, right);

		QuickSort1(arr, left, q - 1);
		QuickSort1(arr, q + 1, right);
	}
}

int median_of_three(int arr[], int left, int right) {
	int mid;
	mid = (left + right) / 2;

	if (arr[left] > arr[mid])
		Swap(arr, left, mid);
	if (arr[left] > arr[right])
		Swap(arr, left, right);
	if (arr[mid] > arr[right])
		Swap(arr, mid, right);

	return mid;
}


void heap(int arr[], int N) {
	for (int i = 1; i < N; i++) {
		int child = i;
		while (child > 0) {
			int root = parent(child);
			if (arr[root] < arr[child]) {
				int temp = arr[root];
				arr[root] = arr[child];
				arr[child] = temp;
			}
			child = root;
		}
	}
}

void HeapSort(int arr[], int N, int c) {
	time_t start, end;
	int result;
	start = time(NULL);

	heap(arr, N);

	for (int i = N - 1; i >= 0; i--) {
		int temp = arr[i];
		arr[i] = arr[0];
		arr[0] = temp;

		heap(arr, i);
	}
	end = time(NULL);
	result = (int)(end - start);
	ExeTime[7][c] += result;
}

int static compare(const void* first, const void* second){
	if (*(int*)first > *(int*)second)
		return 1;
	else if (*(int*)first < *(int*)second)
		return -1;
	else
		return 0;
}