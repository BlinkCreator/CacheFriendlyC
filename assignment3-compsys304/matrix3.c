
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
    int N = 1000;
    int M = 1;
    int sum;
    int block_size = 50;
	 
    //intialzing the arrays
    double **a = (double **)malloc(N * sizeof(double *)); 
    double **b = (double **)malloc(N * sizeof(double *)); 
    double **c = (double **)malloc(N * sizeof(double *)); 
    for (int i=0; i<N; i++){
         a[i] = (double *)malloc(N * sizeof(double)); 
         b[i] = (double *)malloc(N * sizeof(double)); 
         c[i] = (double *)malloc(N * sizeof(double)); 
         
    }
  // initializing the array values
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            a[i][j] = 1;
            b[i][j] = 1;
            c[i][j] = 1;
        }
    }



	t1 = getTime();

	//Code to be measured goes in here
    for (int repeat = 0; repeat < M; repeat++){
        // transposing the matrix b so that collomns act as rows
        
         for (int i = 0; i <  N; i+=block_size){ 
            for (int j = 0; j < N; j+=block_size){
                //sum = 0;
                for (int k = 0; k < N; k+=block_size) {
                    for(int i1 = i; i1< i+block_size; i1++){
                        for(int j1 = j; j1 < j +block_size; j1++){
                            for(int k1 = k; k1 < k+block_size; k1++){
                                c[i1][j1] += a[i1][k1] * b[k1][j1];
                            }
                        }
                    }
                    // sum += a[i][k] * b_transpose[k][j];
                }     
                //c[i][j] = sum;
            }
         }
    }

	t2 = getTime(); 

    printf("time: %6.5f secs\n",(t2 - t1));
    printf("Last C value: %6.5f \n",(c[N-1][N-1]));
    free(a);
    free(b);
    free(c);
}
    
