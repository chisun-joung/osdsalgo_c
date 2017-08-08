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

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

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
		//s = (SAWON*)((char*)temp - 20);
		//s = (SAWON*)((char*)temp - ( sizeof(SAWON)-sizeof(NODE) ));
		//s = (SAWON*)((char*)temp - (unsigned long)&((SAWON*)0)->list );
		s = list_entry( temp , SAWON, list );
		printf("<->[%s]", s->name ); 
	}
	printf("<->[head]\n");
	getchar();
}

int main()
{
	int i;
	NODE head={&head,&head};
	SAWON s[2] = {{"È«±æµ¿",}, {"ÀÓ²©Á¤",}};
	display(&head);
	for(i=0; i<2; i++ )
	{
		insert_back(&s[i].list, &head);
		display(&head);
	}
	return 0;
}

