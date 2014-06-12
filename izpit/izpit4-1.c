// input: 
// 325 256 309 317 284 234 305 324 351 316 300 254 301 315 331 -9999
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define LEN 10

int *expand(int* array, int m);
void print(int * array, int velikost);

int main()
{
	int velikost = LEN;
	int *array = (int*) malloc(sizeof(int) * velikost);
	int tmp, i = 0;
	scanf("%d", &tmp);
	while(tmp != -9999) {
		array[i] = tmp;
		scanf("%d", &tmp);
		i++;
		if((velikost - 1) == i) {
			velikost += LEN;
			array = expand(array, velikost);
		}
	}
	array[i] = -1;
	velikost = i + 1;
	int lSum = 0, lLen = 0, sum = 0, len = 0, index = 0;
	for(int i = 0; i < velikost; i++) {
		if(array[i] >= 300) {
			lLen++;
			lSum += array[i];
		} else {
			//printf("[%d, %d]\n", lSum, lLen);
			if(lLen > len) {
				sum = lSum;
				len = lLen;
				index = i - len + 1;
			}
			lLen = 0;
			lSum = 0;
		}
	}
	
	//print(array, velikost);

	printf("%d %d\n", index, len);
	free(array);
	return 0;
}

int *expand(int* array, int m) {
	array = (int *) realloc(array, sizeof(int) * m);
	return array;
}

void print(int *array, int velikost) {
	for(int i = 0; i < velikost; i++) {
		printf("%4d ", i);
	}
	printf("\n");
	for(int i = 0; i < velikost; i++) {
		printf("%4d ", array[i]);
	}
	printf("\n");
}
