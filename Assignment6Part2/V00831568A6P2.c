#include <stdlib.h>
#include <stdio.h>

typedef struct node{
	int data;
	struct node* next;
}node;

int main(){
	node* head;
	node* through;
	head = (node*)malloc(sizeof(node));
	head->next = 0;
	head->data = 12;
	through = head;
	while(through->next != NULL){
		through = through->next;
		printf("%d", through->data);
	}

	return EXIT_SUCCESS;
}
