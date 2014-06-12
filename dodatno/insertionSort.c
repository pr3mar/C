#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertionSort(int *a, int velikost);
void selectionSort(int *a, int velikost);
void bubbleSort(int *a, int velikost);
void print(int *a, int velikost);

int main()
{
	int a[] = {7, 5, 2, 4, 3, 9};
	int velikost = 6;
	print(a, velikost);
	printf("\n");
	//insertionSort(a, velikost);
	selectionSort(a, velikost);
	print(a, velikost);
	printf("\n");
	bubbleSort(a, velikost);
	print(a, velikost);
	printf("\n");
	return 0;
}

void insertionSort(int *a, int velikost) {
	for(int i = 1; i <= velikost -1; i++) {
		int j = i - 1;
		int val = a[i];
		printf("a[%d] = %d, j = [%d]-> [", i, val, j);
		print(a, velikost);
		printf("]\n");
		while((j >= 0) && (a[j] > val)) {
			a[j + 1] = a[j];
			j--;
			printf("\t");
			print(a, velikost);
			printf("\n");
		}
		a[j + 1] = val;
		printf("\t");
		print(a, velikost);
		printf("\n");
	}
}

void selectionSort(int *a, int velikost) {
	for(int i = 0; i <= (velikost - 2); i++) {
		int idx_min = i;
		for(int j = i + 1; j <= (velikost - 1); j++) {
			if(a[j] < a[idx_min]) {
				idx_min = j;
			}
		}
		int tmp = a[idx_min];
		a[idx_min] = a[i];
		a[i] = tmp;
	}
}

void bubbleSort(int *a, int velikost) {
	for(int i = 0; i <= (velikost - 2); i++) {
		for(int j = 0; j <= (velikost - i - 2); j++) {
			if(a[j + 1] > a[j]) {
				int tmp = a[j + 1];
				a[j + 1] = a[j];
				a[j] = tmp;
			}
		}
	}
}

void print(int *a, int velikost) {
	for(int i = 0; i < velikost; i++) {
		printf("%d ", a[i]);
	}
	//printf("\n");
}