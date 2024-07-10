#include <stdio.h>
#include <stdlib.h>

struct node{
	int value;
	struct node *next;
};

struct node *head1 = NULL;
struct node *head2 = NULL;
struct node *tail1 = NULL;
struct node *tail2 = NULL;

void showList(struct node *head){
	struct node *Node = (struct node *)malloc(sizeof(struct node));
	Node = head;
	while(Node != NULL){
		printf("%d -> ", Node->value);
		Node = Node->next;
	}
	printf("NULL\n");
}

void addFront(int val){
	struct node *new = (struct node *)malloc(sizeof(struct node));
	
	new->value = val;
	new->next = head1;
	head1 = new;

	if(tail1 == NULL){
		tail1 = head1;
	}
}

void addEnd(int val){
	struct node *new = (struct node *)malloc(sizeof(struct node));
	
	new->value = val;
	new->next = NULL;
	
	if(head2 == NULL){
		head2 == new;
		return;
	}
	
	struct node* temp = head2;
	while(temp != NULL){
		temp = temp->next;
	}
	temp->next = new;
}

int main(){

	int val;
	while(scanf("%d", &val) != EOF){
		addFront(val);
		addEnd(val);
	}
	printf("Linked list in reversed order\n");
	printf("-----------------------------\n");
	showList(head1);

	printf("\nLinked list in order");
	printf("\n--------------------\n");
	showList(head2);
	return 0;
}
