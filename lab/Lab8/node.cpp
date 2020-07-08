#include <iostream>
#include <string>
#include "node.h"

using namespace std;

Node::Node(int _value, int _n) :value(_value), child_num(0), n(_n),
        parent(nullptr), children(new Node*[n]),height(0) {}
  // an array of pointer to Node

void Node::delete_tree() {
    if (child_num != 0) {
        for (int i = 0;i < child_num; i++) {
            delete children[i];
        }
    }

}
Node::~Node() {
    delete_tree();
    delete [] children;
}

void Node::addChild(Node *child) {
    if (n != child->n) cout << "WRONG in add child" << endl;
    if (child_num >= n) throw tooManyChildren();
    children[child_num] = child;
    children[child_num]->parent = this;
}

void Node::addChild(int _value) {
    if (child_num >= n) throw tooManyChildren();
    addChild(new Node(_value, n));
    child_num++;
}

void Node::traverse() const{
    cout << value << " ";
    for (int i = 0; i < child_num; i++) {
        children[i]->traverse();
    }

}

int Node::getHeight() {
    if (child_num == 0) return 0;
    int* arr = new int[child_num];

    for (int i = 0; i < child_num; i++) {
        arr[i] = children[i]->getHeight();
    }
    for (int i = 0; i < child_num; i++) {
        if (height < arr[i]) height = arr[i];
    }
    delete [] arr;
    return height + 1;
}

Node &Node::operator[](int i) {
    if (i >= child_num) throw invalidIndex();
    return *children[i];
}

bool Node::contain(Node *sub) {
    bool to_return = false;
    if (this->getHeight() < sub->getHeight()) return false; // height is less, no possibility
    else if (this->getHeight() == sub->getHeight()) {
        string this_des, sub_des;
        this->descendant(this_des);
        sub->descendant(sub_des);
        if (this_des == sub_des) return true; // compare the descendants
        else return false;
    }
    else {
        for (int i = 0; i < child_num; i++){
            to_return = children[i]->contain(sub);
            if (to_return) return to_return;
        }
    }
    return to_return;
}

void Node::descendant(std::string &des) { // return all the descendants of this root, order matters
    des += to_string(value);
    for (int i = 0; i < child_num; i++) {
        children[i]->descendant(des);
    }

}








