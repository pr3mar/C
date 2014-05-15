#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struktura plovbe
typedef struct _plovba {
	char* zacetek;
	char* konec;
	int trajanje;
	int stVkrcani;
	int stIzkrcani;
	struct _plovba* naslednji;
} plovba, *ptrPlovba;

// funkcije za delanje z plovbami
ptrPlovba dodajZ(ptrPlovba prviEl, char* zacetek, char* konec, int trajanje, int vkrcani, int izkrcani);
void print(ptrPlovba e);
void freeNode(ptrPlovba e);
ptrPlovba findLast(ptrPlovba prviEl);
ptrPlovba izloci(ptrPlovba prviEl, ptrPlovba outer);
ptrPlovba izbrisi(ptrPlovba prviEl, char* iskKonec);
ptrPlovba find(ptrPlovba prviEl, char *zacetek);
void poisciDan(ptrPlovba zacetek, int dan);

// glavna funkcija 
int main()
{
	ptrPlovba prviEl = NULL, tmp = NULL;
	char zacetek[105], konec[105];
	int dnevi, vkrcani, izkrcani;

	while(scanf("%s\n", zacetek) > 0 && strcmp(zacetek,"?") != 0)
	{
		scanf("%s\n%d\n%d\n%d\n", konec, &dnevi, &vkrcani, &izkrcani);
		prviEl = dodajZ(prviEl, zacetek, konec, dnevi, vkrcani, izkrcani);
	}
	// poisci zadnji element
	prviEl = findLast(prviEl);
	// reverse sort tabelo
	tmp = find(prviEl, prviEl -> zacetek);
	while(tmp != NULL)
	{
		prviEl = izloci(prviEl, tmp);
		tmp = find(prviEl, prviEl -> zacetek);
	}
	// preberi dan in poisci kje se nahaja
	int dan;
	while (scanf("%d\n", &dan) > 0)
	{
		poisciDan(prviEl, dan);
	}
	// oslobodi pomnilnik
	freeNode(prviEl);
	return 0;
}
// poisci polozaj ladje
void poisciDan(ptrPlovba zacetek, int dan)
{
	ptrPlovba tmp = zacetek;
	int potovanje = 0;
	int potniki = 0;
	while (tmp != NULL)
	{
		potovanje += tmp -> trajanje;
		potniki += tmp -> stVkrcani;
		if (dan <= potovanje)
		{
			printf("%d %s - %s %d\n", dan, tmp -> zacetek, tmp -> konec, potniki);
			break;
		}
		potniki -= tmp -> stIzkrcani;
		tmp = tmp -> naslednji;
	}
	if (dan > potovanje)
	{
		printf("%d NAPAKA\n", dan);
	}
}
// poisci element
ptrPlovba find(ptrPlovba prviEl, char *konec)
{
	if (prviEl == NULL)
	{
		return NULL;	
	}
	else
	{
		if (strcmp(prviEl -> konec, konec) == 0 )
		{
			return prviEl;
		}
		else
		{
			return find(prviEl -> naslednji, konec);
		}
	}

}

// poisci zadnji element
ptrPlovba findLast(ptrPlovba prviEl)
{
	ptrPlovba outer = prviEl;
	ptrPlovba inner = prviEl;
	int countKon, countZac;

	while (outer != NULL) 
	{
		inner = prviEl;
		countKon = 0;
		countZac = 0;
		while (inner != NULL)
		{
			if (strcmp(inner->konec, outer->konec) == 0)
			{
				countKon++;
			}
			if(strcmp(inner->zacetek, outer->konec) == 0)
			{
				countZac++;
			}
			inner = inner -> naslednji;
		}
		if(countKon == 1 && countZac == 0)
		{
			prviEl = izloci(prviEl, outer);
			break;
		}
		outer = outer -> naslednji;
	}
	return prviEl;
}

// izloci -> doda element za brisanje na zacetek
ptrPlovba izloci(ptrPlovba prviEl, ptrPlovba outer)
{
	char *zac, *kon;
	int tr, vkr, izkr;
	
	zac = (char *) malloc(sizeof(char) * (strlen(outer->zacetek) + 1));
	strcpy(zac, outer -> zacetek);
	kon = (char *) malloc(sizeof(char) * (strlen(outer->konec) + 1));
	strcpy(kon, outer -> konec);
	tr = outer -> trajanje;
	vkr = outer -> stVkrcani;
	izkr = outer -> stIzkrcani;
	
	prviEl = izbrisi(prviEl, outer -> konec);
	prviEl = dodajZ(prviEl, zac, kon, tr, vkr, izkr);
	return prviEl;
}

// izbrise element
ptrPlovba izbrisi(ptrPlovba prviEl, char* iskKonec)
{
	if(prviEl == NULL) return NULL;
	if (strcmp(prviEl -> konec, iskKonec) == 0) 
	{
		ptrPlovba tmp = prviEl;
		prviEl = prviEl -> naslednji;
		free(tmp->zacetek);
		free(tmp->konec);
		free(tmp);
		tmp = NULL;
		return prviEl;
	}
	else
	{
		ptrPlovba zacRepa = izbrisi(prviEl->naslednji, iskKonec);
		prviEl -> naslednji = zacRepa;
		return prviEl;
	}
}

// dodaj element na zacetku
ptrPlovba dodajZ(ptrPlovba prviEl, char* zacetek, char* konec, int trajanje, int vkrcani, int izkrcani)
{
	ptrPlovba nov = (ptrPlovba) malloc(sizeof(plovba));
	char *zac = (char*) malloc(sizeof(char) * (strlen(zacetek) + 1));
	strcpy(zac,zacetek);
	char *kon = (char*) malloc(sizeof(char) * (strlen(konec) + 1));
	strcpy(kon,konec);

	nov -> naslednji = prviEl;
	nov -> zacetek = zac;
	nov -> konec = kon;
	nov -> trajanje = trajanje;
	nov -> stVkrcani = vkrcani;
	nov -> stIzkrcani = izkrcani;

	return nov;
}
// printaj vse naprej od e
void print(ptrPlovba e)
{
	printf("\n");
	while(e != NULL)
	{
		printf("%s %s %d %d %d\n", e->zacetek, e->konec, e->trajanje, e->stVkrcani, e->stIzkrcani);
		e = e-> naslednji;
	}
}

// oslobodi pomnilnik
void freeNode(ptrPlovba e)
{
	while (e != NULL)
	{
		ptrPlovba tmp = e;
		e = e -> naslednji;
		free(tmp->zacetek);
		free(tmp->konec);
		free(tmp);
		tmp = NULL;
	}
}
