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
				printf("□");
			else
				printf("■");
		}
		printf("\n");
	}
	getchar();
}
void line_2(int(*a)[MAX_X], int x1, int y1, int x2, int y2) // DDA 알고리즘 
{
	int dx, dy, steps, k;
	double  x, y, x_incre, y_incre;

	dx = x2 - x1;
	dy = y2 - y1;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);

	x_incre = (double)dx / steps;
	y_incre = (double)dy / steps;
	x = (double)x1;
	y = (double)y1;


	SET_PIXEL(a, (int)x, (int)y);

	for (k = 0; k < steps; k++)
	{
		x = x + x_incre;
		y = y + y_incre;
		SET_PIXEL(a, (int)x, (int)y);
	}
}


int main()
{
	int a[MAX_Y][MAX_X] = { 0, };

	line_2(a, 0, 0, 8, 3);
	display(a);

	return 0;
}