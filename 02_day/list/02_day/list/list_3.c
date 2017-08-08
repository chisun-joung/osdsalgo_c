#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
   int data;
   struct _node *next;
} NODE;

NODE head;

void insert_data( int data, NODE *head )
{
   NODE *temp;
   temp = malloc( sizeof(NODE) );
   temp->data = data;
   temp->next = head->next;
   head->next = temp;
}
//---------------------------------------------------

void display( NODE *head )
{
	NODE *temp;
	system("cls");
	printf("[head]");
	for( temp = head->next; temp; temp = temp->next )
		printf("->[%d]", temp->data );
	printf("\n");
	getchar();
}

int main()
{
	int i;
	display(&head);
	for(i=0; i<7; i++ )
	{
		insert_data(i+1, &head);
		display(&head);
	}
	return 0;
}

