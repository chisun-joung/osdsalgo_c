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
void line_1( int (*a)[MAX_X], int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int x, y;
	int stepx = 1, stepy = 1;
	double m = dy / (double)dx;

	if (dx < 0)
		stepx = -1;
	if (dy < 0)
		stepy = -1;

	if (abs(dy) <= abs(dx))
	{
		for (x = x1; x != x2; x+=stepx)
		{
			y = (int)( m*x + 0.5);
			SET_PIXEL(a, x, y);
		}
		y = (int)(m*x + 0.5);
		SET_PIXEL(a, x, y);
	}
	else {
		for (y = y1; y != y2; y+=stepy)
		{
			x = (int)( y/m + 0.5);
			SET_PIXEL(a, x, y);
		}
		x = (int)(y / m + 0.5);
		SET_PIXEL(a, x, y);
	}
}

int main()
{
	int a[MAX_Y][MAX_X] = { 0, };
	
	line_1(a, 3, 8, 0, 0);
	display(a);

	return 0;
}