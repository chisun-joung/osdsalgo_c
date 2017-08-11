#include <stdio.h>
unsigned long gcd(unsigned long a, unsigned long b)
{
	unsigned long r;

	if (!b)
		return a;
	while ((r = a % b) != 0) {
		a = b;
		b = r;
	}
	return b;
}

int main()
{
	unsigned long a=150, b=270;
	printf("%lu\n", gcd( a, b ));
	return 0;
}
