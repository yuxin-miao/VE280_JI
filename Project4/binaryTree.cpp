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
void deleteNode (Node * node) {
    if (node->leftSubtree()) deleteNode(node->leftSubtree());
    if (node->rightSubtree()) deleteNode(node->rightSubtree());
    delete node;
}
void Node::setleft(Node *n) {
    if (this->leftSubtree()) {
        deleteNode(this->leftSubtree());
    }
    left = n;
}

void Node::setright(Node *n) {
    if(this->rightSubtree()) {
        deleteNode(this->rightSubtree());
    }
    right = n;
}

void Node::incnum() {num++;}

Node *Node::mergeNodes(Node *leftNode, Node *rightNode) {
    Node *temp = new Node(leftNode->str + rightNode->str, leftNode->num + rightNode->num, leftNode, rightNode);
    temp->setleft(leftNode);
    temp->setright(rightNode);
    return temp;
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

bool hasPath(Node* root, string& path, const string& s, bool left) {
    if (!root) return false; // root is null, no path
    if (left) path += "0";
    else path += "1";
    if (root->getstr() == s) return true; // find s, path exist
    if (hasPath(root->leftSubtree(), path, s, true) || hasPath(root->rightSubtree(), path, s, false)) return true;
    path.pop_back();
    return false;
}
string BinaryTree::findPath(const string &s) const{
    string path;
    if (root->getstr() == s) return path;
    if (hasPath(root->leftSubtree(), path, s, true)
        || hasPath(root->rightSubtree(), path, s, false)) return path;
    else return "-1";
}

int sumHelper (Node* root) { // helper function for sum
    if (!root) return 0; // base: empty node
    return root->getnum() + sumHelper(root->leftSubtree()) + sumHelper(root->rightSubtree());
}
int BinaryTree::sum() const {
    return sumHelper(root);
}

int depthHelper(Node* root) { // helper function for depth
    if (!root) return 0; // base is the empty node
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
    cout << root->getnum() << " "; // first node
    preorderNumHelper(root->leftSubtree()); // then left
    preorderNumHelper(root->rightSubtree()); // final right
}
void BinaryTree::preorder_num() const {
    preorderNumHelper(root);
    cout << endl;
}

void inorderStrHelper(Node* root) {
    if (!root) return;
    inorderStrHelper(root->leftSubtree()); // first left
    cout << root->getstr() << " "; // then node
    inorderStrHelper(root->rightSubtree()); // final right
}
void BinaryTree::inorder_str() const {
    inorderStrHelper(root);
    cout << endl;
}

void postorderNumHlper(Node* root) {
    if (!root) return;
    postorderNumHlper(root->leftSubtree()); // first left
    postorderNumHlper(root->rightSubtree()); // then right
    cout << root->getnum() << " "; // final the node
}
void BinaryTree::postorder_num() const {
    postorderNumHlper(root);
    cout << endl;
}

bool pathHelper(Node* root, int temp) {
    if (!root) return true; // with an empty node could not determine
    if (!root->rightSubtree() && !root->rightSubtree()) return (temp - root->getnum() < 0);
    // with a leaf, could determine through the value minus the leaf's value
    return pathHelper(root->leftSubtree(), temp - root->getnum()) &&
            pathHelper(root->rightSubtree(), temp - root->getnum()); // don't care whether the subtree is empty
}
bool BinaryTree::allPathSumGreater(int temp) const {
    if (!root) {cout << "The tree is empty!"; return false;}
    return pathHelper(root, temp);
}

bool coverdHelper(Node* root, Node* tree_root) { // whether root is covered by tree_root
    if(!root) return true;
    if(!tree_root) return false;
    if (root->getnum() != tree_root->getnum()) return false;
    return coverdHelper(root->leftSubtree(), tree_root->leftSubtree()) && coverdHelper(root->rightSubtree(), tree_root->rightSubtree());
}
bool BinaryTree::covered_by(const BinaryTree &tree) const {
    return coverdHelper(root, tree.root);
}

bool BinaryTree::contained_by(const BinaryTree &tree) const {
    if (coverdHelper(root, tree.root)) return true;
    return coverdHelper(root, tree.root->leftSubtree()) || coverdHelper(root, tree.root->rightSubtree());
}

void copyFrom(Node* root, Node* new_copy) {
    if (!new_copy) return;
    if (root->leftSubtree()) {Node* new_left = new Node(root->leftSubtree()->getstr(), root->leftSubtree()->getnum()); new_copy->setleft(new_left);}
    if (root->rightSubtree()) {Node* new_right = new Node(root->rightSubtree()->getstr(), root->rightSubtree()->getnum()); new_copy->setright(new_right);}
    copyFrom(root->leftSubtree(), new_copy->leftSubtree());
    copyFrom(root->rightSubtree(), new_copy->rightSubtree());
}
BinaryTree BinaryTree::copy() const {
    if (!root) {return BinaryTree(nullptr);}
    Node* new_copy = new Node(root->getstr(), root->getnum());
    copyFrom(root, new_copy);
    return BinaryTree(new_copy);
}

