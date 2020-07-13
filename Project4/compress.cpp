#include "binaryTree.h"
#include "huffmanTree.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
int main(int argc, char *argv[]) {
    ifstream readCompress;
    if (argc == 3) readCompress.open(argv[2]);
    else if (argc == 2) readCompress.open(argv[1]);
    if (readCompress.is_open()) {


        readCompress.close();
    }
    else cout << "Failed to open file!" << endl;

    return 0;
}