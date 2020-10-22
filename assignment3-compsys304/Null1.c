#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

double getTime(){
  struct timeval t;
  double sec, msec;
  
  while (gettimeofday(&t, NULL) != 0);
  sec = t.tv_sec;
  msec = t.tv_usec;
  
  sec = sec + msec/1000000.0;
  
  return sec;
}

int main (int argc, char *argv[])
{
    double t1, t2; 
    unsigned int N = 1000;

    double *a[N];
    double *b[N];
    double *c[N];

    for(int i = 0; i < N; i++)
    {
        a[i] = (double *)malloc(N * sizeof(double));
        b[i] = (double *)malloc(N * sizeof(double));
        c[i] = (double *)malloc(N * sizeof(double));
    }

    // initializing the arrays
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            a[i][j] = i + j;
            b[i][j] = j;
            c[i][j] = 0;
        }
    }

    t1 = getTime();
    /* code to be measured goes here */
    /***************************************/
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            for(int k = 0; k < N; k++) {
                c[i][j] = c[i][j] + a[i][k]*b[k][j];
            }
        }
    }
    /***************************************/
	t2 = getTime(); 

    printf("time: %6.5f secs\n",(t2 - t1));

    free(a);
    free(b);
    free(c);
}