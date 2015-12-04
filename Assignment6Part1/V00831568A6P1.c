#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node* NodeRef;

typedef struct Node {
	int data;
	NodeRef next;
} Node;

int main(){
	NodeRef A = (NodeRef) malloc(sizeof(Node));
	NodeRef B = (NodeRef) malloc(sizeof(Node));
	NodeRef C = (NodeRef) malloc(sizeof(Node));

	NodeRef Slist = A;

	A->data = 1;
	B->data = 2;
	C->data = 3;

	A->next = B;
	B->next = C;
	C->next = NULL;

	while (Slist->next != NULL){
		printf("%d", Slist->data);
		Slist = Slist->next;
	}

	return 0;
}
