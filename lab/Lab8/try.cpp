#include "node.h"
#include <iostream>
using namespace std;
int main() {
/*
    Node A = Node(1,3);
    A.addChild(2);
    A.addChild(3);
    A[0].addChild(4);
    A[0].addChild(5);
    A[0].addChild(6);
    A[0][2].addChild(8);
    A[0][2].addChild(9);
    A[1].addChild(7);

    A.traverse();
    cout << endl;
    cout << A.getHeight() << " " << A[0].getHeight() << " " << A[1].getHeight()
         << " " << A[0][0].getHeight()<< endl;

    Node B = Node(1,3);
    B.addChild(3);
    B[0].addChild(5);
    B[0].addChild(6);
    B.addChild(2);
    B.addChild(4);

    B.traverse();
    cout << endl;

    Node C = Node(2,3);
    C.addChild(-4);
    C.addChild(5);
    C.addChild(6);
    C[2].addChild(8);
    C[2].addChild(9);
    C.traverse();
    cout << endl;
    Node D = Node(6, 3);
    D.addChild(8);
    D.addChild(9);
    D.traverse();
    cout << endl;
    Node E = Node(-4, 3);
    E.traverse();
    cout << endl;
    cout << C.contain(&E) << endl;

    cout << A.contain(&D) << endl;

    cout << A.contain(&C) << endl;
    cout << A.contain(&B) << endl;
*/
    Node G = Node(1, 5);
    G.addChild(2);
    G.addChild(3);
    G.addChild(4);
    G.addChild(5);
    G.addChild(6);
    G[0].addChild(7);
    G[0].addChild(8);
    G[1].addChild(9);
    G[2].addChild(10);
    G[2][0].addChild(11);
    G[2][0][0].addChild(16);
    G[2][0][0].addChild(21);
    G[2][0][0][0].addChild(18);
    G[2][0][0][0][0].addChild(19);
    G[2][0][0][0][0].addChild(20);
    G[3].addChild(12);
    G[4].addChild(13);
    G[4][0].addChild(14);
    G[4][0].addChild(15);
    G[4][0][0].addChild(17);
    G[4][0][1].addChild(22);
    G.traverse();
    cout << endl;
    cout << G[1].getHeight() << " " << G[2][0].getHeight() << " " << G[2][0][0][1].getHeight() << G[4].getHeight();

    Node H = Node(18);
    H.addChild(19);
    H.addChild(20);
    cout << G.contain(&H) << endl;
    return 0;
}