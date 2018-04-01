
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <time.h>
#include <sys/time.h>
#include "avl.h"
using namespace std;

#define TEN_E_6 (1000000)

//returns the total time taken to insert and delete
long long run_program() {
    AVLTree<int> tree;
    int s;
    bool insert = false;
    long long total_microseconds = 0;
    struct timeval start, end;

    for (int i = 0; i < 1000000; ++i) {
        insert = (tree.size() < 25 && (rand() & 1)) ? true : !tree.size();
        s = rand() % 100;

        gettimeofday(&start, NULL);
        if (insert) tree.insert(s);
        else tree.remove(s);
        gettimeofday(&end, NULL);

        //tree.print_tree();
        //cout << endl;

        total_microseconds += (long long)(end.tv_usec - start.tv_usec);
        total_microseconds += (long long)(end.tv_sec - start.tv_sec) * TEN_E_6;

    }
    //tree.print_tree();

    return total_microseconds;
}

long long get_average_time(int num_iterations)
{
    int ii;
    unsigned long long total_microseconds = 0, temp_total_microseconds = 0;
    for(ii = 0; ii < num_iterations; ii++){
        total_microseconds += run_program();
        //overflow
        if(temp_total_microseconds > total_microseconds){
            return -1;
        }
        temp_total_microseconds = total_microseconds;
    }
    return total_microseconds / num_iterations;
}

int main(int argc, char ** argv) {
    //srand(198712345);
    srand(time(NULL));
    long long total_microseconds;
    cout << "RUNNING PROGRAM" << endl;

    total_microseconds = get_average_time(5);

    printf("The average time for 10000 insertions and deletions took %lld seconds ", 
           (long long)total_microseconds / TEN_E_6);
    printf("and %lld, microseconds for 100000 insertions and deletions\n",
            total_microseconds % TEN_E_6);
    return 0;
}

