#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
   struct _node *next;
   struct _node *prev;
} NODE;

void __insert_data( NODE *temp, NODE *prev, NODE *next )
{
   temp->next = next;
   prev->next = temp;
   temp->prev = prev;
   next->prev = temp;
}

void insert_front( NODE *temp, NODE *head )
{
   __insert_data( temp, head, head->next );
}

void insert_back( NODE *temp, NODE *head )
{
   __insert_data( temp, head->prev, head );
}

//---------------------------------------------------

typedef struct
{
	char name[20];
	NODE list;
} SAWON;

void display( NODE *head )
{
	NODE *temp;
	SAWON *s;
	system("cls");
	printf("[head]");
	for( temp = head->prev; temp != head ; temp = temp->prev )
	{
		s = (SAWON*)((char*)temp - 20);
		printf("<->[%s]", s->name ); 
	}
	printf("<->[head]\n");
	getchar();
}

int main()
{
	int i;
	NODE head={&head,&head};
	SAWON s[2] = {{"ȫ�浿",}, {"�Ӳ���",}};
	display(&head);
	for(i=0; i<2; i++ )
	{
		insert_back(&s[i].list, &head);
		display(&head);
	}
	return 0;
}

