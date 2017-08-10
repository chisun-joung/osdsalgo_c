#include <stdio.h>

#define BITS_PER_LONG 32
#define BITOP_WORD(nr)		((nr) / BITS_PER_LONG)

unsigned int my_ffs(unsigned int word)
{
	int num = 0;

	if ((word & 0xffff) == 0) {
		num += 16;
		word >>= 16;
	}
	if ((word & 0xff) == 0) {
		num += 8;
		word >>= 8;
	}
	if ((word & 0xf) == 0) {
		num += 4;
		word >>= 4;
	}
	if ((word & 0x3) == 0) {
		num += 2;
		word >>= 2;
	}
	if ((word & 0x1) == 0)
		num += 1;
	return num;
}

unsigned long find_next_bit(const unsigned long *addr, unsigned long size,
			    unsigned long offset)
{
	const unsigned long *p = addr + BITOP_WORD(offset);
	unsigned long result = offset & ~(BITS_PER_LONG-1);
	unsigned long tmp;

	if (offset >= size)
		return size;
	size -= result;
	offset %= BITS_PER_LONG;
	if (offset) {
		tmp = *(p++);
		tmp &= (~0UL << offset);
		if (size < BITS_PER_LONG)
			goto found_first;
		if (tmp)
			goto found_middle;
		size -= BITS_PER_LONG;
		result += BITS_PER_LONG;
	}
	while (size & ~(BITS_PER_LONG-1)) {
		if ((tmp = *(p++)))
			goto found_middle;
		result += BITS_PER_LONG;
		size -= BITS_PER_LONG;
	}
	if (!size)
		return result;
	tmp = *p;

found_first:
	tmp &= (~0UL >> (BITS_PER_LONG - size));
	if (tmp == 0UL)		/* Are any bits set? */
		return result + size;	/* Nope. */
found_middle:
	return result + my_ffs(tmp);
}

int main()
{
	unsigned long bitmap[5] = {0,};
	unsigned long index;
	bitmap[10/32] |= 1UL << ( 10%32 );
	bitmap[50/32] |= 1UL << ( 50%32 );
	bitmap[110/32] |= 1UL << ( 110%32 );
	bitmap[120/32] |= 1UL << ( 120%32 );
	bitmap[145/32] |= 1UL << ( 145%32 );
	index = find_next_bit(bitmap, 140, 100);
	printf("%lu\n", index );
	return 0;
}









