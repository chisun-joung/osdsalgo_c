#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DYNAMIC_MINORS 64
#define DECLARE_BITMAP(name,bits) \
	unsigned long name[BITS_TO_LONGS(bits)]


#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))

#define BITS_PER_BYTE		8
#define BITS_PER_LONG	   32	
#define BITS_TO_LONGS(nr)	DIV_ROUND_UP(nr, BITS_PER_BYTE * sizeof(long))

#define BIT_MASK(nr)	(1UL << ((nr) % BITS_PER_LONG)) 
#define BIT_WORD(nr)	((nr) / BITS_PER_LONG) 

static inline void set_bit(int nr, volatile unsigned long *addr)
{
	unsigned long mask = BIT_MASK(nr);
	unsigned long *p = ((unsigned long *)addr) + BIT_WORD(nr);
	*p  |= mask;
}
static inline int test_bit(int nr, volatile unsigned long *addr)
{
	unsigned long mask = BIT_MASK(nr);
	unsigned long *p = ((unsigned long *)addr) + BIT_WORD(nr);
	return *p  & mask;
}

//---------------------------------------------------------------

static DECLARE_BITMAP(misc_minors, DYNAMIC_MINORS);

int main()
{
	int i;
	for( i=0 ; i<20; i++ )
		set_bit( 63-i, misc_minors );

	for( i=64 ; i>=0; i-- )
		if( test_bit( i, misc_minors ) )
			printf("%d\n", i );
	return 0;
}
