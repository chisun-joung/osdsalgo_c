#if 0
#include <stdio.h>

typedef struct
{
	char ch:1;
} BIT;

int main()
{
	BIT b;
	b.ch = 1;  // +0 ~ -1
	           //  1
	           //  -1
	printf("%d\n", b.ch);
	return 0;
}
#endif
#if 0
#include <stdio.h>

typedef struct
{
	char ch:2;
} BIT;

int main()
{
	BIT b;
	b.ch = 2;  
	           // +1, +0 ~ -1, -2
	           //  10
	           //  -2
    if( b.ch == 2 )
		printf("%d\n", b.ch);
	return 0;
}
#endif
#if 0
#include <stdio.h>

int main()
{
	int i=0xfffffffc;  // 1111 1111 1111 1111 1111 1111 1111 1100
                       // 0000 0000 0000 0000 0000 0000 0000 0100
	                   // -4 
	printf("%d\n", i);
	return 0;
}
#endif

#if 0
#include <stdio.h>

int main()
{
	short s=0xfffe;  // 1111 1111 1111 1110
                     // 0000 0000 0000 0010
	                 // -2 
	printf("%d\n", s);
	return 0;
}
#endif
#if 0
#include <stdio.h>

int main()
{
	char ch=254;
	printf("%d\n", ch);
	return 0;
}
#endif
