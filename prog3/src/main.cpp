
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <time.h>
#include "avl.h"
using namespace std;

// time this
void run_program() {
    AVLTree<int> tree;
    int s;
    bool insert = false;
    for (int i = 0; i < 1000000; ++i) {
        insert = (tree.size() < 50 && (rand() & 1)) ? true : !tree.size();
        s = rand() % 100;
        if (insert) tree.insert(s);
        else tree.remove(s);
    }
    tree.print_tree();
}

int main(int argc, char ** argv) {
    cout << "RUNNING PROGRAM" << endl;
    run_program();
    return 0;
}

