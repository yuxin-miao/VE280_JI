#include <iostream>
#include <map>
using namespace std;
void print_word_counts(const std::vector<std::string> &words);
// EFFECTS: print how many time a 'word' in words occurs
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

void print_word_counts(const std::vector<std::string> &words) {
    std::map<std::string, int> word_counts;
    // Each time a word is seen, add 1 to its entry in the map
    for (const auto &word : words) {
        word_counts[word] += 1;
    }
// Print out the results by iterating through the map.
    for (const auto &key_value : word_counts) { // key-value pairs
        const auto &word = key_value.first;
        const auto &count = key_value.second;
        cout << word << "occurred " << count << " times." << endl;
    }
// using range-based loop to iterate over both the vector and the map, declaring a type-deduced reference to each element.
// A reference avoids making a copy, which is nontrivial for strings.
// The iteration over the map produces key-value pairs(std::pair<std::string, int>)
}