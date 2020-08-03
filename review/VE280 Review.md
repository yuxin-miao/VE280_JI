# VE280 Review

## ADT: Abstract Data Type



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

