
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Initialize's a matrix of size rows by columns with values between 1 and 10
int* initialize_matrix(int rows, int cols)
{
    int *mat = malloc(rows * cols * sizeof(int));
    int r, c;
    for(r = 0; r < rows; r++)
        for(c = 0; c < cols; c++)
            mat[r * rows + c] = rand() % 10;
    return mat;
}

void row_major_addition(int *A, int *B, int *C, int N)
{
    int r, c;
    for(r = 0; r < N; r++)
        for(c = 0; c < N; c++)
            C[r * N + c] = A[r * N + c] + B[r * N + c];
}

void col_major_addition(int *A, int *B, int *C, int N)
{
    int r, c;
    for(c = 0; c < N; c++)
        for(r= 0; r < N; r++)
            C[r * N + c] = A[r * N + c] + B[r * N + c];
}

//takes in the matrix multiplication function and its params
void matrix_addition_timer(void(*func)(int*,int*,int*,int),
                           int *A, int *B, int * C, int N)
{
    clock_t time = clock();
    func(A, B, C, N);
    time = clock() - time;

    double secs = (double)time / CLOCKS_PER_SEC;
    printf("\tN:%d\tT:%.10f\n", N, secs);
}

int main()
{
    printf("Running matrix multiplication program\n");

    unsigned int test_sizes[] = {
        128, 256, 512, 1024, 2048,
        4096, 8192, 16384, 32768
    };
    unsigned int N;
    int *A, *B, *C;

    int i, o;
    for(i = 0; i < sizeof(test_sizes)/sizeof(int); i++){
        N = test_sizes[i];
        A = initialize_matrix(N, N);
        B = initialize_matrix(N, N);
        C = initialize_matrix(N, N);

        printf("Row major matrix addition:\n", N);
        matrix_addition_timer(&row_major_addition, A, B, C, N);

        printf("Column major matrix addition:\n", N);
        matrix_addition_timer(&col_major_addition, A, B, C, N);

        free(A);
        free(B);
        free(C);
    }
}

