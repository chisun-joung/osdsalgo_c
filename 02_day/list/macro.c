#if 1
#include <stdio.h>

#define ADD(a,b)     \
({                    \
	int result;                       \
	result = a+b;                     \
	result;                           \
})

int main()
{
	int ret = 0;
	ret = ADD(3,4);
	printf("%d\n", ret);
	return 0;
}
#endif

#if 0
#include <stdio.h>

int add(int a, int b)
{
	int result;
	result = a+b;
	return result;
}

int main()
{
	printf("%d\n", add(3,4));
	return 0;
}
#endif

#if 0
#include <stdio.h>

#define __FOO(data)                \
	*data = 20;                    \
	printf("%d\n", *data );        

#define FOO(data)                       \
	const typeof(*data) *_data = data;  \
	__FOO(_data)

int main()
{
	int data=10;
	FOO(&data);
	return 0;
}

#endif
#if 0
#include <stdio.h>

void foo(const int *data );

int main()
{
	int data=10;
	foo(&data);
	return 0;
}

void foo(const int *data )
{
	*data = 20;
	printf("%d\n", *data );
}
#endif
