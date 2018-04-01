
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
        insert = (tree.size() < 50 && (rand() & 1)) ? true : !tree.size();
        s = rand() % 100;

        gettimeofday(&start, NULL);
        if (insert) tree.insert(s);
        else tree.remove(s);
        gettimeofday(&end, NULL);

        total_microseconds += (long long)(end.tv_usec - start.tv_usec);
        total_microseconds += (long long)(end.tv_sec - start.tv_sec) / TEN_E_6;

    }
    tree.print_tree();

    return total_microseconds;
}

int main(int argc, char ** argv) {
    long long total_microseconds;
    cout << "RUNNING PROGRAM" << endl;
    total_microseconds = run_program();

    printf("Took a total of %lld seconds and %lld, microseconds\n",
           (long long)total_microseconds / TEN_E_6, total_microseconds % TEN_E_6);
    return 0;
}

