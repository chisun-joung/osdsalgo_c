#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
   int data;
   struct _node *next;
} NODE;

NODE head;

void insert_data( NODE *temp, NODE *head )
{
   temp->next = head->next;
   head->next = temp;
}
//---------------------------------------------------

void display( NODE *head )
{
	NODE *temp;
	system("cls");
	printf("[head]");
	for( temp = head->next; ; temp = temp->next )
		printf("->[%d]", temp->data );  // (*0).data
	printf("\n");
	getchar();
}

int main()
{
	int i;
	NODE temps[7];
	display(&head);
	for(i=0; i<7; i++ )
	{
		temps[i].data = i+1;
		insert_data(temps+i, &head);
		display(&head);
	}
	return 0;
}

