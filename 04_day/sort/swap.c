#if 1
#include <stdio.h>
void swap( int *a, int *b )
{
	int t;
	t = *a;
	*a = *b;
	*b = t;
}
int main()
{
	int a=3, b=4;
	swap(&a, &b);
	printf("a=%d, b=%d\n", a, b );
	return 0;
}
#endif

#if 0
#include <stdio.h>
#define SWAP(a,b)   ((a!=b)?((a) ^= (b) ^= (a) ^= (b)):1)
int main()
{
	float a=3.f, b=4.f;
	SWAP(a,b);
	printf("a=%f, b=%f\n", a, b );
	return 0;
}
#endif

#if 0
#include <stdio.h>
#define SWAP(a,b)   ((a!=b)?((a) ^= (b) ^= (a) ^= (b)):1)
int main()
{
	int a=3, b=3;
	SWAP(a,b);
	printf("a=%d, b=%d\n", a, b );
	return 0;
}
#endif


#if 0
#include <stdio.h>
#define SWAP(a,b)   ((a) ^= (b) ^= (a) ^= (b))
int main()
{
	int a=3, b=4;
	SWAP(a,b);
	printf("a=%d, b=%d\n", a, b );
	return 0;
}
#endif

#if 0
#include <stdio.h>
int main()
{
	int a=3, b=4;
	a ^= b ^= a ^= b; 
	printf("a=%d, b=%d\n", a, b );
	return 0;
}
#endif

#if 0
#include <stdio.h>
int main()
{
	int a=3, b=4;
	a ^= b; 
	b ^= a;
	a ^= b;
	printf("a=%d, b=%d\n", a, b );
	return 0;
}
#endif

#if 0
#include <stdio.h>
int main()
{
	// DES 
	// P ^ K = C
	// C ^ K = P
	int a=3, b=4;
	a = a ^ b; // 0011
	           // 0100 ^
			   // 0111
			   
	b = a ^ b; // 0111
	           // 0100 ^
			   // 0011
			   
	a = a ^ b; // 0111
	           // 0011 ^
			   // 0100
	printf("a=%d, b=%d\n", a, b );
	return 0;
}
#endif

#if 0
#include <stdio.h>
int main()
{
	int a=3, b=4;
	a = a * b;
	b = a / b;
	a = a / b;
	printf("a=%d, b=%d\n", a, b );
	return 0;
}
#endif

#if 0
#include <stdio.h>
int main()
{
	// 11001000  
	// 00111000  -56
	int a=3, b=4;
	a = a + b;
	b = a - b;
	a = a - b;
	printf("a=%d, b=%d\n", a, b );
	return 0;
}
#endif

#if 0
#include <stdio.h>
int main()
{
	int a=3, b=4;
	int t;
	t = a;
	a = b;
	b = t;
	printf("a=%d, b=%d\n", a, b );
	return 0;
}
#endif
