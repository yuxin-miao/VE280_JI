#include "binaryTree.h"
#include "huffmanTree.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;
void printContent(Node* root, string code);
// EFFECTS: print the corresponding string in HTree through root with code
int countSpace(const string& str);
// EFFECTS: count spaces in string
int main(int argc, char *argv[]) {
    HuffmanTree HTree(argv[1]);
    ifstream binaryCode;
    stringstream ss;
    string codeContent;
    binaryCode.open(argv[2]);
    if (binaryCode.is_open()) {
        getline(binaryCode, codeContent);
        if (codeContent.empty()) {return 0;} // if the file is empty
        ss << codeContent;
        string code;
        int spaceNum = countSpace(codeContent);
        if (spaceNum == codeContent.length()) { // If the file only contain \n
            while (spaceNum > 0) {
                printContent(HTree.root, "");
                spaceNum--;
            }
        }
        while (ss >> code) {
            printContent(HTree.root, code);
        }
    }
    else cout << "binary code file open failed!" << endl;
    return 0;
}

void printContent(Node* root, string code) { // recursively call until find the right node
    if (code.empty()) {cout << root->getstr(); return;}
    else if (code[0] == '0') printContent(root->leftSubtree(), code.substr(1));
    else if (code[0] == '1') printContent(root->rightSubtree(), code.substr(1));
    else cout << "Something Wrong!" << endl;
}

int countSpace(const string& str) {
    int count = 0;
    for (char i : str) {
        if (isspace(i)) count++;
    }
    return count;
}