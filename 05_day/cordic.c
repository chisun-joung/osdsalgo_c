#include <stdio.h>
#include <stdlib.h>
typedef int s32;
struct cordic_iq {
	s32 i;
	s32 q;
};

#define CORDIC_ANGLE_GEN	39797
#define CORDIC_PRECISION_SHIFT	16
#define	CORDIC_NUM_ITER		(CORDIC_PRECISION_SHIFT + 2)

#define	FIXED(X)	((s32)((X) << CORDIC_PRECISION_SHIFT))
#define	FLOAT(X)	(((X) >= 0) \
		? ((((X) >> (CORDIC_PRECISION_SHIFT - 1)) + 1) >> 1) \
		: -((((-(X)) >> (CORDIC_PRECISION_SHIFT - 1)) + 1) >> 1))

static const s32 arctan_table[] = {
	2949120,
	1740967,
	919879,
	466945,
	234379,
	117304,
	58666,
	29335,
	14668,
	7334,
	3667,
	1833,
	917,
	458,
	229,
	115,
	57,
	29
};

/*
 * cordic_calc_iq() - calculates the i/q coordinate for given angle
 *
 * theta: angle in degrees for which i/q coordinate is to be calculated
 * coord: function output parameter holding the i/q coordinate
 */
struct cordic_iq cordic_calc_iq(s32 theta)
{
	struct cordic_iq coord;
	s32 angle, valtmp;
	unsigned iter;
	int signx = 1;
	int signtheta;

	coord.i = CORDIC_ANGLE_GEN;
	coord.q = 0;
	angle = 0;

	theta = FIXED(theta);
	signtheta = (theta < 0) ? -1 : 1;
	theta = ((theta + FIXED(180) * signtheta) % FIXED(360)) -
		FIXED(180) * signtheta;

	if (FLOAT(theta) > 90) {
		theta -= FIXED(180);
		signx = -1;
	} else if (FLOAT(theta) < -90) {
		theta += FIXED(180);
		signx = -1;
	}

	for (iter = 0; iter < CORDIC_NUM_ITER; iter++) {
		if (theta > angle) {
			valtmp = coord.i - (coord.q >> iter);
			coord.q += (coord.i >> iter);
			angle += arctan_table[iter];
		} else {
			valtmp = coord.i + (coord.q >> iter);
			coord.q -= (coord.i >> iter);
			angle -= arctan_table[iter];
		}
		coord.i = valtmp;
	}

	coord.i *= signx;
	coord.q *= signx;
	return coord;
}

void display( int y, int x )
{
	int i;
	system("cls");
	for( i=0; i<y; i++ )
		printf("\n");

	for( i=0; i<x; i++ )
		printf(" ");
	printf("#\n");
	getchar();
}

int main()
{
	int i;
	struct cordic_iq coord;
	for(i=0; ; i+=4 )
	{
		coord = cordic_calc_iq(i);
		//printf("coord.i=%d, coord.q=%d\n", coord.i, coord.q);
		display( ((-coord.i + 65541)*30)/131082 , ((coord.q + 65541)*60)/131082 );
	}
	return 0;
}
