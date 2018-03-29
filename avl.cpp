

#define MAX(a,b) (a > b ? a : b)
#define ABS(a) (a < 0 ? -a : a)

#include <iostream>
#include <assert.h>
#include <stack>
#include <queue>
#include <time.h>
#include <stdlib.h>
using namespace std;

template <class T>
struct TreeNode {
    TreeNode *left = nullptr, *right = nullptr;
    T info;

    int multi = 1; // multiplicities
    int m_left = 0, m_right = 0;
        // total left and right multiplcities

    int height = 1;
        // height = 1 + max(left_height, right_height)
    int balance = 0;
        // balance factor

    TreeNode(const T& info) {
        left = right = 0;
        this->info = info;
    }
    ~TreeNode() {
        if (left) delete left;
        if (right) delete right;
    }

    int heights(int &lh, int &rh) {
        lh = left ? left->height : 0;
        rh = right ? right->height : 0;
        balance = lh - rh;
        height = 1 + MAX(lh, rh);
    }

    int child_balances(int &lb, int &rb) {
        lb = left ? left->balance : 0;
        rb = right ? right->balance : 0;
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

        int lh, rh;
        node->heights(lh, rh);

        return ret;
    }
    // rotates a node right, returns the new node
    TreeNode<T> * rotate_right(TreeNode<T> * node) {
        if (node == nullptr) return node;

        TreeNode<T> *ret = node->left;
        TreeNode<T> *temp = ret->right;
        ret->right = node;
        node->left = temp;

        int lh, rh;
        node->heights(lh, rh);

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

public:
    AVLTree() {}
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

    void _avl_insert(const T& elem, TreeNode<T> **droot)
    {
        TreeNode<T> **dptr = droot;
        stack<TreeNode<T>**> path;

        while (*dptr != nullptr) {
            path.push(dptr);
            if (elem < (*dptr)->info) {
                (*dptr)->m_left++;
                dptr = &((*dptr)->left);
            } else if (elem > (*dptr)->info) {
                (*dptr)->m_right++;
                dptr = &((*dptr)->right);
            } else { // elem == (*dptr)->info
                (*dptr)->multi++;
                goto balance;
            }
        }
        *dptr = new TreeNode<T>(elem);

        balance:
        int lh, rh, lb, rb;
        while (path.size()) {
            dptr = path.top(); path.pop();
            (*dptr)->heights(lh, rh); // simulaneously sets balance and height
            (*dptr)->child_balances(lb, rb);
            if ((*dptr)->balance > 1) { // skewed left
                if (lb < 0) (*dptr)->left = rotate_left((*dptr)->left);
                (*dptr)->heights(lh, rh); // simulaneously sets balance and height
                *dptr = rotate_right(*dptr);
            } else if ((*dptr)->balance < -1) { // skewed right
                if (rb > 0) (*dptr)->left = rotate_right((*dptr)->right);
                (*dptr)->heights(lh, rh); // simulaneously sets balance and height
                *dptr = rotate_left(*dptr);
            }
            (*dptr)->heights(lh, rh); // simulaneously sets balance and height
        }
    }

    void insert(const T& elem) {
        n_nodes++;
        int kth = n_nodes / 3 + ((n_nodes % 3) ? 1:0);

        if (root == nullptr) {
            root = new TreeNode<T>(elem); return;
        }

        if (elem > root->info) {
            
        } else if (elem < root->info) {
            
        } else {
            
        }
        _avl_insert(elem, &root);
    }

    void balanced() {
        cout << "Root balanced ? ";
        if (root && ABS(root->balance) <= 1)
            cout << "true" << endl;
        else
            cout << "false" << endl;
    }

    // prints triangle representation of this tree
    void print_tree() {
        if (!root) return;

        queue<TreeNode<T>*> Q;
        TreeNode<T> * ptr = nullptr;
        Q.push(root);

        size_t len;
        size_t level = 1;

        cout << "Root height: " << root->height << endl;

        while (Q.size()) {
            len = Q.size();
            for (; len > 0; --len) {
                ptr = Q.front(); Q.pop();
                if (ptr) {
                    cout << ptr->info << ", ";
                    if (level < root->height) {
                        Q.push(ptr->left); Q.push(ptr->right);
                    }
                } else {
                    cout << " ,";
                    if (level < root->height) {
                        Q.push(0); Q.push(0);
                    }
                }
            }
            cout << endl;
            level++;
        }
    }

    inline size_t size() { return n_nodes; }

private:
    TreeNode<T> *root = 0;
    size_t n_nodes = 0;
    size_t rot = 0;
};


int main() {
    AVLTree<int> tree;
    int s;
    srand(1234);
    for (int i = 0; i < 10; ++i) {
        //s = rand() % 10;
        s = i;
        cout << "Inserting " << s << endl;
        tree.insert(s);
        tree.print_tree();
        tree.balanced();
        cout << endl;
    }
    return 0;
}

