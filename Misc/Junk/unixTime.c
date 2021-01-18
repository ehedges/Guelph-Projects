#include "stdio.h"
#include "stdlib.h"
#include <sys/time.h>
int main () {

   FILE*ptr = fopen("test.txt","r");
   char * buffer = malloc(sizeof(char)*100000);
   int i;
   int t1;
   int t2;
   double newstart, newend;
   double mytime;
   struct timeval start, end;

   for ( i=0; i<500; i++ ) {
      gettimeofday(&start, NULL);
      fread(buffer,16384,1,ptr);
      gettimeofday(&end, NULL);
      newstart = start.tv_sec + (double)start.tv_usec / 1000000.0;
      newend = end.tv_sec + (double)end.tv_usec / 1000000.0;
      mytime = newend - newstart;
      printf("%f\n", mytime);
   }

}

