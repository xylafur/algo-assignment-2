#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define MAX_TRIPLE_LIMIT 1024

//n is the size of the martix
void generate_1024_m(int M[1024][3], int n)
{
  int ii;
  for(ii = 0; ii < 1024; ii++){
    M[ii][0] = rand() % n;
    M[ii][1] = rand() % n;
    M[ii][2] = rand() % MAX_TRIPLE_LIMIT;
  }
}

void add_triples(int * N, int M[1024][3], int n)
{
  int ii;
  for(ii = 0; ii < 1024; ii++)
    N[M[ii][0]* n + M[ii][1]] += M[ii][2];
}

#define TEN_TO_THE_6 (10000000)
#define NUM_M 3
#define NUM_N 6

int n_vals [NUM_N] = {15, 64, 256, 1024, 4096, 16384};
long long m_vals [NUM_M] = {1024, 1677721600, 13421772800};

int main()
{
  int ii, jj, n;
  long long m, temp_m;
  int * N;
  int M [1024][3];
  long long total_microseconds;

  struct timeval begin, end;

  srand(time(NULL));

  for(ii = 0; ii < NUM_M; ii++){
    for(jj = 0; jj < NUM_N; jj++){
      total_microseconds = 0;

      n = n_vals[jj];
      m = temp_m = m_vals[ii];

      //we just use 0 for each value in N
      N = malloc(sizeof(int) * n * n);
      memset(N, 0, sizeof(int) * n * n);

      printf("Running algorithm for n = %d and m = %lld\n", n, m);

      while(temp_m > 0){
        generate_1024_m(M, n);

        gettimeofday(&begin, NULL);
        add_triples(N, M, n);
        gettimeofday(&end, NULL);

        total_microseconds += (long long)(end.tv_usec - begin.tv_usec);
        total_microseconds += (long long)(end.tv_sec - begin.tv_sec) * 
                              TEN_TO_THE_6;
        temp_m -= 1024;
      }
      printf("It took %lld microseconds\n\n", total_microseconds);
    }
  }

  return 0;
}
