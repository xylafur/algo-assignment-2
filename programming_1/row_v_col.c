#include<sys/time.h>
#include<stdio.h>
#include <stdlib.h>

//for this problem I will use char matricies to save space

//Initialize's a matrix of size rows by columns with values between 1 and 10
void initialize_matrix(char ** matrix, int rows, int cols)
{
    int i = 0, r, c;
    for(r = 0; r < rows; r++){
        for(c = 0; c < cols; c++){
            matrix[r][c] = i++ % 10;

        }
    }
}

void row_major_multiplication(char ** A, char ** B, char ** C, int N)
{
    int r, c;
    for(r = 0; r < N; r++){
        for(c = 0; c < N; c++){
            //D[r][c] = A[r][c] + B[r][c];
            C[r][c] = A[r][c] + B[r][c];
        }
    }
}

void column_major_multiplication(char ** A, char ** B, char ** C, int N)
{
    int r, c;
    for(c = 0; c < N; c++){
        for(r= 0; r < N; r++){
            //D[r][c] = A[r][c] + B[r][c];
            C[r][c] = A[r][c] + B[r][c];
        }
    }
}

//takes in the matrix multiplication function and its params
void matrix_multiplication_timing_function(void(*func)(char**,char**,char**,int),
                                           char **A, char **B, char ** C, int N)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    func(A, B, C, N);
    gettimeofday(&end, NULL);
    printf("took %f seconds and %f microseconds\n", end.tv_sec - start.tv_sec, 
           end.tv_usec - start.tv_usec);
}

#define NUMBER_N 9
unsigned int n_sizes [NUMBER_N] = {128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768};

int main()
{
    void (*row_maj)(char**,char**,char**,int);
    void (*col_maj)(char**,char**,char**,int);
    row_maj = &row_major_multiplication;
    col_maj = &column_major_multiplication;

    char **A, **B, **C;

    int i, o;
    unsigned int N;

    printf("Running matrix multiplication program\n");

    for(i = 0; i < NUMBER_N; i++){
        N = n_sizes[i];
        A = malloc(sizeof(char *) * N);
        B = malloc(sizeof(char *) * N);
        C = malloc(sizeof(char *) * N);
        for(o = 0; o < N; o++){
            A[o] = malloc(sizeof(char) * N);
            B[o] = malloc(sizeof(char) * N);
            C[o] = malloc(sizeof(char) * N);
        }
        initialize_matrix(A, N, N);
        initialize_matrix(B, N, N);
        initialize_matrix(C, N, N);

        printf("Row major matrix multiplication for N = %d ", N);
        row_maj(A, B, C, N);

        initialize_matrix(A, N, N);
        initialize_matrix(B, N, N);
        initialize_matrix(C, N, N);

        printf("Column major matrix multiplication for N = %d ", N);
        col_maj(A, B, C, N);

        for(o = 0; o < N; o++){
            free(A[o]);
            free(B[o]);
            free(C[o]);
        }
 

        free(A);
        free(B);
        free(C);
    }


}

