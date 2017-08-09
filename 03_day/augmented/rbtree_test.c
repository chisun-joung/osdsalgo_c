#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbtree_augmented.h"

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

int my_compute( SAWON *s )
{
	int augmented=1;
	if( s->tree.rb_left )
		augmented += rb_entry(s->tree.rb_left,SAWON,tree)->augmented;
	if( s->tree.rb_right )
		augmented += rb_entry(s->tree.rb_right,SAWON,tree)->augmented;
	return augmented;
}

RB_DECLARE_CALLBACKS( , rb, SAWON, tree, int, augmented, my_compute )

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
	rb_insert_augmented(node, root, &rb);

	return NULL;
}

SAWON *my_select( struct rb_node *node, int i )
{
   int k = 1;
   if( node == 0 )
      return 0;
   if( node->rb_left ) 
      k = rb_entry( node->rb_left, SAWON, tree)->augmented+1;
   if( i<k )
     my_select( node->rb_left, i );
   else if( i>k)
     my_select( node->rb_right, i-k );
   else 
     return rb_entry( node, SAWON, tree);
}

int my_rank(struct rb_node *node)
{
	int k = 1;

	if (node->rb_left)
		k = rb_entry(node->rb_left, SAWON, tree)->augmented + 1;

	while (rb_parent(node) != 0)
	{
		if (rb_parent(node)->rb_right == node)
		{
			if (rb_parent(node)->rb_left)
				k += rb_entry(rb_parent(node)->rb_left, SAWON, tree)->augmented + 1;
			else
				k += 1;
		}
		node = rb_parent(node);
	}
	return k;
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
	int index;
	SAWON *temp;

	SAWON s[8] = {{"홍길동",},{"임꺽정",},{"일지매",},{"이순신",},
	              {"강감찬",},{"사임당",},{"유관순",},{"안중근",}};
	struct rb_root root = {0};
	for( i=0; i<8; i++ )
	{
		rb_insert_name(&root, s[i].name, &s[i].tree);
	}
	display(&root);
	while(1)
	{
		printf("몇번째?");
		scanf("%d", &index );
		temp = my_select(root.rb_node, index);
		if( temp )
			printf("%d번째 사원의 이름은 %s입니다.\n", index, temp->name );
		else
			printf("%d번째 사원은 범위에 있지 않습니다.\n", index );

		index = -999;

		index = my_rank( &temp->tree );
		printf("%s 사원은 %d번째 입니다.\n", temp->name, index );
	}
	return 0;
}











