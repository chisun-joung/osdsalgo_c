#if 1
#include <stdio.h>
void swap( void *a, void *b , int size)
{
	char t;
	int i;
	char *p = (char*)a;
	char *q = (char*)b;
	for(i=0; i<size; i++ )
	{
		t = p[i];
		p[i] = q[i];
		q[i] = t;
	}
}
void generic_swap(void *a, void *b, int size)
{
	char t;

	do {
		t = *(char *)a;
		*(char *)a++ = *(char *)b;
		*(char *)b++ = t;
	} while (--size > 0);
}

//----------------------------------------------

int main()
{
	int a=3, b=4;
	double ad=3., bd=4.;
	generic_swap(&a, &b, sizeof a);
	printf("a=%d, b=%d\n", a, b );
	generic_swap(&ad, &bd, sizeof ad);
	printf("ad=%lf, bd=%lf\n", ad, bd );
	return 0;
}
#endif

#if 0
#include <stdio.h>
void swap( char *a, char *b , int size)
{
	char t;
	int i;
	for(i=0; i<size; i++ )
	{
		t = a[i];
		a[i] = b[i];
		b[i] = t;
	}
}
//----------------------------------------------

int main()
{
	int a=3, b=4;
	double ad=3., bd=4.;
	swap((char*)&a, (char*)&b, sizeof a);
	printf("a=%d, b=%d\n", a, b );
	swap((char*)&ad, (char*)&bd, sizeof ad);
	printf("ad=%lf, bd=%lf\n", ad, bd );
	return 0;
}
#endif

#if 0
#include <stdio.h>
void swap_ii( int *a, int *b )       // swap_ii
{
	int t;
	t = *a;
	*a = *b;
	*b = t;
}
void swap_dd( double *a, double *b )  // swap_dd
{
	double t;
	t = *a;
	*a = *b;
	*b = t;
}

int main()
{
	int a=3, b=4;
	double ad=3., bd=4.;
	swap_ii(&a, &b);
	printf("a=%d, b=%d\n", a, b );
	swap_dd(&ad, &bd);
	printf("ad=%lf, bd=%lf\n", ad, bd );
	return 0;
}
#endif

#if 0
#include <stdio.h>
#define TYPE  float
void swap( TYPE *a, TYPE *b )
{
	TYPE t;
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
