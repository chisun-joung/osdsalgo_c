#include <stdio.h>
#include "flex_array.h"

int main()
{
	struct flex_array *fa=0;
	fa = flex_array_alloc( sizeof(int), 1000, 0 );
	printf("fa=%p\n", fa );

	return 0;
}
