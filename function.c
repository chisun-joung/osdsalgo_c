#if 1
#include <stdio.h>

typedef int (*FP1)[2];
typedef FP1 (*FP2)(void);
typedef FP2 (*FP3)(void);
typedef FP3 (*FP4)[2];
//-------------------------------------------------
FP1 aaa(void)
{
	static int a[2][2];
	printf("aaa(void)\n");
	return a;
}

FP2 bbb(void)
{
     printf("bbb(void)\n");
     return aaa;
}

int main()
{
	FP3 p[2][2]= {{bbb,bbb},{bbb,bbb}};
	FP4 q = p;
	q[1][1]()()[1][1] = 10;
	return 0;
}



#endif
#if 0
#include <stdio.h>

typedef int FP1[2];
typedef FP1* FP2;
typedef FP2 FP3(void);
typedef FP3* FP4;
typedef FP4 FP5(void);
typedef FP5* FP6;
typedef FP6 FP7[2];
typedef FP7* FP8;
//-------------------------------------------------
FP2 aaa(void)
{
	static int a[2][2];
	printf("aaa(void)\n");
	return a;
}

FP4 bbb(void)
{
     printf("bbb(void)\n");
     return aaa;
}

int main()
{
	FP6 p[2][2]= {{bbb,bbb},{bbb,bbb}};
	FP8 q = p;
	q[1][1]()()[1][1] = 10;
	return 0;
}



#endif
#if 0
#include <stdio.h>

int (*aaa(void))[2]
{
	static int a[2][2];
	printf("aaa(void)\n");
	return a;
}

int (*(*bbb(void))(void))[2]
{
     printf("bbb(void)\n");
     return aaa;
}

//---------------------------------

int main()
{
	int (*(*(*p[2][2])(void))(void))[2] = {{bbb,bbb},{bbb,bbb}};
	int (*(*(*(*q)[2])(void))(void))[2] = p;
	q[1][1]()()[1][1] = 10;
	return 0;
}


#endif


#if 0
#include <stdio.h>

void aaa(void) 
{
	printf("aaa(void)\n");
}

void (*bbb(void))(void) 
{
     printf("bbb(void)\n");
     return aaa;
}

//---------------------------------


int main()
{
	bbb()();
	return 0;
}


#endif

#if 0
#include <stdio.h>

void aaa(void (*p)(void)) 
{
	p(); // bbb();
	printf("aaa(void)\n");
}

//---------------------------------

void bbb(void)
{
     printf("bbb(void)\n");
}

int main()
{
	aaa(bbb);
	return 0;
}

#endif

#if 0
#include <stdio.h>

void foo(void) 
{
	printf("foo(void)\n");
}

int main()
{
	void (*p)(void)  = foo;
	p();
	return 0;
}
#endif

#if 0
#include <stdio.h>

void foo()
{
	printf("foo()\n");
}

int main()
{
	foo;
	return 0;
}
#endif
