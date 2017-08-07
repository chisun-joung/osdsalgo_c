#include <stdio.h>

int main()
{
	int item[32] = {0,};
	int i;

	item[700/32] |= 1<<(700%32);
	item[800/32] |= 1<<(800%32);

	for(i=0; i<1024; i++ )
		if( item[i/32] &(1<<(i%32)) )
			printf("%d\n",  i );
	printf("----------\n");
	
	item[800/32] &= ~(1<<(800%32));

	for(i=0; i<1024; i++ )
		if( item[i/32] &(1<<(i%32)) )
			printf("%d\n",  i );
	return 0;
}
