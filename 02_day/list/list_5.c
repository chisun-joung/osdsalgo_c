#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
   int data;
   struct _node *next;
} NODE;

NODE tail={0,&tail};
NODE head={0,&tail};

void insert_data( NODE *temp, NODE *head )
{
   temp->next = head->next;
   head->next = temp;
}
//---------------------------------------------------

void display( NODE *head , NODE *tail)
{
	NODE *temp;
	system("cls");
	printf("[head]");
	for( temp = head->next; temp != tail ; temp = temp->next )
		printf("->[%d]", temp->data );  // (*0).data
	printf("->[tail]\n");
	getchar();
}

int main()
{
	int i;
	NODE temps[7];
	display(&head, &tail);
	for(i=0; i<7; i++ )
	{
		temps[i].data = i+1;
		insert_data(temps+i, &head);
		display(&head, &tail);
	}
	return 0;
}

