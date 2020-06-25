class anInt{
    // a private member is visible only to other members of this class
   int v; // data elements

public:
    // visible to anyone who sees the class
    // not just to other members of this class
    // member functions / methods declarations
   int getValue();
   void setValue(int v); // MODIFIES: this (this object)
   // EFFECTS: set the current value equal to arg
};

// the definition of member functions are put in the .cpp