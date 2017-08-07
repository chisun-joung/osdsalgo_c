#include <stdio.h>

#define FD_SET(fd, fdsetp) \
		(((fd_set *)(fdsetp))->fds_bits[(fd) >> 5] |= (1<<((fd) & 31)))

#define FD_CLR(fd, fdsetp) \
		(((fd_set *)(fdsetp))->fds_bits[(fd) >> 5] &= ~(1<<((fd) & 31)))

#define FD_ISSET(fd, fdsetp) \
		((((fd_set *)(fdsetp))->fds_bits[(fd) >> 5] & (1<<((fd) & 31))) != 0)

#define FD_ZERO(fdsetp) \
		(memset (fdsetp, 0, sizeof (*(fd_set *)(fdsetp))))
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
