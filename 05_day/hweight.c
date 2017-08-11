#include <stdio.h>

#define BITS_PER_LONG 32
#define BITOP_WORD(nr)		((nr) / BITS_PER_LONG)

unsigned int my_count( unsigned int bitmap )
{
	int i;
   int count=0;
	for(i=0; i<32; i++ )
		if( bitmap & (1<<i) )
			count++;
	return count;
}

typedef unsigned int uint32_t;
const uint32_t m1  = 0x55555555; 
const uint32_t m2  = 0x33333333; 
const uint32_t m4  = 0x0f0f0f0f; 
const uint32_t m8  = 0x00ff00ff; 
const uint32_t m16 = 0x0000ffff; 
const uint32_t h01 = 0x01010101; 

int popcount32a(uint32_t x)
{
    x = (x & m1 ) + ((x >>  1) & m1 );  
    x = (x & m2 ) + ((x >>  2) & m2 );  
    x = (x & m4 ) + ((x >>  4) & m4 );  
    x = (x & m8 ) + ((x >>  8) & m8 );  
    x = (x & m16) + ((x >> 16) & m16);  
    return x;
}

int popcount32b(uint32_t x)
{
    x -= (x >> 1) & m1;             
    x = (x & m2) + ((x >> 2) & m2);  
    x = (x + (x >> 4)) & m4;         
    x += x >>  8;  
    x += x >> 16;  
    return x & 0x7f;
}

int popcount32c(uint32_t x)
{
    x -= (x >> 1) & m1;             
    x = (x & m2) + ((x >> 2) & m2); 
    x = (x + (x >> 4)) & m4;        
    return (x * h01) >> 24;         
}

unsigned int __sw_hweight32(unsigned int w)
{
	w -= (w >> 1) & 0x55555555;
	w =  (w & 0x33333333) + ((w >> 2) & 0x33333333);
	w =  (w + (w >> 4)) & 0x0f0f0f0f;
	return (w * 0x01010101) >> 24;
}

int popcount32d(uint32_t x)
{
    int count;
    for (count=0; x; count++)
        x &= x - 1;
    return count;
}

int main()
{
	unsigned int bitmap = 0x12345678; // 0001 0010 0011 0100 0101 0110 0111 1000
	unsigned int count;
	count = popcount32d(bitmap);
	printf("%u\n", count );
	return 0;
}










