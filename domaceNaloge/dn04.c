#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_ZIVIH 1000
#define MAX_GLASOVOV 9001
#define SOSEDNOST 8

int matrika[100][100];

int stGeneracij;
int stZivih;
int zivi[MAX_ZIVIH][3];
int glasovi[MAX_GLASOVOV][3];
int noviZivi[MAX_ZIVIH][3];

int sosedi;
int stej;
// 8 sosednost
int sosednost[8][2] = {
	{	0,   1}, // -> desno
	{	0,  -1}, // -> levo
	{	1,   0}, // -> gor
	{  -1,	 0}, // -> dol
	{	1,	 1}, // -> gor, desno
	{	1,  -1}, // -> gor, levo
	{  -1,	 1}, // -> dol, desno
	{  -1,  -1}  // -> dol, levo
};

void najdiSosede();
void sosed(int x, int y);

void prestejSosede();
int poisciTocko(int array[MAX_GLASOVOV][3], int velikost, int x, int y);

void dodajNovim(int x, int y, int vnosi);

void polni();
void printaj();

int main()
{
	// get input
	scanf("%d", &stGeneracij); 	// get generations
	scanf("%d", &stZivih); 		// get alive
	for(int i = 0; i < stZivih; i++)
	{
		scanf("%d %d",&(zivi[i][0]), &(zivi[i][1]));
		zivi[i][2] = 0;
	}
		polni();
	sosedi = 0;	stej = 0;
	for (int i = 0; i  < stGeneracij; i++)
	{
		sosedi = 0; stej = 0;
		najdiSosede();
		prestejSosede();
		stZivih = stej;
		memcpy(zivi, noviZivi, sizeof(zivi));
		polni();
	}
	
	if (stZivih == 0) 
	{
		printf("0\n");
	} 
	else 
	{
		int minV, maxV, minS, maxS;
		minV = zivi[0][0]; maxV = zivi[0][0];
		minS = zivi[0][1]; maxS = zivi[0][1];
		for(int i = 1; i < stZivih; i++)
		{
			if(zivi[i][0] < minV) minV = zivi[i][0];
			if(zivi[i][0] > maxV) maxV = zivi[i][0];
			if(zivi[i][1] < minS) minS = zivi[i][1];
			if(zivi[i][1] > maxS) maxS = zivi[i][1];
		}
		printf("%d %d %d %d %d\n", stZivih, minV, maxV, minS, maxS);
	}
	return 0;
}

void najdiSosede()
{
	for(int i = 0; i < stZivih; i++)
	{
		sosed(zivi[i][0], zivi[i][1]);
	}
}

void sosed(int x, int y)
{
	for(int i = 0; i < SOSEDNOST; i++, sosedi++)
	{
		glasovi[sosedi][0] = x + sosednost[i][0];
		glasovi[sosedi][1] = y + sosednost[i][1];
		glasovi[sosedi][2] = 0;
	}
}

void prestejSosede()
{
	int j = 0;
	for(int i = 0; i < sosedi; i++)
	{
		int tmp = 0;
		if(glasovi[i][2] == 0)
		{
			tmp = poisciTocko(glasovi, sosedi, glasovi[i][0], glasovi[i][1]);
			if( (tmp == 2 || tmp == 3) && (glasovi[i][2] == 0)) 
			{
				//printf("%2d. = %2d %2d -> %2d (%d)\n",(j + 1),glasovi[i][0], glasovi[i][1], tmp, glasovi[i][2]);
				dodajNovim(glasovi[i][0], glasovi[i][1], tmp);
				j++;
			}
		}

	}
	//printf("\nsosedi->%d\nst novih->%2d\n\n", sosedi, j);
}

int poisciTocko(int array[MAX_GLASOVOV][3], int velikost, int x, int y)
{
	int krat = 0;
	for(int i = 0; i < velikost; i++)
	{
		if (array[i][0] == x && array[i][1] == y)
		{
			if (krat >= 1) { glasovi[i][2] = 1; }
			krat++;
		}
	}
	return krat;
}

void dodajNovim(int x, int y, int vnosi)
{
	int obstaja = poisciTocko(noviZivi, (stej + 1), x, y);
	int ziva = poisciTocko(zivi, stZivih, x, y);
	if (obstaja == 0)
	{
		if (vnosi == 3)
		{
			noviZivi[stej][0] = x;
			noviZivi[stej][1] = y;
			noviZivi[stej][2] = 0;
			stej++;
		} 
		else if (vnosi == 2 && ziva != 0)
		{
			noviZivi[stej][0] = x;
			noviZivi[stej][1] = y;
			noviZivi[stej][2] = 0;
			stej++;
		}
	}
}

void polni()
{
	for (int i = 0; i < MAX_ZIVIH; i++)
	{
		noviZivi[i][0] = INT_MIN;
		noviZivi[i][1] = INT_MIN;
	}
}
