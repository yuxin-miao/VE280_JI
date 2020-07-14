#include "binaryTree.h"
#include "huffmanTree.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;
vector<char> read_file(const string& filename);
// EFFECTS: return a vector store the content in the filename
bool compare(Node* left, Node* right);
// EFFECTS: compare function for sort based on the frequency and ASCII
void find_root(vector<Node*> &arr);
// EFFECTS: modify arr until only contains the root node
void encode(const HuffmanTree& HTree, const vector<char>& content);
// EFFECTS: output the binary code based on the HTree

int main(int argc, char *argv[]) {
    vector<char> content;
    vector<int> freq; // used to store the character's frequency
    vector<char> character; // used to store every unique character
    /**FILE READ**/
    if (argc == 3) content = read_file(argv[2]);
    else if (argc == 2) content = read_file(argv[1]);
    /**COUNT FREQUENCY**/
    for (auto ptr = content.begin(); ptr < content.end(); ptr++) {
        if (find(content.begin(), ptr, *ptr) == ptr) {// this char do not be counted before
            freq.push_back(count(content.begin(), content.end(), *ptr));
            character.push_back(*ptr);
        }
    }
    /**CREATE NODES**/
    vector<Node*> arr;
    for (int i = 0; i < (int)character.size(); i++) {
        if (character[i] == '\n') { Node* temp = new Node("\n", freq[i]); arr.push_back(temp);}
        else if (character[i] == ' ') { Node* temp = new Node(" ", freq[i]); arr.push_back(temp);}
        else {
            stringstream convert;
            convert << character[i];
            string str;
            convert >> str;
            Node* temp = new Node(str, freq[i]);
            arr.push_back(temp);}
    }
    find_root(arr);
    HuffmanTree HTree(arr[0]);
    if (argc == 3) HTree.printTree();
    if (argc == 2) encode(HTree, content);
    return 0;
}

vector<char> read_file(const string& filename) {  // Step1
    vector<char> content;
    ifstream readCompress;
    string line;
    readCompress.open(filename);
    if (readCompress.is_open()) {
        while (getline(readCompress, line)) { // find all end of line
            for (char & i : line)
                content.push_back(i);
            content.push_back('\n'); // end of line will be discarded with getline
        }
        readCompress.close();
    }
    else cout << "Failed to open file!" << endl;
    return content;
}

bool compare(Node* left, Node* right) {
    if (left->getnum() < right->getnum()) return true;
    else if (left->getnum() > right->getnum()) return false;
    else return left->getstr() < right->getstr();
}

void find_root(vector<Node*> &arr) {
    sort(arr.begin(), arr.end(), compare);
    if (arr.size() > 1) { // when more than one node exist
        Node* parent = Node::mergeNodes(arr[1], arr[0]);
        arr.erase(arr.begin());
        arr.erase(arr.begin());
        arr.push_back(parent);
        find_root(arr);
    }
}

void encode(const HuffmanTree& HTree, const vector<char>& content) {
    for (char i : content) {
        if (i == ' ') cout << HTree.findPath(" ");
        else if (i == '\n') cout << HTree.findPath("\n");
        else {
            stringstream convert;
            string s;
            convert << i;
            convert >> s;
            cout << HTree.findPath(s);
        }
        cout << " ";
    }
}