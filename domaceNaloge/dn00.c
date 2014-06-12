
/*
	Napišite program, ki iz standardnega vhoda prebere pozitivno celo število 
	in na standardni izhod izpiše Y, če je prebrano število praštevilo, in N sicer.
	Izhodna koda programa naj bo vedno 0.
*/

#include <stdio.h>

int main(int argc, char *argv[])
{
	int stevilo, preveri;
	// preberi število
	scanf("%d", &stevilo);

	preveri = 0; // 0 = false, 1 = true

	// če je število sodo potem ni praštevilo,
	// če je liho, potem obstaja možnost da je praštevilo
	if (stevilo % 2 == 0)
	{
		printf("N");
	}
	else
	{
		// isPrime?
		for(int i = 2; i < stevilo/2; i++)
		{
			if (stevilo % i == 0)
			{
				preveri = 1;
				break;
			}
		}
		
		// izpiši rezultat
		if (preveri == 0)
		{
			printf("Y");
		}
		else
		{
			printf("N");
		}
	}

	return 0;
}
