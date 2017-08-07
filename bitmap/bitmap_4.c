#include <stdio.h>

#define BIT_SET( index, x ) (x[index/32] |= 1<<(index%32))
#define BIT_ISSET( index, x ) ( x[index/32] &(1<<(index%32)) )
#define BIT_CLR( index, x ) (x[index/32] &= ~(1<<(index%32)))
//---------------------------------------------------------------
int main()
{
	int item[32] = {0,};
	int i;

	BIT_SET( 700, item );
	BIT_SET( 800, item );

	for(i=0; i<1024; i++ )
		if( BIT_ISSET(i, item ) )
			printf("%d\n",  i );
	printf("----------\n");
	
	BIT_CLR( 800, item );

	for(i=0; i<1024; i++ )
		if( BIT_ISSET(i, item ) )
			printf("%d\n",  i );
	return 0;
}
