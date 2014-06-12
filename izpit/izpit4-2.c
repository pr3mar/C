#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct node {
	int value;
	struct node *next;
} node, *ptrNode;

node *add(node *original, int value);
node *addEnd(node *original, int value);
void print(node *original);
node *kopija(node *original);

int main()
{
	node *test = NULL;
	for(int i = 1; i <= 5; i++) {
		test = add(test, i);
	}
	printf("%10s ", "original:");
	print(test);
	test = kopija(test);
	printf("%10s ", "copied:");
	print(test);
	return 0;
}

node *kopija(node *original) {
	node *tmp = NULL;
	node *buff = original;
	while(buff -> next != NULL) {
		tmp = addEnd(tmp, buff -> value);
		buff = buff -> next;
	}
	tmp = addEnd(tmp, buff -> value);
	buff -> next = tmp;
	return original;
}

node *addEnd(node *original, int value) {
	if(original == NULL) {
		node *tmp = (node*) malloc(sizeof(node));
		tmp -> value = value;
		tmp -> next = NULL;
		return tmp;
	} else {
		original -> next = addEnd(original -> next, value);
		return original;
	}
}

node *add(node *original, int value) {
	node *tmp = (node*) malloc(sizeof(node));
	tmp -> value = value;
	if(original == NULL) {
		tmp -> next = NULL;
	} else {
		tmp -> next = original;
	}
	return tmp;
}

void print(node *original) {
	node *tmp = original;
	while(tmp != NULL) {
		printf("%d ", tmp -> value);
		tmp = tmp -> next;
	}
	printf("\n");
}