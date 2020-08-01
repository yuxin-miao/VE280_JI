#include <iostream>
using namespace std;
template <class T>
class GoodTree {
    T *op;
    GoodTree *left;
    GoodTree *right;
public:
    void removeAll();
    // EFFECTS: remove all things of "this"
    void insert(T *op);
    // REQUIRES: T type has a linear order "<"
    // EFFECTS: insert op into "this" with the correct location
    //					Assume no duplicate op.
    void copyAll(GoodTree<T>*gt);
    void copyTree(GoodTree<T>*gt);
    void copy_helper(const GoodTree<T> *t);
};

template<class T>
void GoodTree<T>::copyTree(GoodTree<T> *gt) {
    if (*this != gt) {
        removeAll();
    }
    copyAll(gt);
}

template<class T>
void GoodTree<T>::copyAll(GoodTree<T> *gt) {
    T* tmp = new T(gt->op);

    insert(new T*(gt->op));
    if (gt->left) copyAll(gt->left);
    if (gt->right) copyAll(gt->right);
}

template <class T>
void GoodTree<T>::copy_helper(const GoodTree<T> *t) {
    if (t == nullptr)
        return;
    T *tmp = new(t->op);
    insert(tmp);
    copy_helper(t->left);
    copy_helper(t->right);
}
/*
template <class T>
void GoodTree<T>::copyAll(const GoodTree<T> &t) {
    removeAll();
    copy_helper(&t);
}*/