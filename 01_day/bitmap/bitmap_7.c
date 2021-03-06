#include <stdio.h>

#define BIT_SET( index, x ) ((x)->data[index/32] |= 1<<(index%32))
#define BIT_ISSET( index, x ) ( (x)->data[index/32] &(1<<(index%32)) )
#define BIT_CLR( index, x ) ((x)->data[index/32] &= ~(1<<(index%32)))
#define BIT_ZERO( x )       do{ int i;                  \
                                for(i=0; i<32; i++ )    \
							      (x)->data[i] = 0; }while(0)
typedef struct 
{
	int data[32];
} bit_set;
//---------------------------------------------------------------
int main()
{
	bit_set item;
	int i;

	BIT_ZERO( &item );
	BIT_SET( 700, &item );
	BIT_SET( 800, &item );

	for(i=0; i<1024; i++ )
		if( BIT_ISSET(i, &item ) )
			printf("%d\n",  i );
	printf("----------\n");
	
	BIT_CLR( 800, &item );

	for(i=0; i<1024; i++ )
		if( BIT_ISSET(i, &item ) )
			printf("%d\n",  i );
	return 0;
}
