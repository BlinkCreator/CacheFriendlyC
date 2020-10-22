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
    // As the cache of my processor is 128 KB, each core would get 32 KB.
    // Total doubles in 32 KB = 4095 => sqrt(4096) = 64
    // Closest factor of 1000 to 64 is 50
    unsigned int K = 50; // length of the block

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
    for(int i = 0; i < N; i+=K) {
        for(int j = 0; j < N; j+=K) {
            for(int k = 0; k < N; k+=K) {
                for(int ii = i; ii < i+K; ii++) {
                    for(int jj = j; jj < j+K; jj++) {
                        for(int kk = k; kk < k+K; kk++) {
                            c[ii][jj] = c[ii][jj] + a[ii][kk]*b[kk][jj];
                        }
                    }
                }
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