#if 1
#include <stdio.h>
typedef int FP1[2];
typedef FP1* FP2;

//------------------------
FP2 foo(void) 
{
    static int a[2][2];
    return a;
}

int main()
{    
    foo()[1][1] = 10;
    return 0;
}

#endif

#if 0
#include <stdio.h>
typedef int [2] FP1;
typedef FP1* FP2;

//------------------------
FP2 foo(void) 
{
    static int a[2][2];
    return a;
}

int main()
{    
    foo()[1][1] = 10;
    return 0;
}

#endif

#if 0
#include <stdio.h>

int (*foo(void))[2] 
{
    static int a[2][2];
    return a;
}

int main()
{
    foo()[1][1] = 10;

    return 0;
}

#endif
#if 0
#include <stdio.h>

int (*)[2] foo( void )
{
    static int a[2][2];
    return a;
}

int main()
{
    int (*p)[2];
    
    p = foo();
    p[1][1] = 10;

    return 0;
}

#endif

#if 0
#include <stdio.h>

int main()
{
	int a[2][2] = {1,2,3,4};
	int (*p)[2]  = a;
	p[1][1] = 10;
	return 0; 
}
#endif
#if 0
#include <stdio.h>

int main()
{
	int a[2][2] = {1,2,3,4};
	int **p  = a;
	p[1][1] = 10;
	return 0; 
}
#endif

#if 0
#include <stdio.h>

int main()
{
	int a[2][2] = {1,2,3,4};
	int *p  = a;
	p[1][1] = 10;
	return 0; 
}
#endif

#if 0
#include <stdio.h>

int main()
{
	int a[2] = {1,2};
	int (*p)[2]  = &a;
	(*p)[1] = 10;
	return 0; 
}
#endif
#if 0
#include <stdio.h>

int main()
{
	int a[2] = {1,2};
	int *p = a;
	p[1] = 10;
	printf("%lu\n", sizeof(p));
	printf("%lu\n", sizeof(int*));
	printf("%lu\n", sizeof(a));
	printf("%lu\n", sizeof(int[2]));
	return 0; 
}
#endif

#if 0
#include <stdio.h>

int main()
{
	int a[2] = {1,2};
	int *p = a;
	p[1] = 10;
	return 0; 
}
#endif
#if 0
#include <stdio.h>

int main()
{
	char ch=100;
	int *i = &ch;
	return 0; 
}
#endif

#if 0
#include <stdio.h>

int main()
{
	char ch=100;
	int i = ch;
	return 0; 
}
#endif
