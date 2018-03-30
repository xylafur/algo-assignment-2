
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
    struct timeval start, end;
    gettimeofday(&start, NULL);
    func(A, B, C, N);
    gettimeofday(&end, NULL);

    double usecs = end.tv_sec * 1000000 + end.tv_usec;
    usecs -= start.tv_sec * 1000000 + start.tv_usec;
    printf("  Time:%.2f microseconds\n", usecs);
}

int main(int argc, char ** argv)
{
    puts("Running matrix multiplication program\n");

    int n_tests = 9;
    if (argc > 1)
        n_tests = ((n_tests = atoi(argv[1])) > 0 && n_tests < 9) ? n_tests : 4;

    unsigned int test_sizes[] = {
        128,    // 0
        256,    // 1
        512,    // 2
        1024,   // 3
        2048,   // 4
        4096,   // 5
        8192,   // 6
        16384,  // 7
        32768   // 8
    };

    unsigned int N;
    int *A, *B, *C;

    int i, o;
    for(i = 0; i < n_tests; i++){
        N = test_sizes[i];
        A = initialize_matrix(N, N);
        B = initialize_matrix(N, N);
        C = initialize_matrix(N, N);
        printf("Test #%d, Matrix Length N: %d\n", i, N);

        printf("Row major matrix addition:\n", N);
        matrix_addition_timer(&row_major_addition, A, B, C, N);

        printf("Column major matrix addition:\n", N);
        matrix_addition_timer(&col_major_addition, A, B, C, N);

        free(A);
        free(B);
        free(C);
        puts("");
    }

    return 0;
}

