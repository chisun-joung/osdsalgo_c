#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
   int data;
   struct _node *next;
} NODE;

NODE *head;

void insert_data( int data )
{
   NODE *temp;
   temp = malloc( sizeof(NODE) );
   temp->data = data;
   temp->next = head;
   head = temp;
}
//---------------------------------------------------

void display( void )
{
	NODE *temp;
	system("cls");
	printf("head");
	for( temp = head; temp; temp = temp->next )
		printf("->[%d]", temp->data );
	printf("\n");
	getchar();
}

int main()
{
	int i;
	display();
	for(i=0; i<7; i++ )
	{
		insert_data(i+1);
		display();
	}
	return 0;
}

