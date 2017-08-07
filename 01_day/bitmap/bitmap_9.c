#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
	unsigned long fds_bits [32];
} fd_set;

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
	fd_set item;
	int i;

	FD_ZERO( &item );
	FD_SET( 700, &item );
	FD_SET( 800, &item );

	for(i=0; i<1024; i++ )
		if( FD_ISSET(i, &item ) )
			printf("%d\n",  i );
	printf("----------\n");
	
	FD_CLR( 800, &item );

	for(i=0; i<1024; i++ )
		if( FD_ISSET(i, &item ) )
			printf("%d\n",  i );
	return 0;
}
