#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbtree.h"

typedef struct
{
	char name[20];
	int  augmented;
	struct rb_node tree;
} SAWON;

typedef struct
{
	char name[20];
	int  augmented;
	int color;
} INFO;

SAWON * rb_insert_name(struct rb_root * root, char *name, struct rb_node * node)
{
	struct rb_node ** p = &root->rb_node;
	struct rb_node * parent = NULL;
	SAWON *s;

	s = rb_entry(node, SAWON, tree);
	s->augmented = 1;

	while (*p)
	{
		parent = *p;
		s = rb_entry(parent, SAWON, tree);
		s->augmented++;

		if (strcmp( name , s->name ) < 0 )
			p = &(*p)->rb_left;
		else if (strcmp( name , s->name ) > 0 )
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
   a[*row][*col].color = temp->__rb_parent_color & 1 ;
   a[*row][*col].augmented = rb_entry(temp,SAWON,tree)->augmented ;
   strcpy(a[*row][(*col)++].name , rb_entry(temp,SAWON,tree)->name);
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
			if( strlen(a[i][j].name) != 0 )
			{
				if( a[i][j].color == 0 )
					printf("<%8s,%d>", a[i][j].name, a[i][j].augmented );
				else 
					printf("[%8s,%d]", a[i][j].name, a[i][j].augmented );
			}
			else
				printf("%12c", ' ' );
		}
		printf("\n");
	}
	getchar();
}

int main()
{
	int i, sid;
	SAWON s[8] = {{"홍길동",},{"임꺽정",},{"일지매",},{"이순신",},
	              {"강감찬",},{"사임당",},{"유관순",},{"안중근",}};
	struct rb_root root = {0};
	display(&root);
	for( i=0; i<8; i++ )
	{
		rb_insert_name(&root, s[i].name, &s[i].tree);
		display(&root);
	}
	return 0;
}











