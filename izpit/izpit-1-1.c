#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

int najBlok(int z[5][6], int m, int n);
int min(int a, int b, int c);
void print(int **auxiliary, int m, int n);

int main()
{
	int matrika[5][6] = {
		{0, 1, 0, 1, 0, 0},
		{0, 1, 1, 1, 1, 0},
		{0, 1, 1, 1, 1, 1},
		{0, 0, 1, 1, 1, 1},
		{1, 0, 0, 1, 0, 1}
	};
	int rez = najBlok(matrika, 5, 6);
	printf("%d\n", rez);
	return 0;
}

int najBlok(int z[5][6], int m, int n) {
	int max = 0;
	int **auxiliary;
	auxiliary = (int **) malloc(sizeof(int*) * m);
	for(int i = 0; i < m; i++) {
		auxiliary[i] = (int*) malloc(sizeof(int) * n);
	}
	for(int i = 0; i < m; i++) {
		auxiliary[i][0] = z[i][0];
	}
	for(int i = 0; i < m; i++) {
		auxiliary[0][i] = z[0][i];
	}
	for(int i = 1; i < m; i++) {
		for(int j = 1; j < n; j++) {
			if(z[i][j] == 1) {
				auxiliary[i][j] = min(auxiliary[i][j - 1], auxiliary[i -1][j], auxiliary[i -1][j-1]) + 1;
				if(auxiliary[i][j] > max) {
					max = auxiliary[i][j];
				}
			} else {
				auxiliary[i][j] = 0;
			}
		}
	}
	for(int i = 0; i < m; i++) {
		free(auxiliary[i]);
	}
	free(auxiliary);
	return max;
}

void print(int **auxiliary, int m, int n) {
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++) {
			printf("%d ", auxiliary[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int min(int a, int b, int c) {
	//printf("a = %d b = %d c = %d\n", a, b, c);
	int m = a;
	if (m > b) {
		m = b;
	}
	if (m > c) {
		m = c;
	}
	return m;
}
