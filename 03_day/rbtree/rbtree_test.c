#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

typedef struct
{
	int sid;
	struct rb_node tree;
} SAWON;

typedef struct
{
	int sid;
	int color;
} INFO;

SAWON * rb_insert_sid(struct rb_root * root, int sid, struct rb_node * node)
{
	struct rb_node ** p = &root->rb_node;
	struct rb_node * parent = NULL;
	SAWON *s;

	while (*p)
	{
		parent = *p;
		s = rb_entry(parent, SAWON, tree);

		if (sid < s->sid)
			p = &(*p)->rb_left;
		else if (sid > s->sid)
			p = &(*p)->rb_right;
		else
			return s;
	}

	rb_link_node(node, parent, p);  // *p = node;
	rb_insert_color(node, root);

	return NULL;
}

void __display(struct rb_node *temp, INFO (*a)[10], int *row, int *col )
{
   int i;
   if( temp == 0 )
      return;
   ++*row;
   __display(temp->rb_left, a, row, col);
   a[*row][*col].color = rb_color(temp);
   a[*row][(*col)++].sid = rb_entry(temp,SAWON,tree)->sid;
   __display(temp->rb_right, a, row, col);
   --*row;
} 

void display( struct rb_root *root )
{
	int i,j;
	INFO a[10][10]={0,};
	int row=-1, col=0;
	system("cls");
	__display( root->rb_node, a, &row, &col );
	for(i=0; i<10; i++ )
	{
		for(j=0; j<10; j++ )
		{
			if( a[i][j].sid )
			{
				if( a[i][j].color == RB_RED )
					printf("<%2d>", a[i][j].sid );
				else 
					printf("[%2d]", a[i][j].sid );
			}
			else
				printf("%4c", ' ' );
		}
		printf("\n");
	}
	getchar();
}

int main()
{
	int i;
	SAWON s[8];
	struct rb_root root = {0};
	display(&root);
	for( i=0; i<8; i++ )
	{
		s[i].sid = i+1;
		rb_insert_sid(&root, i+1, &s[i].tree);
		display(&root);
	}
	return 0;
}

