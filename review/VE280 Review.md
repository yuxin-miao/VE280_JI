# VE280 Review

```bash
tar zxvf p5.tar // 解包p5.tar到当前mu lu
tar -cf new.tar *.cpp *.h *.txt // 打包当前目录下所有.h .cpp .txt文件到 new.tar
tar -cf try.tar final // 打包final文件夹为try.tar 
tar -xzf XYZ.tgz // to decompress and the command 
tar -czf XYZ.tgz XYZ // to compress.
```

```Cmake
cmake_minimum_required(VERSION 3.16)
project(final)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic")
add_executable(final review/main.cpp)
add_executable(Q1 Q1/q1.cpp)
add_executable(final2 review/memory.cpp)
add_executable(final3 review/deepCopy.cpp)
```



## ADT: Abstract Data Type

An ADT provides an **abstract** **description** of **values** and **operations**

- information hiding 
- encapsulation 

member function call: The other members of the object are also visible to the function members!

**representation invariants / rep invariants**: This invariant is a rule that the representation must obey both **immediately before** and **immediately after** any method's execution. eg. rep invariants for the following code is 

- Represent a set of size N as an **unordered** array of integers with no duplicates, stored in the first N slots of the array.
- int numElts: maintains the number of elements currently in the array.

```c++
const int MAXELTS = 100;
class IntSet { /* Implement with fixed size array */
    // OVERVIEW: a mutable set of integers, |set| <= MAXELTS
      int elts[100]; 
  		int numElts;
  		int indexOf(int v) const; // RME
  public:
  	IntSet()::numElts(0); 
    void insert(int v); // RME
    void remove(int v); // RME
    bool query(int v); // RME
    int  size(); // RME
};
```

When `remove`, the representation invariants violated is 

- The requirement that the first N values occupy first N slots of the array
- numElts does not maintain the number of elements currently in the array 

Invariants can also be coded, to check the **sanity of the structure.** Eg. for sorted IntSet()

```c++
bool strictSorted(int a[], int size)
// REQUIRES: a has size elements
// EFFECTS: returns true if a is sorted with no duplicates
bool repOK(){ // as a private method 
      // EFFECTS: returns true if the rep. invariants hold
    return strictSorted(elts, numElts);
}
// add in the class member function when modifies this 
assert(repOK());
```

**Initialization syntax** *FIRST*: The initialization list initializes variables; *SECOND:* **The body of the constructor executes**

const member function will not change `this`, as `this` is a pointer to const instance. Only can call other member function that are const. 

## Subtype

S is a subtype of T, "S <: T", T is a supertype of S. When type T is expected, an object of type S can be supplied without changing the correctness of the original computation. 

**Substituion Principle**

- The new method must do everything the old method did, but it is allowed to do more as well
- It must require no more of the caller than the old method did, but it can require less.

```c++
void add(istream &source) {
	double n1, n2;
	source >> n1 >> n2;
    cout << n1 + n2;
}
int main(){
    ifstream inFile;
    inFile.open("test.in")
		add(inFile); // no type conversion, it calls function add of ifstream
    inFile.close();
}
```

**Create a subtype**

- add one or more operations 

- strengthen the postcondition of one or more operations 

  PostCondition: 

  + The EFFECTS clause: promising <u>everything you used to</u>, plus extra.
  +  its return type

- weaken the preconditions of one or more operations 

  + The REQUIRES clause: could not only accept all previous conditions, but accept more (that would not be accepted before)
  + its argument type

### Inheritance (subclassing)

it is possible to create **subclasses** that are **NOT** **subtypes** and don't follow the substitution principle. 

```c++
class bar : /* access */ foo { // derived class bar, derived from foo
	... // bar is a foo, possibly with extra space / with new or redifined member function
};
```

When a class (called derived, child class or subclass) inherits from another class (base, parent class, or superclass), the derived class is automatically populated with almost everything from the base class. 

- This includes member variables, functions, types, and even static members. 
- The only thing that does not come along is friendship-ness.

**Access specifier** - default: `private`

1. `access` is `private` method: public / private / protected member objects are all become `private`

   neither the derived class nor the outside could access any of them

2. `access` is `protected` method: `private` -> `private`;` protected / public`:  `protected`

3. `access` is `public` method: `private` -> `private`;` protected / public`:  `public`

**Constructors and destructors**

constructor will call from parent to son, destructor will call from son to parent. All will be called. 

```c++
class Parent {
public:
    Parent() { cout << "Parent::Constructor\n"; }
    virtual ~Parent() { cout << "Parent::Destructor\n"; }
};

class Child : public Parent {
public:
    Child() : Parent() { cout << "Child::Constructor\n"; }
    ~Child() override { cout << "Child::Destructor\n"; }
};

class GrandChild : public Child {
public:
    GrandChild() : Child() { cout << "GrandChild::Constructor\n"; }
    ~GrandChild() override { cout << "GrandChild::Destructor\n"; }
};

int main() {
    GrandChild gc;
}
```

output: 

```bash
Parent::Constructor
Child::Constructor
GrandChild::Constructor
GrandChild::Destructor
Child::Destructor
Parent::Destructor
```

### Inheritance & Subtyping

Inheritance is neither a sufficient nor a necessary condition of subtyping relation. Yet, it is the only subtyping method supported by C++ (without a hack) in runtime. 

```c++
// Creat subtype by copy and paste
class A {
public:
    void quak(){} 
};
class B { // B :< A
public:
    void quak(){} 
    void nop(){}
};

// Private inheritance prevents D to be a subtype of A, only a subclass
class C {
    int priv;
};
class D : C {};
```

### Keyword `Virtual`

Consider the apparent type and actual type:

- Apparent Type: Apparent type is the type annotated by the type system. It is the static type information. It is the you remarked to the compiler.
- Actual Type: It is the data type of the actual instance. It is the data type that describes what exactly is in the memory.

"someone might override my implementation: always check at run-time to see which version to call.”

## Interface

**Interface:** the contract for using this type

Base class: interface-only, **abstract base class or virtual base clss**

- Declare each method as a virtual function
- “Assign” a zero to each of these virtual function

```c++
// in .h
class IntSet { // a mutable set of integers
   public: // could not provide constructor
   // pure virtual functions, as a set of function pointers 
     virtual void insert(int v) = 0; // this + {v}
     virtual void remove(int v) = 0; // this – {v}
     virtual bool query(int v) = 0; // does v exist in this?
     virtual int  size() = 0; // return |this|
  };
IntSet *getIntSet(); // for an access function
	  // EFFECTS: returns a pointer to the IntSet
```

- No instance of an abstract class could be created, no implementation provided 
- The derived class need to implement the constructor

```c++
// in .cpp
static IntSetImpl impl;
Intset* getIntSet() {
	return& impl;
}
```

So the user could use `IntSet *s = getIntSet();`

- Derived class pointer compatible to base class.
- Derived class instance compatible to base class (possibly `const`) reference.
- You can assign a derived class object to a base class object.

The reverse is generally false. E.g. assigning a base class pointer to derived class pointers needs special casting.

```c++
class ISummable { 
public:
	/* Add item x to itself */
	virtual void add(ISummable& x) = 0; 
};
// This class models the objects that are summable. 
// Based on this modeling, we could write the following very general function: 
void sum(ISummable elem[],size_t size, ISummable& rst) {
	for (int i = 0; i < size; ++i) 
		rst.add(elem[i]); 
}
// This will work for anything that is Summable object. 
// When a class derives from an interface and provides an implementation, 
// we say it implements the interface.
```



### Casting

**dynamic_cast**

In C++, dynamic casting is primarily used to safely downcast like casting a base class pointer (or reference) to a derived class pointer (or reference). It can also be used for upcasting, i.e. casting a derived class pointer (or reference) to a base class pointer (or reference).

* To use `dynamic_cast<new_type>(ptr)`, the base class should contain at least one virtual function.
* Dynamic casting checks consistency at runtime; hence, it is slower than static cast

```c++
class Shape{
    string s_name;
public:
    Shape(string name): s_name(name){}
    virtual void get_info(){ cout<<s_name<<endl; }
};

class Square : public Shape{
    int side;
public:
    Square(string S_name, int value) : Shape(S_name), side(value){}
    void get_info(){ cout<<"Area of the square is: "<<side * side<<endl; }
};

class Rectangle : public Shape{
    int length;
    int width;
public:
    Rectangle(string S_name, int len, int wid) : Shape(S_name), length(len), width(wid){}
    void get_info() override { cout<<"Area of the rectangle is: "<<length * width<<endl; }
};

Shape* create_square(string S_name, int value){
    return new Square(S_name, value);
}

Rectangle* create_rectangle(string S_name, int len, int wid){
    return new Rectangle(S_name, len, wid);
}

int main() {
    // quad is the pointer to the parent class, 
    // it needs to be casted to be used to
    // access the method of the child class.
    Shape *quad = create_square("Quadliteral", 4);
    // Trying to downcast the parent class pointer to
    // the child class pointer.
    Square* sq = dynamic_cast<Square*>(quad);
    // dynamic_cast returns returns null if the type
    // to be casted into is a pointer and the cast
    // is unsuccessful.
    if(sq){
        sq -> get_info();
    }
    Rectangle *rect = create_rectangle("Quadliteral", 4, 5);
    
    // An example of a valid upcasting
    Shape* quad1 = dynamic_cast<Shape*>(rect);
 
    // An example of invalid downcasting
    Square* sq1 = dynamic_cast<Square*>(quad1);
    if(!sq1){
        cout<<"Invalid casting."<<endl;
    }
}

```

## Dynamic Memory

**Static**

- Global: have the same lifie time of the program. Reserved the space before the program begins, at complie time. 
-  local variables: defined whitin a block, including **function arguments**. Reserved the space at run time, known size to the compiler.

**Dynamic** complier don’t no the size and how long it lives. 

### Memory Management

Each running program has its own memory layout, separated from other programs. The layout consists of a lot of segments, including:

- `stack`: stores local variables
- `heap`: dynamic memory for programmer to allocate
- `data`: stores global variables, separated into initialized and uninitialized
- `text`: stores the code being executed

In order to pinpoint each memory location in a program’s memory, we assign each byte of memory an “address”. The addresses go from 0 all the way to the largest possible address, depending on the machine. As the figure below, the `text`, `data`, and `stack` segments have low address numbers, while the `stack` memory has higher addresses.

![img](/Users/yuxinmiao/CLionProjects/Clion_2020Summer/VE280/review/imagesForReview/memory_layout.png)

### `new` and `delete`

new and new[] does the following:

* Allocates space in heap (for one or a number of objects).
* Constructs object in-place (including, but not limited to ctor).
* Returns the “first” address.

```c++
Type* obj0 = new Type; // Default construction
Type* obj1 = new Type(); // Default construction
Type* obj2 = new Type(arg1, arg2);
Type* objA0 = new Type[size]; // Default cons each elt
Type* objA1 = new Type[size](); // Same as obj A0
```

`delete` and `delete[]` releases the objects allocated from `new` and `new[]` respectively. They does the following:

* Destroy the object (each object in the array) being released (by calling the destructor of the object).
* Returns the memory to the system. 

```c++
int num = 100;
int *array = new int[num];
delete [] array;
```

### Destructor

The destructors for any ADTs declared locally within a block of code are **called automatically when the block ends**.

```c++
{
	IntSet ip = IntSet(50);
	...		
} // ip will be destroyed by calling its destructor
```

Destructor of ADT will also be **called when using `delete`**. A effective destructors should:

* Be named as `~ClassName`
* Takes no argument and returns nothing *(not even void)*
* If one expect the class to be inherited the **destructor should be declared as `virtual`** (or double delete may happen)
* Release resource allocated only in this class, do not release base class resources!!!

Consider that in lab8:

```c++
Node::~Node() {
  	// EFFECTS: destroy the whole tree rooted at sub
    // MODIFIES: this
    for(int i = 0; i < this->child_num; i++) { delete(children[i]); }
    delete[] children;
}
```

**double deletion**

```c++ 
class Base {
protected:
    int *p;
public:
    Base() : p(new int(10)) {}
    virtual ~Base() {delete p;}
};

class Derived : public Base {
    int *q;
public:
    Derived() : Base(), q(new int(20)) {}
    virtual ~Derived() override {delete p; delete q;}
};

/* A */
void main() {
	Base* ptrA = new Derived; // double deletion occurs, destructor of both base and derived will be called 
	delete ptrA;
}

/* B */
void main() {
	Derived* ptrB = new Derived; // double deletion occurs, destructor of both base and derived will be called 
	delete ptrB;
}

/* To correct */
class Derived : public Base { // in the derived class, it should not delete ANYTHING in the base class
    int *q;
public:
    Derived() : Base(), q(new int(20)) {}
    virtual ~Derived() override {delete q;}
};
```

## Deep Copy

**Shallow copy**

the default copy constructor and default assignment operators it provides use a copying method known as a member-wise copy, also known as a *shallow copy*. This works well if the fields are values, but may not be what you want for fields that point to dynamically allocated memory. The pointer will be copied. but the memory it points to will not be copied: the field in both the original object and the copy will then point to the same dynamically allocated memory, this causes problem at erasure, causing dangling pointers.

**Deep copy**

ecall binary tree and in-order traversal. We define that a good tree is a binary tree with ascending in-order traversal. How to deep copy a template good tree provided interface:

```c++
template <class T> 
class GoodTree { 
		T *op; 
		GoodTree *left; 
		GoodTree *right; 
public:
  	void removeAll(); 
  	// EFFECTS: remove all things of "this" 
  	void insert(T *op); 
  	// REQUIRES: T type has a linear order "<" 
  	// EFFECTS: insert op into "this" with the correct location
  	//					Assume no duplicate op.
};
template <class T> 
void GoodTree<T>::copy_helper(const GoodTree<T> *t) { 
  	if (t == nullptr) 
      	return; 
  	T *tmp = new(t->op); 
  	insert(tmp); 
  	copy_helper(t->left); 
  	copy_helper(t->right); 
}

template <class T> 
void GoodTree<T>::copyAll(const GoodTree<T> &t) {
		removeAll();
  	copy_helper(&t); 
}
```

You may use `removeAll` and `insert` in your `copyAll` method.

## Dynamic Resizing

## Linked List

## Template & Container

### Container of pointers: 1 invariant & 3 rules

- *At-most-once invariant*: any object can be linked to at most one container at any time through pointer.

1. *Existence*: An object must be dynamically allocated before a pointer to it is inserted.
2. *Ownership*: Once a pointer to an object is inserted, that object becomes the property of the container. No one else may use or modify it in any way.
3. *Conservation*: When a pointer is removed from a container, either the pointer must be inserted into some container, or its referent must be deleted.

## Operator Overloading

1. ###### Overloaded operator has a return type and a parameter list

   Keyword - operator; followed by the symbol

   ```C++
   // nonmember function & binary operator
   A operator+ (const A&left, const A&right) // return left + right
     
   // class member function & binary operator
   A A::operator+(const A&left, const A&right) // return *this + right
   // class member function & unary operator
   A &A::operator+=(const A&right) // return *this + right, modifies this 
   ```

2. ###### friendship

   friend declared inside the class, but the friend object or friend class are not the member of that class.

   Friend function: expose the private state of one class to another function (and only that function) explicitly.

   Friend class:  expose the private state of one class to another class (and only that class) explicitly.

   ```c++
   class foo {
       friend class bar; // not a member of foo
       friend void baz(); // not a member of foo
       int f; // private member 
   };
   class bar { ... };  // objects of class bar can access private member f of foo
   void baz() { ... } 
   ```

   

   ```c++
   class Complex {
     // OVERVIEW: a complex number class
     double real;
     double imag;
   public:
     Complex(double r=0, double i=0); // Constructor
     Complex &operator += (const Complex &o);
   // MODIFIES: this
   // EFFECTS: adds this complex number with the // complex number o and return a reference
   // to the current object.
     friend Complex operator+(const Complex &o1,const Complex &o2);
   };
   
   Complex operator + (const Complex &o1, const Complex &o2) {
   	Complex rst;
   	rst.real = o1.real + o2.real; rst.imag = o1.imag + o2.imag; 
     return rst;
   }
   ```

3. ###### Example for different operators

   **opeartor[]** - binary operator 

   *const version and nonconst versio* needed. call non-const version first

   ```c++
   const int &IntSet::operator[](int i) const { 
     // with some const object or whithin some const member function
     if(i >= 0 && i < numElts) 
       return elts[i]; 
     else throw -1;
   }
   
   int &IntSet::operator[](int i) { 
     // when assign an element through the subscript eg. is[5]=2
     if(i >= 0 && i < numElts) 
       return elts[i]; 
     else throw -1;
   }
   ```

   **operator<< && operator >>**  - binary

   *returns a reference its ostream parameter* - so could chained together 

   must be *nonmember* function -first operand: ostream type, not of the class type

   ```c++
   ostream &operator<<(ostream &os, const IntSet &is){ 
     // not return const parameter - may be changed 
     for(int i = 0; i < is.size(); i++)
       os << is[i] << " ";
     return os;
   }
   istream &operator>>(istream &is, foo &obj){ 
     ...
       return is; 
   }
   ```

## Linear List

A collection of zero or more integers; **duplicates possible.**  Insertion and removal **by position** (remember to check the boundary condition)

```c++ 
   void insert(int i, int v) // if 0 <= i <= N 
   // (N is the size of the list), insert v at position i
   // otherwise, throws BoundsError exception.

```

## Stack

**LIFO** access: last in, first out (restriction from linear list) 一叠盘子 insert at first, remove from first

Through *single-ended, singly-linked list*, top be the first node 

```
size(): number of elements in the stack.
isEmpty(): checks if stack has no elements.
push(Object o): add object o to the top of stack.
pop(): remove the top object if stack is not empty; otherwise, throw stackEmpty.
Object &top(): return a reference to the top element.
```

## Queue

**FIFO** access: first in, first out 一个队列 insert at last, remove from the front

Through *double-ended, singly-linked list* or *circular array*

```
size(): number of elements in the queue.
isEmpty(): check if queue has no elements.
enqueue(Object o): add object o to the rear of the queue.
dequeue(): remove the front object of the queue if not empty; otherwise, throw queueEmpty.
Object &front(): return a reference to the front element of the queue.
Object &rear(): return a reference to the rear element of the queue.
```

*Circular array*

```c++
// If front(or rear) == MAXSIZE-1, the statement sets front(or rear) to 0.
front = (front+1) % MAXSIZE;
rear = (rear+1) % MAXSIZE;

// need to distinguish between the full array and empty array
// add size 
```

## Deque

Double-ended queue, A combination of stack and queue. Items can be inserted and removed from **both ends** of the list.

Through *Double-ended doubly-linked list* or *Circular array*

## STL 

defines powerful, template-based, reusable components that implements common data structures and algorithms

Three components:

+ containers 

+ iterators

  pointers to the elements of containers.

  ```c++
  vector<int>::iterator it;
  // could not change the value pointed by the const_iterator through const_iterator
  vector<string>::const_iterator itConst; 
  *itConst = "Wrong operation" 
  ```

+ algorithms

Common operations for all three different types 

Common operations

```c++
C<T> c; // creates an empty container
C<T> c1(c2); // copies elements from c2 into c1, c2 must be the same type as c1
C<T> c(b, e); // b and e are iterators denoting a sequence. Copy elements from the sequence into c
begin(), end(), size(), empty(), clear(), =
```

### Sequential Container

Elements' order controlled by the programmer, independent of the value of the elements 

#### vector

- based on array, collection of a single type objects 

- Supports fast random access.

- Fast insert/delete at front or back.

- Iterator

  Iterator Arithmetic ``iter+n, iter-n``

  Relational Operation on Iterator `>, >=, <, <=` Compare the postion, ahead means smaller 

```c++
vector<int> v;
vector<int>::iterator it = v.begin(); 
// v.end() : not denote an actual element, positioning to one-past-the-end
vector<int>::iterator mid = v.begin() + v.size()/2;

// sizeof(int) in the example is the sizeof(type name); sizeof(a) is the sizeof(obj)
// sizeof an array is equivalent to taking the sizeof the element type times the number of elements in the array
int a[] = {1, 2, 3, 4};
unsigned int sz = sizeof(a)/sizeof(int);
vector<int> vi(a, a+sz);
```

#### deque 

- based on array
- Supports fast random access.
- Fast insert/delete at front or back.

#### List 

- based on a doubly-linked list
- Fast insert/delete at any point in the list.

no Iterator Arithmetic 

### Associative Container

Elements' order based on value, irrelevant to their insertion order

#### map / associative array

Elements in map are ordered by keys, 

- Subscripting a vector = dereferencing a vector iterator 

  Subscripting a map ≠ dereferencing a map iterator (if not exist this key, new key will be  created)

### Container Adapters

container adaptor takes an existing container type and makes it act like a different abstract data type

#### Stack

- sequential container adaptors
- use a sequential container ``c`` to initialize, `c` must be deque 

#### Queue

- sequential container adaptors
- use a sequential container ``c`` to initialize, `c` must be deque 

## Dictionary

- optimized to quickly **add** **(key, value)** pair and **retrieve** **value** by key.
- one key could only associated to one value in a dictionary

