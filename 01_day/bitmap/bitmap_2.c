#if 1
#include <stdio.h>

int main()
{
	int item = 0;
	int i;

	item |= 1<<0;
	item |= 1<<3;

	for(i=0; i<32; i++ )
		if( item &(1<<i) )
			printf("%d\n",  i );
	printf("----------\n");
	
	item &= ~(1<<3);
	for(i=0; i<32; i++ )
		if(item &(1<<i) )
			printf("%d\n",  i );
	
	return 0;
}
#endif

#if 0
#include <stdio.h>

int main()
{
	int item = 0;
	int i;

	item = item | 1;
	item = item | 8;

	for(i=0; i<32; i++ )
		if( item &(1<<i) )
			printf("%d\n",  i );
	printf("----------\n");
	
	item = item & ~8;
	for(i=0; i<32; i++ )
		if(item &(1<<i) )
			printf("%d\n",  i );

	return 0;
}
#endif
