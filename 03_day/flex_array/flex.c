#if 1
#include <stdio.h>
struct  node 
{
	int a;
	int b[];  // flexible array
};

int main()
{
	struct  node  node;
	printf("%lu\n", sizeof(node));
	return 0;
}
#endif
#if 0
int main()
{
	int a[] = {1,2,3,4};
	return 0;
}
#endif
