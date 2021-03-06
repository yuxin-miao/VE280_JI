#ifndef INTSET_H
#define INTSET_H

const int MAXELTS = 1000000;

class IntSet{
//protected: // Needed to make MaxIntSet work
    // OVERVIEW: a mutable set of integers, |set| <= MAXELTS
    // set: a collection of zero or more integers, with no duplicates
    // mutable: can insert or remove values from the set

    int       elts[MAXELTS]; // the representation of sets
    int       numElts;  // representation invariant or rep invariant
    // (must obey both immediately before / after any method' execution)


    int       indexOf(int v) const; // (expose details about the concrete representation, so private)
    // EFFECTS: returns the index of v if it exists in the
    //          array, MAXELTS otherwise.

public:
    IntSet(); // (guaranteed to be the first functino called immediately after an object is created )
    // EFFECTS: default constructor. Creates an empty IntSet.
    void insert(int v);
    // MODIFIES: this
    // EFFECTS: this = this + {v} if room, 
    //          throws int MAXELTS otherwise.
    void remove(int v);
    // MODIFIES: this
    // EFFECTS: this = this - {v} if v is in this
    bool query(int v) const; // (this is now a pointer to a const instance, could not be modified)
    // EFFECTS: returns true if v is in this, false otherwise.
    int  size() const;
    // EFFECTS: returns |this|. ()
    void print() const;
    // MODIFIES: cout
    // EFFECTS: print out the integers contained in the set in
    //          sequence.
};
// Each member function of a class has an extra, implicit parameter 'this'
// 'this' is a pointer to the current instance on which the function is invoked
#endif
