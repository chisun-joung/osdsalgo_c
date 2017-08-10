#include <stdio.h>
#include <string.h>

#define OUTPUT(index)   printf("%d\n", index)
#define XSIZE   256

void preMp(char *x, int m, int mpNext[]) {
   int i, j;

   i = 0;
   j = mpNext[0] = -1;
   while (i < m) {
      while (j > -1 && x[i] != x[j])
         j = mpNext[j];
      mpNext[++i] = ++j;
   }
}


void MP(char *x, int m, char *y, int n) {
   int i, j, mpNext[XSIZE];

   /* Preprocessing */
   preMp(x, m, mpNext);

   /* Searching */
   i = j = 0;
   while (j < n) {
      while (i > -1 && x[i] != y[j])
         i = mpNext[i];
      i++;
      j++;
      if (i >= m) {
         OUTPUT(j - i);
         i = mpNext[i];
      }
   }
}


//-------------------------------------------------------
int main()
{
	char y[] = "This algorithm can be algorithm";
	char x[] = "algorithm";
	MP( x, strlen(x), y, strlen(y) );
	return 0;
}




