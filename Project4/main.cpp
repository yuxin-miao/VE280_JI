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
    N1->setleft(N2);
    N1->setright(N3);
    N3->setright(N6);
    N2->setright(N7);
    N2->setleft(N8);
    BinaryTree emptyTree(nullptr);
    BinaryTree Tree1(N1);

    Node* D1 = new Node("ab", 9);
    BinaryTree Tree2(D1);

    Node* A1 = new Node("xy", 10);
    Node* A2 = new Node("uu", 11);
    A1->setleft(A2);
    BinaryTree Tree3(A1);

    Node* B2 = new Node("ku", 9);
    Node* B1 = new Node("mm", 7, nullptr, B2);
    BinaryTree Tree4(B1);
   /* cout << emptyTree.depth()  <<" Tree1:" << Tree1.depth() << " Tree2:" << Tree2.depth() << " Tree3:"
    << Tree3.depth() << " Tree4:" << Tree4.depth() << endl;*/
    emptyTree.postorder_num();
    Tree1.postorder_num();
    Tree2.postorder_num();
    Tree3.postorder_num();
    Tree4.postorder_num();
    return 0;
}