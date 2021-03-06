#include "IntSet.h"
#include <iostream>

using namespace std;

IntSet::IntSet(): numElts(0){
} // initialization syntax
/* Generally
Class_T::Class_T(): anInt(0),
    aDouble(1.2),
    aString("Yes"){
}

 As the order they appeared in the definition
*/

int IntSet::indexOf(int v) const{
    for (int i = 0; i < numElts; i++){
        if (elts[i] == v) return i;
    }
    return MAXELTS;
}

int IntSet::size() const{
  return numElts;
}

bool IntSet::query(int v) const{
  return (indexOf(v) != MAXELTS);
}

void IntSet::insert(int v){
    if (indexOf(v) == MAXELTS){
        if (numElts == MAXELTS) throw MAXELTS; 
        elts[numElts++] = v;
    }
}
// if unordered then could directly move to hole
void IntSet::remove(int v){
    int victim = indexOf(v);
    if (victim != MAXELTS){
        elts[victim] = elts[numElts-1];
        numElts--;
    }
}

void IntSet::print() const{
    for (int i = 0; i < numElts; i++){
        cout << elts[i] << " " << flush;
    }
    cout << endl;
}
