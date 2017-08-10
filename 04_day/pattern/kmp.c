#include <stdio.h>
#include <string.h>

#define OUTPUT(index)   printf("%d\n", index)
#define XSIZE   256

void preKmp(char *x, int m, int kmpNext[]) {
   int i, j;

   i = 0;
   j = kmpNext[0] = -1;
   while (i < m) {
      while (j > -1 && x[i] != x[j])
         j = kmpNext[j];
      i++;
      j++;
      if (x[i] == x[j])
         kmpNext[i] = kmpNext[j];
      else
         kmpNext[i] = j;
   }
}


void KMP(char *x, int m, char *y, int n) {
   int i, j, kmpNext[XSIZE];

   /* Preprocessing */
   preKmp(x, m, kmpNext);
   for(i=0; i<m+1; i++ )
	   printf("%4d", kmpNext[i] );
   printf("\n");

   /* Searching */
   i = j = 0;
   while (j < n) {
      while (i > -1 && x[i] != y[j])
         i = kmpNext[i];
      i++;
      j++;
      if (i >= m) {
         OUTPUT(j - i);
         i = kmpNext[i];
      }
   }
}


//-------------------------------------------------------
int main()
{
	char y[] = "This algorithm can be algorithm";
	char x[] = "gagggagg";
	KMP( x, strlen(x), y, strlen(y) );
	return 0;
}




