#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **matrikaZnakov; 
int *vrstice; 

void sortiraj(int size);

int main()
{
	// declarations
	int vrstica, beseda, crka;
	int wordSize, maxWords;
	
	// get sizes
	scanf("%d %d\n", &wordSize, &maxWords);
	
	// assign memory
	matrikaZnakov = (char**) malloc(maxWords * sizeof(char*));
	vrstice = (int*) malloc(maxWords * sizeof(int));
	for(int i = 0; i < maxWords; i++) {
		matrikaZnakov[i] = (char*) malloc( (wordSize + 1) * sizeof(char));
	}
	
	// get input
	vrstica = 1; beseda = 0; crka = 0;
	int znak = getc(stdin);
	while(znak >= 0) {
		if (znak == ' ') {
			matrikaZnakov[beseda][crka] = '\0';
			vrstice[beseda] = vrstica;
			beseda++;
			crka = 0;
		} else if (znak == '\n') {
			matrikaZnakov[beseda][crka] = '\0';
			vrstice[beseda] = vrstica;
			beseda++;
			crka = 0;
			vrstica++;
		} else {
			matrikaZnakov[beseda][crka] = znak;
			crka++;
		}
		znak = getc(stdin);
		
	}
	
	// sortiraj besede
	maxWords = beseda;
	sortiraj(maxWords);
	
	// izpisi rezultat
	printf("%s %d", matrikaZnakov[0], vrstice[0]);
	for(int i = 1; i < beseda; i++) {
		if (strcmp(matrikaZnakov[i], matrikaZnakov[i - 1]) == 0)
		{
			printf(" %d", vrstice[i]);
		}
		else
		{
			printf("\n%s %d", matrikaZnakov[i], vrstice[i]);
		}
	}
	printf("\n");
	
	// free memory
	for(int i = 0; i < maxWords; i++) {
		free(matrikaZnakov[i]);
		matrikaZnakov[i] = NULL;
	}
	matrikaZnakov = NULL;
	// exit program
	return 0;
}

// navadno vstavljanje
void sortiraj (int size)
{
	for (int i = 1; i <= (size - 1); i++) {
		char* val1 = (char *) malloc( sizeof(char) * strlen(matrikaZnakov[i]));
		strcpy(val1,matrikaZnakov[i]);
		int val2 = vrstice[i];
		int j = i - 1;
		while ( (j>=0) && ( strcmp(matrikaZnakov[j], val1) > 0) )
		{
			strcpy(matrikaZnakov[j + 1], matrikaZnakov[j]);
			vrstice[j + 1] = vrstice[j];
			j--;
		}
		strcpy(matrikaZnakov[j + 1], val1);
		vrstice[j + 1] = val2;
	}
}
