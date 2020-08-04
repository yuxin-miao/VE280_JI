#include "binaryTree.h"

// Implement the following methods listed below.
// You don't need to implement the other methods.
// If you decide to implement the other methods,
// DON'T INCLUDE THEM IN YOUR SUBMISSION.
//
// In your implementations, you can call any other
// methods, even those you don't need to implement.

BinaryTree::BinaryTree(int v, const BinaryTree &lChild,
                       const BinaryTree &rChild) {
    this->v = v;
    this->empty = false;
    this->left = new BinaryTree(lChild);
    this->right = new BinaryTree(rChild);
}

BinaryTree::BinaryTree(const BinaryTree &bt) {
    if (this == &bt) return;
    this->v = bt.v;
    this->empty = bt.empty;
    if (bt.left) this->left = new BinaryTree(*bt.left);
    if (bt.right) this->right = new BinaryTree(*bt.right);
}

BinaryTree &BinaryTree::operator=(const BinaryTree &bt) {
    if (this != &bt) {
        removeAll();
        this->v = bt.v;
        this->empty = bt.empty;
        if (bt.left) this->left = new BinaryTree(*bt.left);
        if (bt.right) this->right = new BinaryTree(*bt.right);
    }
    return *this;
}

bool BinaryTree::isSorted() {
    if (empty) return true;
    if (left && !left->empty) {
        if (this->v < left->v) return false;
        if (left->right && !left->right->empty &&  this->v < left->right->v) return false;
    }
    if (right && !right->empty) {
        if (this->v > right->v) return false;
        if (right->left && !right->left->empty && this->v > right->left->v) return false;
    }
    return left->isSorted() && right->isSorted();
}

int BinaryTree::count() {
    if (empty) return 0;
    int count = 1;
    if (left) count = count + left->count();
    if (right) count = count + right->count();
    return count;
}