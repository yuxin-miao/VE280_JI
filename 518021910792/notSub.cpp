
#include <iostream>
#include "dict.h"
using namespace std;

int main(){
    Dict<string, int> dict;
    dict.insert("a",1);
    dict.insert("b",2);
    dict.insert("c",3);

    cout << *dict.find("b") << endl;
    cout << dict.size() << endl;
    cout << dict.size() << endl;

}
