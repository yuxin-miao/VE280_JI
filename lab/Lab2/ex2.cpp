/*
 * Lab2 Ex2 VE280 20SU
 * Created by: Yiqing Fan
 * Last update: May 25, 2020
 */

#include <cstdlib>
#include <iostream>

using namespace std;

typedef struct {
    // TODO: complete struct
    char name[18];
    int Chinese_score;
    int Math_score;
    int English_score;
} Student;

int compare(const void* p1, const void* p2) {
    // TODO: complete compare function for qsort()
    const Student* l = (Student*)p1;
    const Student* r = (Student*)p2;
    int mark1 = l->English_score + l->Math_score + l->Chinese_score;
    int mark2 = r->English_score + r->Math_score + r->Chinese_score;
    return mark2 - mark1;
}

int main() {
    // TODO: read input
    int num;
    cin >> num;
    Student stud[12];
    for (int i = 0; i < num; i++) {
        cin >> stud[i].name >> stud[i].Chinese_score >> stud[i].Math_score >> stud[i].English_score;

    }

    // TODO: sort array with qsort()
    qsort((void*)&stud, num, sizeof(stud[0]), compare);
    // TODO: print result
    for (int i = 0; i < num; i++) {
        cout << stud[i].name << " " << stud[i].Chinese_score << " " << stud[i].Math_score << " " << stud[i].English_score << endl;
    }
    return 0;
}
