#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>


void populate_char_array(char * C, unsigned long len)
{
    unsigned long i;
    for(i = 0; i < len; i++)
        C[i] = i % 20;
}

void perform_computations(char * C, unsigned long len)
{
    unsigned long long num_computations = len * 5, i;
    for(i = 0; i < num_computations; i++){
        C[i % len] += C[2 * i % len];
        C[3 * i % len] *= C[i % len];
    }
}

#define num_multipliers 15
float multipliers [num_multipliers] = {
    .5, .6, .7, .8, .9, .95, .99, 1.0, 1.01, 1.1, 1.5, 2.0, 5.0, 10.0, 50.0
};

int main(int argc, char * argv [])
{
    if(argc != 2){
        printf("Must only supply the active set size in bytes as param\n");
        exit(1);
    }
    int M = atoi(argv[1]);
    char * C;
    int i;
    unsigned long len;
    struct timeval start, end;
    for(i = 0; i < num_multipliers; i++){
        len = (unsigned long)M * multipliers[i];
        //allocate M * multiplier bytes for C
        C = malloc(sizeof(char) * len);
        printf("Computations of C = %0.2f * M took ", multipliers[i]);
        gettimeofday(&start, NULL);
        perform_computations(C, len);
        gettimeofday(&end, NULL);
        printf("%d seconds and %d microseconds\n", end.tv_sec - start.tv_sec,
               end.tv_usec - start.tv_usec);
        free(C);
    }
}
