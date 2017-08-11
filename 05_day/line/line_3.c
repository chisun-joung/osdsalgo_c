#include <stdio.h>
#include <stdlib.h>
#define SET_PIXEL( a, x, y )   (a[y][x] = 1)
#define MAX_X  40
#define MAX_Y  20

void display(int(*a)[MAX_X])
{
	int i, j;
	system("cls");
	for (i = 0; i < MAX_Y; i++)
	{
		for (j = 0; j < MAX_X; j++)
		{
			if (a[i][j] == 0)
				printf("бр");
			else
				printf("бс");
		}
		printf("\n");
	}
	getchar();
}
void line_3(int(*a)[MAX_X], int x1, int y1, int x2, int y2) 
{
	int dx = x2 - x1;
	int dy = y2 - y1;

	double m = (double)dy / dx;
	double fraction = m + 0.5;

	// 0.8 , 1.1 , 0.4, 0.7 , 1.0 , 0.3 
	//  0 ,  1,  ,  1 ,  1,   2  ,  2
	while (x1 != x2)
	{
		SET_PIXEL(a, x1, y1);

		if (fraction >= 1)
		{
			y1 += 1;
			fraction = fraction - 1;
		}
		fraction += m;
		x1 += 1;
	}
}


int main()
{
	int a[MAX_Y][MAX_X] = { 0, };

	line_3(a, 0, 0, 3, 8);
	display(a);

	return 0;
}