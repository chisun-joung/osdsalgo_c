#include <stdio.h>
#include <stdlib.h>
typedef struct _node
{
    int data;
    struct _node *left;
    struct _node *right;
} NODE;

NODE *root;

typedef enum {LEFT, RIGHT} FLAG;

void insert_data( int data , NODE *s, FLAG flag )
{
    NODE *temp;
    temp = malloc( sizeof(NODE) );
    temp->left = 0;
    temp->right = 0;
    temp->data = data;

    if( root == 0 )
    {
        root = temp;
        return;
    }
    if( flag == LEFT )
        s->left = temp;
    else
        s->right = temp;
}
//--------------------------------------------------


void pre_order(NODE *temp)
{
   if( temp == 0 )
      return;
   printf("%d\n", temp->data);
   pre_order(temp->left);
   pre_order(temp->right);
} 

void in_order(NODE *temp)
{
   if( temp == 0 )
      return;
   
   in_order(temp->left);
   printf("%d\n", temp->data);
   in_order(temp->right);
} 

void post_order(NODE *temp)
{
   if( temp == 0 )
      return;
   
   post_order(temp->left);
   post_order(temp->right);
   printf("%d\n", temp->data);
} 

/*
void display(NODE *temp)
{
   static int indent=-1;
   int i;
   if( temp == 0 )
      return;
   ++indent;
   display(temp->right);
   for(i=0; i<indent; i++ )
       printf("%4c", ' ');
   printf("%d\n", temp->data);
   display(temp->left);
   --indent;
} 
*/

void __display(NODE *temp, int (*a)[10], int *row, int *col )
{
   int i;
   if( temp == 0 )
      return;
   ++*row;
   __display(temp->left, a, row, col);
   a[*row][(*col)++] = temp->data;
   __display(temp->right, a, row, col);
   --*row;
} 

void display( NODE *temp )
{
	int i,j;
	int a[10][10]={0,};
	int row=-1, col=0;
	system("cls");
	__display( temp, a, &row, &col );
	for(i=0; i<10; i++ )
	{
		for(j=0; j<10; j++ )
		{
			if( a[i][j] )
				printf("%4d", a[i][j] );
			else
				printf("%4c", ' ' );
		}
		printf("\n");
	}
	getchar();
}

int main()
{
	display(root);
	insert_data(1, root, LEFT );
	display(root);
	insert_data(2, root, LEFT );
	display(root);
	insert_data(3, root, RIGHT );
	display(root);
	insert_data(4, root->left, LEFT );
	display(root);
	insert_data(5, root->left, RIGHT );
	display(root);
	insert_data(6, root->right, LEFT );
	display(root);
	insert_data(7, root->right, RIGHT );
	display(root);
	return 0;
}













