#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;

struct Apple {
    string name;
    double price;
    double weight;
    double average_price;
};

int main(int argc, char* argv[]) {
    string line;
    Apple result;
    result.average_price = 0;
    ifstream read_file;
    read_file.open(argv[1]);

    if (read_file.is_open()) {
        while (getline(read_file, line)) {
            stringstream ss;
            ss << line;
            string name;
            double price, weight;
            ss >> name >> price >> weight;

            if (result.average_price == 0 || result.average_price > price / weight) {
                result.average_price = price / weight;
                result.name = name;
                result.price = price;
                result.weight = weight;
            }
        }

    }
    else cout << "NOT OPEN!" << endl;
    cout << setprecision(2) << fixed;
    cout << result.name << " " << result.price << " " << result.weight << endl;


}