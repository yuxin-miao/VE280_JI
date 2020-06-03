#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
    bool help = false; bool add = false; bool small = false; bool verbose = false;
    // denote whether this option exists
    int num = 0;
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg.find("help") != string::npos) help = true;
        else if (arg.find("add") != string::npos) add = true;
        else if (arg.find("small") != string::npos) {
            small = true;
            i++;
            num = atoi(argv[i]);
        }
        else if (arg.find("verbose") != string::npos) verbose = true;
    }

    int size = 0;
    cin >> size;
    vector<int> vec(size);
    int temp;
    for (int i = 0; i < size; i++) {
        cin >> temp;
        vec[i] = temp;
    }

    if (help) {
        cout << "Hey, I love Integers." << endl;
        return 0;
    }

    if (!add & !small) {
        cout << "No work to do!" << endl;
        return 0;
    }



    if (add & !verbose) cout << accumulate(vec.begin(), vec.end(), 0)  << endl;
    else if (add & verbose) {
        cout << "This is add operation." << endl;
        cout << accumulate(vec.begin(), vec.end(), 0)  << endl;
    }

    if (small & !verbose) cout << *min_element(vec.begin(), vec.end()) + num << endl;
    else if (small & verbose) {
        cout << "This is small operation." << endl;
        cout << *min_element(vec.begin(), vec.end()) + num << endl;
    }
    return 0;
}
