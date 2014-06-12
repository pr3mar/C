#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAXLEN 20

void crke(char *pass, int len, int used, int noChars, int noNums);

int main()
{
	char *pass = (char *) malloc(sizeof(char) * MAXLEN);
	for(int i = 20; i <= MAXLEN; i += 2) {
		crke(pass, i, 0, 0, 0);
	}
	return 0;
}

void crke(char *pass, int len, int used, int noChars, int noNums) {
	if (len == used) { // print
		for(int i = 0; i < len; i++) {
			printf("%c", pass[i]);
		}
		printf("\n");
	} else { // generate chars
		if(noChars < (len / 2)) {
			for(int i = 'a'; i <= 'b'; i++) {
				pass[used] = i;
				crke(pass, len, used + 1, noChars + 1, noNums);
			}
		}
		if(noNums < (len / 2)) {
			for(int i = '0'; i <= '1'; i++) {
				pass[used] = i;
				crke(pass, len, used + 1, noChars, noNums + 1);
			}
		}
	}
}