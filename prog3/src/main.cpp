
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <time.h>
#include "avl.h"
using namespace std;


void run_program() {
    AVLTree<int> tree;
    char buff[1024];
    int s;
    for (int i = 0; i < 50; i++) {
        s = rand() % 100;
        tree.insert(s);
        tree.is_balanced();
    }
    tree.print_tree();
    while (tree.size()) {
        s = rand() % 100;
        tree.remove(s);
        tree.print_tree();
        tree.is_balanced();
    }
}

int main(int argc, char ** argv) {
    cout << "RUNNING PROGRAM" << endl;
    run_program();
    return 0;
}

