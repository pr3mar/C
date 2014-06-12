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
void print(node *original);
node *obratno(node *prviEl);

int main()
{
	node *test = NULL;
	for (int i = 1; i <= 5; i++) {
		test = add(test, i);
	}
	printf("originalna: \n");
	print(test);
	test = obratno(test);
	printf("obratna: \n");
	print(test);
	return 0;
}

node *obratno(node *prviEl) {
	node *obratniEl = NULL;
	node *tmp = prviEl;
	while(tmp != NULL) {
		obratniEl = add(obratniEl, tmp -> value);
		tmp = tmp -> next;
	}
	return obratniEl;
}

node *add(node *original, int value) {
	if (original == NULL) {
		original = (node*) malloc(sizeof(node));
		original -> value = value;
		original -> next = NULL;
		return original;
	} else {
		node *tmp = (node*) malloc(sizeof(node));
		tmp -> value = value;
		tmp -> next = original;
		return tmp;
	}
}

void print(node *original) {
	node *tmp = original;
	while(tmp != NULL) {
		printf("%d ", tmp -> value);
		tmp = tmp -> next;
	}
	printf("\n");
}