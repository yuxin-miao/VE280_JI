#include <iostream>
#include <map>
using namespace std;

int main(){
    pair<string, int> count("blue", 2);
    map<string, int> word_count;
    word_count.insert(count);
    map<string, int>::iterator it = word_count.begin();
    cout << *it->first << endl; // Dereference a map iterator yields a pair (first member: const key, second member: value)
    // *it.first = "new key"; // error, const member could not be changed
    *it->second = 9;
    /** Subscript a map**/
    // not same as subscripting a vector (dereference a vector iterator)
    // not dereference a map iterator, but will create the key if not existed

    word_count["Anna"] = 1; // it will first search for key "Anna", if in the map, change the value to 1
    // if not in the map, insert key = "Anna", value is initialized as 0, then changed to value 1

    string word;
    while(cin >> word) {
        ++word_count[word];
    }
    /** Map insert**/
    word_count.insert(make_pair(word, 10)); // returns a pair of (map iterator, bool)
    // bool indicates whether key is in the map

    while (cin >> word) {
        pair<map<string, int>::iterator, bool> ret = word_count.insert(make_pair(word, 1));
        if (!ret.second) // already exist
            ++ret.first->second; // increment count
    }

    /** Map find**/
    int occur = 0;
    map<string, int>::iterator it = word_count.find("Anna");
    if (it != word_count.end())
        occur = it->second;
    cout << occur << endl;
    word_count.erase(it); // using iterator, it should not be map.end()
    bool exist = word_count.erase("Anna"); // using key, no key, nothing happen exist=0

    for(it = word_count.begin(); it!=word_count.end(); it++) { // default: alphabetical orders
        cout << it->first << " occurs " << it->second << " times" << endl;
    }
    return 0;
}
