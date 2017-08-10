#include <stdio.h>
#include <stdlib.h>
// 1234 => 10
// 4321 => 10
int my_atoi(char *str)
{
	int sum=0;
	int i;
	for(i=0; str[i]; i++ )
		sum = sum*10 + str[i]-'0';  // 1*1000+2*200+3*10+4*1
	return sum;
}

int main()
{
	char str[] = "1234";
	int num;
	num = my_atoi(str);
	printf("num=%d\n", num );
	return 0;
}
