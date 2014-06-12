#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _file{
	int length;
	int price;
	struct _file *next;
} strFile, *ptrFile;

ptrFile add(ptrFile first, int length, int price);
ptrFile addOrdered(ptrFile first, int length, int price);
ptrFile merge(ptrFile first, ptrFile second);
void print(ptrFile printIt);
int solution(ptrFile list, int maxStorage);

int main()
{
	int tmp1, tmp2;
	int maxStorage;
	int maxValue = 0;
	ptrFile list = NULL;
	scanf("%d\n", &maxStorage);
	while(scanf("%d %d", &tmp1, &tmp2) > 0) {
		list = add(list, tmp1, tmp2);
	}
	maxValue = solution(list, maxStorage);
	printf("%d\n", maxValue);
	return 0;
}

int solution(ptrFile list, int maxStorage) {
	int maxValue = 0;
	ptrFile neDodaj = NULL, dodaj = NULL;
	neDodaj = add(neDodaj, 0, 0);
	ptrFile tmp = list, buff;
	int tmpValue = 0, tmpStorage = 0;
	while(tmp != NULL) {
		buff = neDodaj;
		while(buff != NULL) {
			tmpValue = (tmp -> price) + (buff -> price);
			tmpStorage = (tmp -> length) + (buff -> length);
			if(tmpStorage <= maxStorage) {
				dodaj = add(dodaj, tmpStorage, tmpValue);
				if(tmpValue > maxValue) {
					maxValue = tmpValue;
				}
			}
			buff = buff -> next;
		}
		neDodaj = merge(neDodaj, dodaj);
		dodaj = NULL;
		tmp = tmp -> next;
	}
	return maxValue;
}

ptrFile merge(ptrFile first, ptrFile second) {
	ptrFile tmp1 = first, tmp2 = second;
	ptrFile merged = NULL;
	while( tmp1 != NULL || tmp2 != NULL) {
		if(tmp1 != NULL) {
			merged = addOrdered(merged, tmp1 -> length, tmp1 -> price);
			tmp1 = tmp1 -> next;
		} else if(tmp2 != NULL) {
			merged = addOrdered(merged, tmp2 -> length, tmp2 -> price);
			tmp2 = tmp2 -> next;
		}
	}
	return merged;
}

ptrFile add(ptrFile first, int length, int price) {
	ptrFile tmp = (ptrFile) malloc(sizeof(strFile));
	tmp -> length = length;
	tmp -> price = price;
	tmp -> next = first;
	return tmp;
}

ptrFile addOrdered(ptrFile first, int length, int price) {
	if(first == NULL) {
		ptrFile tmp = (ptrFile) malloc(sizeof(strFile));
		tmp -> length = length;
		tmp -> price = price;
		tmp -> next = first;
		return tmp;
	} else if((first -> length) < length) {
		first -> next = addOrdered(first -> next, length, price);
		return first;
	} else if ((first -> length) == length) {
		if((first -> price) > price) {
			return first;
		} else {
			first -> price = price;
			return first;
		}
	} else if((first -> price) == price) {
		if((first -> length) > length) {
			return first;
		} else {
			first -> length = length;
			return first;
		}
	} else {
		ptrFile tmp = (ptrFile) malloc(sizeof(strFile));
		tmp -> length = length;
		tmp -> price = price;
		tmp -> next = first;
		return tmp;
	}

}

void print(ptrFile printIt) {
	while(printIt != NULL) {
		printf("[%d, %d]\n", printIt -> length, printIt -> price);
		printIt = printIt -> next;
	}
	printf("=====================\n");
}
