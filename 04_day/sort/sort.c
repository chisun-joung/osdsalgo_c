#if 1
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int u32;

void u32_swap(void *a, void *b, int size)
{
	u32 t = *(u32 *)a;
	*(u32 *)a = *(u32 *)b;
	*(u32 *)b = t;
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

void sort(void *base, size_t num, size_t size,
	  int (*cmp_func)(const void *, const void *),
	  void (*swap_func)(void *, void *, int size))
{
	/* pre-scale counters for performance */
	int i = (num/2 - 1) * size, n = num * size, c, r;

	if (!swap_func)
		swap_func = (size == 4 ? u32_swap : generic_swap);

	/* heapify */
	for ( ; i >= 0; i -= size) {
		for (r = i; r * 2 + size < n; r  = c) {
			c = r * 2 + size;
			if (c < n - size &&
					cmp_func(base + c, base + c + size) < 0)
				c += size;
			if (cmp_func(base + r, base + c) >= 0)
				break;
			swap_func(base + r, base + c, size);
		}
	}

	/* sort */
	for (i = n - size; i > 0; i -= size) {
		swap_func(base, base + i, size);
		for (r = 0; r * 2 + size < i; r = c) {
			c = r * 2 + size;
			if (c < i - size &&
					cmp_func(base + c, base + c + size) < 0)
				c += size;
			if (cmp_func(base + r, base + c) >= 0)
				break;
			swap_func(base + r, base + c, size);
		}
	}
}

//----------------------------------------------

int asc_int(const void* a, const void* b )
{
	return  *(int*)a - *(int*)b;
}
int desc_int(const void* a, const void* b )
{
	return  *(int*)b - *(int*)a;
}

int main()
{
	int i;
	int a[] = { 400,600,300,500,200,700,100 };
	sort( a, 7, sizeof a[0], desc_int, 0 );
	for(i=0; i<7; i++ )
		printf("%6d", a[i] );
	printf("\n");
	return 0;
}
#endif


#if 0
#include <stdio.h>
#include <stdlib.h>
void generic_swap(void *a, void *b, int size)
{
	char t;

	do {
		t = *(char *)a;
		*(char *)a++ = *(char *)b;
		*(char *)b++ = t;
	} while (--size > 0);
}

// O(n*log2N)
void bubble( void *a, int n, int size, 
             int (*cmp)(const void*, const void*)  )
{
  int i,j;
  for(i=0; i<n-1; i++ )
    for(j=0; j<n-1-i; j++ )
      if( cmp((char*)a+j*size, (char*)a+(j+1)*size ) > 0 )
        generic_swap( (char*)a+j*size, (char*)a+(j+1)*size, size );
}


//----------------------------------------------

int asc_int(const void* a, const void* b )
{
	return  *(int*)a - *(int*)b;
}
int desc_int(const void* a, const void* b )
{
	return  *(int*)b - *(int*)a;
}

int main()
{
	int i;
	int a[] = { 400,600,300,500,200,700,100 };
	qsort( a, 7, sizeof a[0], desc_int );
	for(i=0; i<7; i++ )
		printf("%6d", a[i] );
	printf("\n");
	return 0;
}
#endif

#if 0
#include <stdio.h>
void generic_swap(void *a, void *b, int size)
{
	char t;

	do {
		t = *(char *)a;
		*(char *)a++ = *(char *)b;
		*(char *)b++ = t;
	} while (--size > 0);
}

void bubble( void *a, int n, int size  )
{
	int i,j;
	for(i=0; i<n-1; i++ )
		for(j=0; j<n-1-i; j++ )
			if( *(int*)((char*)a+j*size) > *(int*)((char*)a+(j+1)*size) )
				generic_swap( (char*)a+j*size, (char*)a+(j+1)*size, size );
}

//----------------------------------------------

int main()
{
	int i;
	int a[] = { 400,600,300,500,200,700,100 };
	bubble( a, 7, sizeof a[0] );
	for(i=0; i<7; i++ )
		printf("%6d", a[i] );
	printf("\n");
	return 0;
}
#endif
#if 0
#include <stdio.h>
void generic_swap(void *a, void *b, int size)
{
	char t;

	do {
		t = *(char *)a;
		*(char *)a++ = *(char *)b;
		*(char *)b++ = t;
	} while (--size > 0);
}

void bubble( int *a, int n )
{
	int i,j;
	for(i=0; i<n-1; i++ )
		for(j=0; j<n-1-i; j++ )
			if( a[j] > a[j+1] )
				generic_swap( a+j, a+j+1, sizeof a[0] );
}
//----------------------------------------------

int main()
{
	int i;
	int a[] = { 4,6,3,5,2,7,1 };
	bubble( a, 7 );
	for(i=0; i<7; i++ )
		printf("%6d", a[i] );
	printf("\n");
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
