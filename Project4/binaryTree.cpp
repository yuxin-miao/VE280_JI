#include "binaryTree.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

/* ================================== Node =================================== */
Node::Node(const std::string &str, int num, Node *left, Node *right)
: str(str), num(num), left(left), right(right)  {}

Node* Node::leftSubtree() const{return left;}

Node* Node::rightSubtree() const{return right;}

string Node::getstr() const {return str;}

int Node::getnum() const {return num;}

void Node::setleft(Node *n) {left = n;}

void Node::setright(Node *n) {right = n;}

void Node::incnum() {num++;}

Node *Node::mergeNodes(Node *leftNode, Node *rightNode) {
    return new Node(leftNode->str + rightNode->str, leftNode->num + rightNode->num, leftNode, rightNode);
}

/* =============================== Binary Tree =============================== */

BinaryTree::BinaryTree(Node *rootNode){
    root = rootNode;
}
void deleteNodes(Node* root) {
    // helper function for freeing all the memory allocated in this binary tree.
    if (root->leftSubtree())
        deleteNodes(root->leftSubtree());
    if (root->rightSubtree())
        deleteNodes(root->rightSubtree());
    delete root;
}
BinaryTree::~BinaryTree() {
    if (root) deleteNodes(root);
    else delete root;
}

string findPathHelper(Node* root, string &path, const string& s) {

    if (root->getstr() == s) return path;
    if (!root->leftSubtree() && !root->rightSubtree()) return "x";
    if (root->leftSubtree()) {return findPathHelper(root->leftSubtree(), path, s) == path ? path += "0" : path;}
    if (root->rightSubtree()) {return findPathHelper(root->rightSubtree(), path, s) == path ? path += "1": path;}
    return path;
}
/*
bool findPathHelper2(Node* root, string &path, const string& s) {
    static bool exist = false;
    if (root->getstr() == s) return true;
    if (!root->leftSubtree() && !root->rightSubtree()) return false;
    if (root->leftSubtree()) {if(findPathHelper2(root->leftSubtree(), path, s)) {path += "0";exist = true;}}
    if (root->rightSubtree() && !exist) {if(findPathHelper2(root->leftSubtree(), path, s)) path += "1";}

}*/
bool findPathHelper3(Node* root, string &path, const string& s) {
    if (root->getstr() == s) return true;
    if (!root->leftSubtree() && !root->rightSubtree()) return false;
    if (root->leftSubtree()) {if(findPathHelper3(root->leftSubtree(), path, s)) path += "0";}
    if (root->rightSubtree()) {if(findPathHelper3(root->leftSubtree(), path, s)) path += "1";}
    return true;
}
string BinaryTree::findPath(const string &s) const{
    if (root->getstr() == s) return "";
    string path;
    findPathHelper(root, path, s);
    if (path.empty()) return "-1";
    else return path;
}

int sumHelper (Node* root) { // helper function for sum
    if (!root) return 0;
    return root->getnum() + sumHelper(root->leftSubtree()) + sumHelper(root->rightSubtree());
}

int BinaryTree::sum() const {
    return sumHelper(root);
}

int depthHelper(Node* root) { // helper function for depth
    if (!root) return 0;
    int leftDepth = depthHelper(root->leftSubtree());
    int rightDepth = depthHelper(root->rightSubtree());
    if (leftDepth > rightDepth) return leftDepth + 1;
    else return rightDepth + 1;
}
int BinaryTree::depth() const {
    return depthHelper(root);
}

void preorderNumHelper(Node* root) {
    if (!root) return;
    cout << root->getnum() << " ";
    preorderNumHelper(root->leftSubtree());
    preorderNumHelper(root->rightSubtree());
}
void BinaryTree::preorder_num() const {
    preorderNumHelper(root);
}

void inorderStrHelper(Node* root) {
    if (!root) return;
    inorderStrHelper(root->leftSubtree());
    cout << root->getstr() << " ";
    inorderStrHelper(root->rightSubtree());
}
void BinaryTree::inorder_str() const {
    inorderStrHelper(root);
}

void postorderNumHlper(Node* root) {
    if (!root) return;
    postorderNumHlper(root->leftSubtree());
    postorderNumHlper(root->rightSubtree());
    cout << root->getnum() << " ";
}
void BinaryTree::postorder_num() const {
    postorderNumHlper(root);
}

bool BinaryTree::allPathSumGreater(int temp) const {
    // TODO: implement this function.
    return false;
}

bool BinaryTree::covered_by(const BinaryTree &tree) const {
    // TODO: implement this function.
    return false;
}

bool BinaryTree::contained_by(const BinaryTree &tree) const {
    // TODO: implement this function.
    return false;
}

BinaryTree BinaryTree::copy() const {
    // TODO: implement this function.
    return *this;
}

