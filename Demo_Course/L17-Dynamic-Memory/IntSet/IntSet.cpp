#include "IntSet.h"
#include <iostream>

using namespace std;
// When creating a dynamic array, it stores the size of array along with the array
// a pointer to the beginning of the array is returned (which is pointing behind the size)
IntSet::IntSet(int size): elts(new int[size]),
    sizeElts(size), numElts(0){ // initialization syntax
}

IntSet::~IntSet(){
    delete[] elts; // delete [] will look before (for the size) to see how many elements to return to the heap
}

int IntSet::indexOf(int v){
    for (int i = 0; i < numElts; i++){
        if (elts[i] == v)
            return i;
    }
    return sizeElts;
}

int IntSet::size(){
  return numElts;
}

bool IntSet::query(int v){
  return (indexOf(v) != sizeElts);
}

void IntSet::insert(int v){
    if (indexOf(v) == sizeElts){
        if (numElts == sizeElts) 
            throw sizeElts; 
        elts[numElts++] = v;
    }
}

void IntSet::remove(int v){
    int victim = indexOf(v);
    if (victim != sizeElts){
        elts[victim] = elts[numElts-1];
        numElts--;
    }
}

void IntSet::print(){
    for (int i = 0; i < numElts; i++){
        cout << elts[i] << " " << flush;
    }
    cout << endl;
}
