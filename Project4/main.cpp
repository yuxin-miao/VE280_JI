#include "binaryTree.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;


int main(int argc, char *argv[]) {
    Node* N1 = new Node("a", 3);
    Node* N2 = new Node("b",6);
    Node* N3 = new Node("c", 9);
    Node* N4 = new Node("d", 10);
    Node* N5 = new Node("e", 13);
    Node* N6 = new Node("f", 2, N4, N5);
    Node* N7 = new Node("g",18);
    Node* N8 = new Node("h",4);
    Node* N9 = new Node("pp", 1);
    N1->setleft(N2);
    N1->setright(N3);
    N3->setright(N6);
    N2->setright(N7);
    N2->setleft(N8);
    N4->setleft(N9);
    BinaryTree emptyTree(nullptr);
    BinaryTree Tree1(N1);
    cout << Tree1.findPath("a") << endl;

    Node* D1 = new Node("ab", 3);
    BinaryTree Tree2(D1);

    Node* A1 = new Node("xy", 3);
    Node* A2 = new Node("uu", 6);
    A1->setleft(A2);
    BinaryTree Tree3(A1);

    Node* B3 = new Node("f", 13);
    Node* B5 = new Node("uy",1);
    Node* B4 = new Node("xxx", 10, B5);
    Node* B2 = new Node("ku", 2, B4, B3);
    Node* B1 = new Node("mm", 9, nullptr, B2);

    BinaryTree Tree4(B1);

    Node* C1 = new Node("io", 4);
    Node* C2 = new Node("p", 18);
    Node* C3 = new Node("joj", 6, C1, C2);
    Node* C4 = new Node("pop", 11);
    C1->setright(C4);
    BinaryTree Tree5(C3);


   /* cout << emptyTree.depth()  <<" Tree1:" << Tree1.depth() << " Tree2:" << Tree2.depth() << " Tree3:"
    << Tree3.depth() << " Tree4:" << Tree4.depth() << endl;*/
    /*emptyTree.postorder_num();
    Tree1.postorder_num();
    Tree2.postorder_num();
    Tree3.postorder_num();
    Tree4.postorder_num();
    Tree5.postorder_num();
    Tree5.inorder_str();
    cout << Tree5.contained_by(Tree1)<< endl;
    cout << Tree4.covered_by(Tree1) << endl; */
    BinaryTree Tree6 = Tree1.copy();
    Tree1.preorder_num();
    Tree6.preorder_num();
    BinaryTree Tree7 = Tree6.copy();
    BinaryTree Tree8 = Tree4.copy();
    cout << Tree8.covered_by(Tree4) << endl;

    BinaryTree Tree9 = Tree8.copy();
    Tree9.preorder_num();
    Tree8.preorder_num();
    BinaryTree Tree10 = Tree9.copy();
    BinaryTree Tree11 = emptyTree.copy();
    cout << Tree11.depth();
    return 0;
}