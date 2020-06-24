#include <iostream>
#include <fstream>

using namespace std;

void process_line(const string &line) {
    int i, j, author_count = 0;
    string title, conference, year, temp;
    string surname[10000];
    string first_name[10000];
    temp = "";

    // Start to read title until '-'
    for (i = 0; i < (int)line.length(); i++) {
        temp += line[i];
        if (line[i + 1] == '-') {
            title = temp;
            break;
        }
    }


    i += 3;
    temp = "";
    // Start to read authors until '-'
    for (; i < (int)line.length(); i++) {
        temp += line[i];
        if (line[i + 1] == ' ') {
            if (temp == "-") break;
            if (temp[temp.length() - 1] == ',') {
                surname[author_count] = temp;
                temp = "";
            } else if (temp[temp.length() - 1] == ';' || line[i + 2] == '-') {
                first_name[author_count] = temp;
                temp = "";
                author_count++;
            }
            i++;
        }
    }


    i += 2;
    temp = "";

    // Read year
    year = "";
    for (j = (int)line.length() - 1; j >= i; j--) {
        if (line[j] == ' ') break;
        year = line[j] + year;
    }

    // Read conference
    conference = "";
    for (; i < j; i++) {
        conference += line[i];
    }

    // Start output
    for (i = 0; i < author_count; i++) {
        if (i != 0) cout << " and ";
        cout << first_name[i][0] << ". ";
        cout << surname[i].substr(0, surname[i].length() - 1);
    }
    cout << "; ";
    cout << title;
    cout << "(" << year << "); ";
    cout << conference << endl;
}

int main(int argc, char *argv[]) {
    string line, temp;
    ifstream file(argv[1]);
    while (getline(file, line)) {
        // read in the file line by line
        if (line.length() == 0) continue; // for empty line, continue
        process_line(line); // process every line
    }
    file.close();
    return 0;
}