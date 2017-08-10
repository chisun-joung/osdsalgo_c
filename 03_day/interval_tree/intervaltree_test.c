#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interval_tree.h"
#include "interval_tree_generic.h"

typedef struct
{
	unsigned long start;	
	unsigned long last;	
	unsigned long __subtree_last;
	int color;
} INFO;


#define START(node) ((node)->start)
#define LAST(node)  ((node)->last)

INTERVAL_TREE_DEFINE(struct interval_tree_node, rb,
		     unsigned long, __subtree_last,
		     START, LAST,, interval_tree)

void __display(struct rb_node *temp, INFO (*a)[10], int *row, int *col )
{
   int i;
   if( temp == 0 )
      return;
   ++*row;
   __display(temp->rb_left, a, row, col);
   a[*row][*col].color = temp->__rb_parent_color & 1 ;
   a[*row][*col].start = rb_entry(temp,struct interval_tree_node,rb)->start ;
   a[*row][*col].last  = rb_entry(temp,struct interval_tree_node,rb)->last ;
   a[*row][(*col)++].__subtree_last = 
	   rb_entry(temp,struct interval_tree_node,rb)->__subtree_last ;
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
			if( a[i][j].start != 0 )
			{
				if( a[i][j].color == 0 )
					printf("<%2d,%2d,%2d>", a[i][j].start, 
							a[i][j].last, a[i][j].__subtree_last );
				else 
					printf("[%2d,%2d,%2d]", a[i][j].start, 
							a[i][j].last, a[i][j].__subtree_last );
			}
			else
				printf("%10c", ' ' );
		}
		printf("\n");
	}
	getchar();
}

typedef struct 
{
	unsigned long start;
	unsigned long last;
} Range;

int main()
{
	int i;
	Range r[] = {{17,19},{5,11},{22,23},{4,8},{15,18},{7,10}};
	struct interval_tree_node nodes[6];
	struct rb_root root = {0};
	struct interval_tree_node *temp;				      
	display(&root);
	for( i=0; i<6; i++ )
	{
		nodes[i].start = r[i].start;
		nodes[i].last  = r[i].last;
		interval_tree_insert(&nodes[i], &root);
		display(&root);
	}
	temp = interval_tree_subtree_search( 
			rb_entry(root.rb_node, struct interval_tree_node, rb),
			13, 14 );	
	if( temp )
		printf("%lu~%lu 구간과 겹치는 최초의 구간은 %lu~%lu구간 입니다.\n",
				13, 14, temp->start, temp->last );
	else
		printf("%lu~%lu 구간과 겹치는 구간은 없습니다. \n",
				13, 14 );

	return 0;
}











