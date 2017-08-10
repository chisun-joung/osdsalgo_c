#include <stdio.h>
#include "flex_array.h"

int main()
{
	struct flex_array *fa=0;
	int data = 10;
	int *p;
	fa = flex_array_alloc( sizeof(int), 2000, 0 );
	printf("fa=%p\n", fa );  // int fa[2000]
	flex_array_put( fa, 1500, &data, 0 ); // fa[1500] = 10;
	p = flex_array_get( fa, 1500 );       // p = &fa[1500];
	printf("%d\n", *p );

	return 0;
}
