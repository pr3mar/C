/*
  Napišite program, ki v zaporedju podatih števil uredi soda števila v naraščajočem vrstnem redu, liha števila pa pusti pri miru.

  Program naj najprej prebere dolžino zaporedja (največ 100), nato pa posamezna števila.
  Primer: Vsebina vhoda
  7 4 3 6 1 4 2 9
  pomeni, da je v zaporedju 7 števil, ta števila pa so po vrsti 4, 3, 6, 1, 4, 2 in 9.
  Program naj izpiše preurejeno zaporedje, vendar brez dolžine:
  2 3 4 1 4 6 9
  Torej, liha števila ostanejo na svojih mestih, soda so urejena po vrsti.
  Števila naj bovo med seboj ločena s presledki, zadnjemu številu sledita še presledek in znak za skok v novo vrstico.
*/

#include <stdio.h>
#define velicina 100


void izpisi(int *pTabela, int stElementov);

void urediNavadno(int *pTabela, int stElementov);

void uredi(int *pTabela, int stElementov);

void swap(int *x, int *y);

int main()
{
	int stElementov;
	int tabela[velicina];
	int i;
	scanf("%d", &stElementov);
	for(i = 0; i < stElementov; i++)
	{
		scanf("%d", &tabela[i]);
	}
	
	//izpisi(tabela, stElementov);
	//urediNavadno(tabela, stElementov);
	//izpisi(tabela, stElementov);
	uredi(tabela, stElementov);
	izpisi(tabela, stElementov);

	return 0;
}

void izpisi(int *pTabela, int stElementov)
{
	for(int i = 0; i < stElementov; i++)
	{
		printf("%d ", pTabela[i]);
	}
	printf("\n");
}
// zamenjaj 2 vrednosti
void swap(int *x, int *y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}
// uredi po naraščajočem vrstnem redu
void urediNavadno(int *pTabela, int stElementov)
{
	int i, j;
	for(i = 0; i < stElementov; i++)
	{
		for(j = 0; j < stElementov; j++)
		{
			if( pTabela[i] > pTabela[j])
			{
				swap(&pTabela[i], &pTabela[j]);
			}
		} 
	}
}
// uredi le soda števila po naraščajočem vrstnem redu
void uredi(int *pTabela, int stElementov)
{
	int i, j;
	for(i = 0; i < stElementov; i++)
	{
		if(pTabela[i] % 2 == 0)
		{
			for(j = 0; j < stElementov; j++)
			{
				if (pTabela[j] % 2 == 0)
				{
					if( pTabela[i] < pTabela[j])
					{
						swap(&pTabela[i], &pTabela[j]);
					}
				}
			}
		}
		else
		{
			continue;
		} 

	}
}
