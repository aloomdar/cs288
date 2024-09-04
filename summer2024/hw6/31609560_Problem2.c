#include <stdio.h>
#include <stdlib.h>

struct node{
	int value;
	struct node *next;
};

struct node *head = NULL;
struct node *tail = NULL;

struct node *createNode(int val){
	struct node *new = (struct node *)malloc(sizeof(struct node));
	new->value = val;
	new->next = NULL;
	return new;
}

void addBegin(int val){
	struct node *new = createNode(val);
	
	new->next = head;
	head = new;
	if(tail == NULL){
		tail = head;
	}
}

struct node *swap(struct node *a, struct node *b){
	struct node *temp = b->next;
	b->next = a;
	a->next = temp;
	return b;
}

void bubbleSort(struct node **head, int n){
	struct node **temp;
	int swapped;
	
	for(int i = 0; i <= n; i++){
		temp = head;
		swapped = 0;
		for(int j = 0; j < n - i - 1; j++){
			struct node *p1 = *temp;
			struct node *p2 = p1->next;
			if(p1->value > p2->value){
				*temp = swap(p1, p2);
				swapped = 1;
			}
			temp = &(*temp)->next;
		}
		if(swapped == 0){
			break;
		}
	}
}

int main(){
	printf("Enter integer values: \n");
	int val, n = 0;
	while(scanf("%d", &val) != EOF){
		addBegin(val);
		n++;
	}
	
	bubbleSort(&head, n);
	printf("\nSorted\n");
	struct node *p = head;
	while(p != NULL){
		printf("%d\n", p->value);
		p = p->next;
	}
	return 0;
}
