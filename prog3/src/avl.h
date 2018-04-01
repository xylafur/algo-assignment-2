
#pragma once

#define MAX(a,b) (a > b ? a : b)
#define ABS(a) (a < 0 ? -a : a)

#include <iostream>
#include <assert.h>
#include <stack>
#include <queue>
#include <time.h>
#include <stdlib.h>
#include <type_traits>
using namespace std;

#define M 3650722200

template <class T>
struct TreeNode {
    TreeNode *left = nullptr, *right = nullptr;
    T info;

    size_t height = 1;
        // height = 1 + max(left_height, right_height)
    int balance = 0;
        // balance factor

    long long *matrix __attribute__((used)) = 0;
    size_t mat_size = 0;

    TreeNode(const T& info, unsigned long long m_size) {
        this->info = info;
        // Modification for problem
        switch (info % 3) {
            case 0: mat_size = m_size * 3/4; break; // 2^20
            case 1: mat_size = m_size; break; // 2^19 + 2^18 = 3*2^18
            case 2: mat_size = m_size * 5/4; break; // 2^18 + 2^17 = 3*2^17
        }
        printf("m_size: %llu\n", m_size);
        printf("Original M: %llu\n", M);
 
        matrix = new long long [(size_t)mat_size];
        memset(matrix, rand() % 256, sizeof(long long) * mat_size);
    }
    TreeNode(TreeNode<T> &&move) {
        left = move.left;
        right = move.right;
        move.left = move.right = nullptr;
        info = std::move(info);

        // Modificiation for problem
        matrix=move.matrix;
        mat_size = move.mat_size;
        move.matrix = nullptr;
    }

    ~TreeNode() {
        if (left) delete left;
        if (right) delete right;
        if (matrix) delete matrix;
    }

    void heights(int *lh, int *rh) {
        int L = left ? left->height : 0;
        int R = right ? right->height : 0;
        balance = L - R;
        height = 1 + MAX(L, R);
        if (lh) *lh = L;
        if (rh) *rh = R;
    }

    void child_balances(int *lb, int *rb) {
        if (lb) *lb = left ? left->balance : 0;
        if (rb) *rb = right ? right->balance : 0;
    }
};

template <class T>
class AVLTree
{
protected:

    TreeNode<T> * rotate_left(TreeNode<T> * node) {
        if (node == nullptr) return node;

        TreeNode<T> *ret = node->right;
        TreeNode<T> *temp = ret->left;
        ret->left = node;
        node->right = temp;

        node->heights(0, 0);
        ret->heights(0, 0);

        return ret;
    }

    // rotates a node right, returns the new node
    TreeNode<T> * rotate_right(TreeNode<T> * node) {
        if (node == nullptr) return node;

        TreeNode<T> *ret = node->left;
        TreeNode<T> *temp = ret->right;
        ret->right = node;
        node->left = temp;

        node->heights(0, 0);
        ret->heights(0, 0);

        return ret;
    }

    void copy_tree(TreeNode<T> **ptr, const AVLTree &copy)
    {
        if (copy.root == nullptr) return;
        if (*ptr) delete *ptr;
        *ptr = new TreeNode<T>(copy.root.info);
        copy_tree(&((*ptr)->left), copy.left);
        copy_tree(&((*ptr)->right), copy.right);
    }

    void balance(stack<TreeNode<T>**> &path) {
        if (!path.size()) return;

        int lb, rb;
        TreeNode<T> **dptr;
        while (path.size()) {
            dptr = path.top(); path.pop();

            (*dptr)->heights(0, 0); // simulaneously sets balance and height
            (*dptr)->child_balances(&lb, &rb);

            if ((*dptr)->balance > 1) { // skewed left
                if (lb < -1) { // left child skewed right
                    (*dptr)->left = rotate_left((*dptr)->left);
                }
                //(*dptr)->heights(0, 0); // simulaneously sets balance and height
                *dptr = rotate_right(*dptr);
            } else if ((*dptr)->balance < -1) { // skewed right
                if (rb > 1) { // right child skewed left
                    (*dptr)->right = rotate_right((*dptr)->right);
                }
                //(*dptr)->heights(0, 0); // simulaneously sets balance and height
                *dptr = rotate_left(*dptr);
            }

        }
    }

    bool _avl_insert(const T& elem, TreeNode<T> **droot, unsigned long long m_size)
    {
        TreeNode<T> **dptr = droot;
        stack<TreeNode<T>**> path;

        while (*dptr != nullptr) {
            path.push(dptr);
            if (elem < (*dptr)->info) {
                dptr = &((*dptr)->left);
            } else if (elem > (*dptr)->info) {
                dptr = &((*dptr)->right);
            } else { // elem == (*dptr)->info
                return 0;
            }
        }
        (*dptr) = new TreeNode<T>(elem, this->m_size);
        path.push(dptr);
        n_nodes++;

        balance(path);

        return 1;
    }

    bool _avl_delete(const T& elem, TreeNode<T> **droot, unsigned long long m_size)
    {
        TreeNode<T> **dptr = droot;
        stack<TreeNode<T>**> path;

        while (*dptr != nullptr && (*dptr)->info != elem) {
            path.push(dptr);
            if (elem < (*dptr)->info) {
                dptr = &((*dptr)->left);
            } else {
                dptr = &((*dptr)->right);
            }
        }

        if (*dptr == nullptr) {
            return 0;
        }

        n_nodes--;
        if ((*dptr)->left == nullptr || (*dptr)->right == nullptr) {
            TreeNode<T> *living_child = (*dptr)->left ?
                                        (*dptr)->left : (*dptr)->right;

            (*dptr)->left = (*dptr)->right = nullptr; delete *dptr;
            *dptr = living_child;
            if (living_child) path.push(dptr);

        } else { // both are children are non null

            TreeNode<T> **temp1 = &((*dptr)->right);
            while ((*temp1) && (*temp1)->left) {
                path.push(temp1);
                temp1 = &((*temp1)->left);
            }

            std::swap((*dptr)->info, (*temp1)->info);
            std::swap((*dptr)->matrix, (*temp1)->matrix);
            std::swap((*dptr)->mat_size, (*temp1)->mat_size);

            auto temp = (*temp1)->right;
            (*temp1)->right = nullptr;
            delete *temp1;
            *temp1 = temp;
        }
        balance(path);
        return 1;
    }

public:
    AVLTree() {}
    AVLTree(long long m_size) {
        this->m_size = m_size;
    }
    AVLTree(AVLTree<T> &&move)
    {
        this->n_nodes = move.n_nodes;
        this->root = move->root;
        move->root = 0;
    }

    AVLTree(const AVLTree<T> &copy)
    {
        copy_tree(copy);
    }

    ~AVLTree()
    {
        if (root) delete root;
    }

    inline bool insert(const T& elem) {
        return _avl_insert(elem, &root,this->m_size);
    }

    inline bool remove(const T& elem) {
        return _avl_delete(elem, &root, this->m_size);
    }

    // prints triangle representation of this tree
    void print_tree() {
        if (!root) return;

        queue<TreeNode<T>*> Q;
        TreeNode<T> * ptr = nullptr;
        Q.push(root);

        size_t len;
        size_t level = 1;

        cout << "n_nodes = " << n_nodes << ", root height = "
             <<  root->height << endl;
        while (Q.size()) {
            len = Q.size();
            for (; len > 0; --len) {
                ptr = Q.front(); Q.pop();
                if (ptr) {
                    cout << ptr->info << ",";
                    if (level < root->height) {
                        Q.push(ptr->left);
                        Q.push(ptr->right);
                    }
                } else {
                    cout << " ,";
                    if (level < root->height) {
                        Q.push(0);
                        Q.push(0);
                    }
                }
            }
            cout << endl;
            level++;
        }
    }

    void is_balanced() {
        if (root && ABS(root->balance) <= 1) {
            cout << "Tree is Balanced" << endl;
        } else {
            cout << "Tree is NOT Balanced" << endl;
        }
    }

    inline size_t size() { return n_nodes; }

private:
    TreeNode<T> *root = 0;
    size_t n_nodes = 0;
    size_t rot = 0;
    unsigned long long m_size;
};


