#include <stdio.h>
#include <stdlib.h>

struct hlist_head {
	struct hlist_node *first;
};

struct hlist_node {
	struct hlist_node *next, **pprev;
};

void hlist_add_head(struct hlist_node *n, struct hlist_head *h)
{
	struct hlist_node *first = h->first;
	n->next = first;
	if (first)
		first->pprev = &n->next;
	h->first = n;
	n->pprev = &h->first;
}

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

#define hlist_entry(ptr, type, member) \
	container_of(ptr, type, member)
//-------------------------------------------------------------
typedef struct
{
      int sid;
      struct hlist_node hash;
} SAWON;

void display( struct hlist_head *heads )
{
	int i;
	struct hlist_node *temp;
	SAWON *s;
	system("cls");
	for(i=0; i<8; i++ )
	{
		printf("[%d]", i);
		for( temp = heads[i].first; temp ; temp = temp->next )
		{
			s = hlist_entry( temp , SAWON, hash );
			printf("<->[%d]", s->sid ); 
		}
		printf("\n");
	}
	getchar();
}
int main()
{
	struct hlist_head heads[8] = {0,};
	SAWON s[30];
	int i;
	display( heads );
	for(i=0; i<30; i++ )
	{
		s[i].sid = 1000+i;
		hlist_add_head(&s[i].hash, &heads[s[i].sid%8]);
		display( heads );
	}
	
	return 0;
}












