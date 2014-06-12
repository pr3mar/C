#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int position = 0;
char ** lcs;

void printing(int ** b, char ** X,int i,int j){
	if(i == 0 || j == 0){
		return;
	}
	if( b[i][j] == -1 ){
		printing(b, X, i - 1, j - 1);
		lcs[position] = X[i - 1];
		position += 1;	
	}
	else if (b[i][j] == -2){
		printing(b, X, i - 1, j);
	}
	else{
		printing(b, X, i, j - 1);
	}
	
}

int izpis(char * in, char ** tabela, FILE * dat, int pos, int dol){
	while(pos != dol){
		if(in == NULL){
			fprintf(dat, "%c", tabela[pos][0]);
		}
		else if(strcmp(in, tabela[pos]) == 0){
			pos += 1;			
			return pos;
		}
		else{
			fprintf(dat, "%c", tabela[pos][0]);
		}			
		pos += 1;
	}

	return pos;
}

void izpisKonec(char ** tabela, FILE * dat, int pos, int dol){
	while(pos != dol){
		fprintf(dat, "%c", tabela[pos][0]);	
		printf("%c", tabela[pos][0]);
		pos += 1;
	}
}



int main(int argumenti, char * argument[]){
	int lineln = 101;
	int maxstvrstic = 1000;
	int lena = 0;
	int lenb = 0;

	FILE * result = fopen(argument[3], "w");
	FILE * ina = fopen(argument[1], "r");
	FILE * inb = fopen(argument[2], "r");

	char ** inputa = malloc(maxstvrstic * sizeof(char *));
	char ** inputb = malloc(maxstvrstic * sizeof(char *));
	
	for(int i = 0; i < maxstvrstic; i++){
		inputa[i] = malloc(lineln * sizeof(char));
		inputb[i] = malloc(lineln * sizeof(char));
	}
	
	while (fgets(inputa[lena], lineln - 1, ina) != NULL) {
		//printf("%s", inputa[lena]);
		lena += 1;
	}
	while (fgets(inputb[lenb], lineln - 1, inb) != NULL) {
		//printf("%s", inputb[lenb]);
		lenb += 1;
	}

	lena += 1;
	lenb += 1;
	int m = lena;
	int n = lenb;
	int ** b = malloc(m * sizeof(int *));
	for(int i =0; i < m; i++){
		b[i] = malloc(n * sizeof(int));
	}

	int ** c = malloc(m * sizeof(int *));
	for(int i =0; i < m; i++){
		c[i] = malloc(n * sizeof(int));
	}

	for(int i = 0; i < m; i++){
		c[i][0] = 0;
	}

	for(int j = 0; j < n; j++){
		c[0][j] = 0;
	}

	for(int i = 1; i < m; i++){
		for(int j = 1; j < n; j++){
			if(strcmp(inputa[i - 1], inputb[j - 1]) == 0){
				c[i][j] = c[i -1][j - 1] + 1;
				b[i][j] = -1;
			}
			else if(c[i - 1] [j] >= c[i][j - 1]){
				c[i][j] = c[i - 1][j];
				b[i][j] = -2;
			}
			else{
				c[i][j] = c[i][j - 1];
				b[i][j] = -3;
			}
		}
	}
	/*
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			printf("%d", c[i][j]);
		}
		printf("\n");
	}
	*/
	lcs = malloc(c[m - 1][n - 1] * sizeof(char *));
	for(int i =0; i < c[m - 1][n - 1]; i++){
		lcs[i] = malloc(101 * sizeof(char));
	}
	printing(b, inputa, m - 1, n - 1);
	int positiona = 0;
	int positionb = 0;
	for(int i =0; i < c[m - 1][n - 1]; i++){
		positiona = izpis(lcs[i], inputa, result, positiona, lena - 1);
		positionb = izpis(lcs[i], inputb, result, positionb, lenb - 1);
	}

	positiona = izpis(NULL, inputa, result, positiona, lena - 1);
	positionb = izpis(NULL, inputb, result, positionb, lenb - 1);

	fprintf(result, "\n");
	fclose(ina);
	fclose(inb);
	fclose(result);
	return 0;
}


