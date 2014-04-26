#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


#define SIZE 100
// funkcije sklada
int velicina(double *sklad); // vrne velikost sklada
void enlarge(double *array); // 
void push(double *sklad, double stevilo);
double pop(double *sklad);
double top(double *sklad);
void print(double *sklad);
// funkcije kalkulatorja
void enoparametricne(double *sklad, char *tmp);
void dvoparametricne(double *sklad, char *tmp);

int usedSpace;
int size;

int main()
{
	usedSpace = -1;
	size = SIZE;
	double *sklad;
	sklad = (double*) malloc(sizeof(double) * SIZE);
	char preberi[101];
	
	// srce programa
	while(scanf("%s\n",&(preberi[0])) > 0)
	{
		// vse dvoparametricne operacije
		if(strcmp(preberi,"+") == 0 || strcmp(preberi,"-") == 0 || 
			strcmp(preberi,"*") == 0 || strcmp(preberi,"/") == 0 || 
				strcmp(preberi,"^") == 0 || strcmp(preberi,"mod") == 0 ||
					strcmp(preberi,"xchg") == 0)
		{
			dvoparametricne(sklad, preberi);
		}
		// vse enoparametricne operacije
		else if (strcmp(preberi,"inv") == 0 || strcmp(preberi,"dup") == 0 ||
					strcmp(preberi,"drop") == 0 || strcmp(preberi,"sqrt") == 0 ||
						strcmp(preberi,"sin") == 0 || strcmp(preberi,"cos") == 0 ||
							strcmp(preberi,"tan") == 0 || strcmp(preberi,"log") == 0 || 
								strcmp(preberi,"ln") == 0)
		{
			enoparametricne(sklad, preberi);
		}
		// printaj zgornji element
		else if(strcmp(preberi,"print") == 0)
		{
			printf("%lf\n",top(sklad));
		}
		// dodaj konstanto e
		else if(strcmp(preberi,"e") == 0)
		{
			push(sklad, M_E);
		}
		// dodaj konstanto pi
		else if(strcmp(preberi,"pi") == 0)
		{
			push(sklad, M_PI);
		}
		// dodaj stevilo
		else
		{
			push(sklad, atof(preberi));
		}
	}
		
	return 0;
}

void print(double *sklad)
{
	for(int i = 0; i < usedSpace + 10; i++)
	{
		printf("%lf ", sklad[i]);
	}
	printf("\n");
}

void dvoparametricne(double *sklad, char *tmp)
{
	if (velicina(sklad) < 1) {
		printf("ERR\n");
		return;
	}
	double x = pop(sklad);
	double y = pop(sklad);
	if(strcmp(tmp,"+") == 0) {
		push(sklad, y + x);
	} else if (strcmp(tmp,"-") == 0) {
		push(sklad, y - x);
	} else if (strcmp(tmp,"*") == 0) {
		push(sklad, y * x);
	} else if (strcmp(tmp,"/") == 0) {
		push(sklad, y / x);
	} else if (strcmp(tmp,"^") == 0) {
		push(sklad, pow(y, x));
	} else if (strcmp(tmp,"mod") == 0) {
		push(sklad, fmod(y, x));
	} else if (strcmp(tmp,"xchg") == 0) {
		push(sklad, x);
		push(sklad, y);
	}
}

void enoparametricne(double *sklad, char *tmp)
{
	if(velicina(sklad) < 0) {
		printf("ERR\n");
		return;
	}
	double x = pop(sklad);
	if (strcmp(tmp,"inv") == 0) {
		push(sklad, 1.0/x);
	} else if(strcmp(tmp,"dup") == 0) {
		push(sklad, x);
		push(sklad, x);
	} else if(strcmp(tmp,"drop") == 0) {
		// ze narejeno
		// do nothing
	} else if(strcmp(tmp,"sqrt") == 0) {
		push(sklad, sqrt(x));
	} else if(strcmp(tmp,"sin") == 0) {
		push(sklad, sin(x));
	} else if(strcmp(tmp,"cos") == 0) {
		push(sklad, cos(x));
	} else if(strcmp(tmp,"tan") == 0) {
		push(sklad, tan(x));
	} else if(strcmp(tmp,"log") == 0) {
		push(sklad, log10(x));
	} else if(strcmp(tmp,"ln") == 0) {
		push(sklad, log(x));
	}
}

int velicina(double *sklad)
{
	if(usedSpace == 0) {
		return 1;
	} else {
		return usedSpace;
	}
}

void enlarge(double *array)
{
	size = size + SIZE;
	array = (double*) realloc(array, sizeof(double) * size);
}

void push(double *sklad, double stevilo)
{
	if(usedSpace == (size - 1))
	{
		enlarge(sklad);
	}
	if(usedSpace < 0)
	{
		usedSpace = 0;
	}
	sklad[usedSpace] = stevilo;
	usedSpace++;
}

double pop(double *sklad)
{
	double tmp = sklad[usedSpace - 1];
	usedSpace--;
	return tmp;
}

double top(double *sklad)
{
	if (usedSpace <= 0)
	{
		return sklad[0];	
	}
	else
	{
		return sklad[usedSpace - 1];
	}

}
