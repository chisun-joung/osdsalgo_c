#include <stdio.h>
#include <stdlib.h>
typedef struct _node
{
    int data;
    struct _node *left;
    struct _node *right;
} NODE;

NODE *root;

void insert_data( int data )
{
    NODE *temp;
    NODE **p = &root;
    temp = malloc( sizeof(NODE) );
    temp->left = 0;
    temp->right = 0;
    temp->data = data;

    while(*p)
    {
       if( (*p)->data > data )
          p = &(*p)->left ;
       else if( (*p)->data < data )
          p = &(*p)->right;
       else
          return;
    }
    *p = temp;
}

void __fill( NODE *temp, int *a, int *n)
{
    if( temp == 0 )
       return;
    __fill( temp->left, a, n );
    a[(*n)++] = temp->data;
    __fill( temp->right, a, n );
}

NODE* __bal(int *a, int n)
{
    int mid = n/2;
    NODE *temp;
    if( n<1 )
       return 0;
    temp=malloc(sizeof(NODE));
    temp->data = a[mid];
    temp->left = __bal(a,mid);
    temp->right = __bal(a+mid+1,n-mid-1);
    return temp;
}

void bal( NODE *temp )
{
	int a[100]={0,};
	int n=0;
	__fill( temp, a, &n );
	root = __bal( a, n );
}

//--------------------------------------------------

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
	int a[] = { 1,2,3,4,5,6,7 };
	int i;
	display(root);
	for( i=0; i<7; i++ )
	{
		insert_data(a[i]);
		display(root);
	}
	bal(root);
	display(root);
	return 0;
}













