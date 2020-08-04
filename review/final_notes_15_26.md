# Before Revision

`RTFM` is impolite yet the most educative response. Manual knows better than we do.

![RTFM: Acronym Whose Time Never Came](https://images.squarespace-cdn.com/content/v1/54bcbd06e4b060f2e987ebbe/1459529343746-L8K4Z6PYO3N7H9ZQ5VOR/ke17ZwdGBToddI8pDm48kKZxGWUYFJ6SqUoEs64UrUJZw-zPPgdn4jUwVcJE1ZvWEtT5uBSRWt4vQZAgTJucoTqqXjS3CfNDSuuf31e0tVGMXKC-EUVLq81mAulepnsSPwlw0m8iD4lEEr8_2AGhSmQ6l2WM7tn7mqHTODzkmeM/image-asset.png)

# Lecture 15-16: Classes in C++

## Subtype Polymorphism

Subtype relation is an “IS-A” relationship.

For examples, a Swan **is a** Bird, thus a class Swan is a subtype of class Bird. A bird can fly, can quake and can lay eggs. A swan can also do these. It might do these better, but as far as we are concerned, we don’t care. Bird is the super-type of the Swan.

### Liskov Substitution Principle

If $S$ is a subtype of $T$ or $T$ is a supertype of $S$, written $S <: T$, then for any instance where an object of type $T$ is expected, an object of type $S$ can be supplied without changing the correctness of the original computation.

- Functions written to operate on elements of the supertype can also operate on elements of the subtype. 
- Benefits: code reuse.

An example would be the input streams of c++:

```mermaid
graph TD;
    istream-->iostream;
    istream-->ifstream;
    istream-->istringstream;
```

### Compare: Type Coercion

Consider the following examples.

- Example 1: 

  Can we use an `ifstream` where an `istream` is expected? Is there ant type conversion happening in this piece of code?

  ```c++
  void add(istream &source) {
  	double n1, n2;
  	source >> n1 >> n2;
      cout << n1 + n2;
  }
  
  int main(){
      ifstream inFile;
      inFile.open("test.in")
  	add(inFile);
      inFile.close();
  }
  ```

- Example 2: Coercion.

  Can we use an `int` where a `double` is expected? Is there ant type conversion happening in this piece of code?

  ```c++
  void add(double n1, double n2) {
      cout << n1 + n2;
  }
  
  int main(){
      int n1 = 1;
      int n2 = 2;
  	add(n1, n2);
  }
  ```

### Creating Subtypes

In an Abstract Data Type, there are three ways to create a subtype from a supertype:

1. Add operations.
2. Strengthen the postconditions

- Postconditions include:
  - The EFFECTS clause
  - The return type

1. Weaken the preconditions

- Preconditions include:
  - The REQUIRES clause
  - The argument types



## Inheritance Mechanism

When a class (called derived, child class or subclass) inherits from another class (base, parent class, or superclass), the derived class is automatically populated with almost everything from the base class. 

- This includes member variables, functions, types, and even static members. 
- The only thing that does not come along is friendship-ness.
- We will specifically discuss the constructors and destructors later.

The basic syntax of inheritance is:

```c++
class Derived : /* access */ Base1, Base2, ... {
private:
	/* Contents of class Derived */
public:
	/* Contents of class Derived */
};
```

### Access Specifier

There are a three choices of access specifiers, namely `private`, `public` and `protected`.

The accessibility of members are as follows:

|      specifier      | private | protected | public |
| :-----------------: | :-----: | :-------: | :----: |
|      **self**       |   Yes   |    Yes    |  Yes   |
| **derived classes** |   No    |    No     |  Yes   |
|    **outsiders**    |   No    |    No     |  Yes   |

When declaring inheritance with access specifiers, the status of member in the derived classes are as follows:

| Inheritance \ Member |   private    | protected |  public   |
| :------------------: | :----------: | :-------: | :-------: |
|     **private**      | inaccessible |  private  |  private  |
|    **protected**     | inaccessible | protected | protected |
|      **public**      | inaccessible | protected |  public   |

When you omit the access specifier, the access specifier is assumed to be `private`, and the inheritance is assumed to be `private ` as well.

An example would be as follows. Which parts of the code does not compile? (Constructors and Destructors are omitted)

```c++
class Base {
    
	friend void friendBase(Base* b);
    
/* A */
private: 
    int priv; 
    void privMethod(){
        priv = 0;
    }
    
/* B */
protected:
    int prot; 
    void protMethod(){
        prot = 0;
    }
    
/* C */
public: 
    int pub; 
    void pubMethod(){
        pub = 0;
    }
    
};

class Derived : public Base {
    
	int derived;
    friend void friendDrived(Derived* d);
    
    /* D */
	void tryPrivDerived() { 
   		priv = 0; 
    	privMethod();
	}
    
    /* E */
    void tryProtDerived() { 
    	prot = 0; 
    	protMethod();
    }
    
    /* F */
	void tryPubDerived() { 
    	pub = 0; 
    	pubMethod();
    }
    
};

class PrivateDerived : Base {};
class Rederived : PrivateDerived {
    /* G */
    void tryPubRederived(){
        pub = 0;
        pubMethod();
    }
};

/* H */
void tryPrivOutside() { 
    Derived d;
    d.priv = 0; 
    d.privMethod(); 
}

/* I */
void tryProtOutside() { 
    Derived d;
    d.prot = 0; 
    d.protMethod(); 
}

/* J */
void tryPubOutside() { 
	Derived d;
    d.pub = 0; 
    d.pubMethod(); 
}

friend void friendBase(Base* b){
    /* K */
    b->priv = 0;
    b->privMethod();
}

friend void friendDrived(Derived* d){
    /* L */
    d->derived = 0;
    d->tryPubDerived();
    
    /* M */
    d->priv = 0;
    d->privMethod();
}
```

### Constructors and Destructors in Inheritance 

What would be the order of constructor and destructor call in a inheritance system? A short answer to remember would be:

![img](https://media.geeksforgeeks.org/wp-content/uploads/order-of-constructor.png)

Consider the following example:

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

Here’s what actually happens when derived is instantiated:

1. Memory for derived is set aside
   - Enough for both the Base and Derived portions, in fact
2. The appropriate Derived constructor is called
3. **The Base object is constructed first using the appropriate Base constructor**. If no base constructor is specified, the default constructor will be used.
4. The initialization list initializes variables
5. **The body of the constructor executes**
6. Control is returned to the caller

Thus the output would be:

```bash
Parent::Constructor
Child::Constructor
GrandChild::Constructor
GrandChild::Destructor
Child::Destructor
Parent::Destructor
```

~~See also the [default](https://en.cppreference.com/w/cpp/language/member_functions#Special_member_functions) keyword for good clang-tidy coding style.~~

~~See also the [explicit]() keyword to avoid unexpected conversion in single-argument constructor.~~

### Inheritance & Subtyping

Inheritance is neither a sufficient nor a necessary condition of subtyping relation. Yet, it is the only subtyping method supported by C++ (without a hack) in runtime. 

We can create a subtype simply by repeating everything.

```c++
class A {
public:
    void quak(){} 
};

class B {
public:
    void quak(){} 
    void nop(){}
};
```

Private inheritance prevents B from being a subtype of A.

```c++
class A {
    int priv;
};

class B : A {};
```

Yet, we will **assume public inheritance** in the rest of discussion.

### Pointer and Reference in Inheritance

From the language perspective, C++ simply trusts the programmer that every subclass is indeed a subtype. We have the following rules.

- Derived class pointer compatible to base class.
- Derived class instance compatible to base class (possibly `const`) reference.
- You can assign a derived class object to a base class object.

The reverse is generally false. E.g. assigning a base class pointer to derived class pointers needs special casting.

An example for the third rule is as follows. What would be the output?

```c++
class Base {
    string str;
public:
    Base() { cout << "base::default\n"; }
    Base(const Base& other) { cout << "base::copy\n"; }
};

class Derived1 : public Base {};

class Derived2 : public Base {
public:
    Derived2() = default;
    Derived2(const Derived2& d2) : Base(d2) { cout << "derived::copy\n"; }
};

int main() {
    cout << "Derived 1: \n";
    Derived1 d1;
    Derived1 d1c(d1);
    
    cout << "Derived 2: \n";
    Derived2 d2;
    Derived2 d2c(d2);
}
```

The output would be:

```bash
Derived 1:
base::default
base::copy
Derived 2:
base::default
base::copy
derived::copy
```

A synthesized copy constructor will do things almost identical to synthesized default constructor.

- Copy construct the base class. See `Derived1`.
- Copy construct every member, if there is any.
- Call the copy constructor of the class.

The case of `Derived2` shows how we do this manually.

Without default constructor (see `Derived3`), since you already provided a constructor, compiler won’t synthesize default constructor for you.

```c++
class Derived3 : public Base {
public:
    Derived3(const Derived3& d3) : Base(d3) { cout << "derived3::copy\n"; }
};

int main() {
    cout << "Derived 3: \n";
    Derived3 d3; // error
    Derived3 d3c(d3);
}
```

This code leads to a compile error.

Without copy constructing the base (see `Derived4`), the compiler will treat it as if the copy constructor is a usual constructor, defaulting constructing the base and all members.

```c++
class Derived4 : public Base {
public:
    Derived4() = default;
    Derived4(const Derived4& d4) { cout << "derived4::copy\n"; }
};

int main() {
    cout << "Derived 4: \n";
    Derived4 d4;
    Derived4 d4c(d4);
}
```

The output would be:

```bash
Derived 4:
base::default
base::default
derived4::copy
```

### `friend` Keyword

We may want to access private member of class instances. You could provide an accessing operator
for each of the member, but often it is not a good idea. One workaround is specifically grant access to the protected members. This can be done by using the `friend` keyword:

```c++
class Bar {
	friend void foo (const MyClass &mc);
}
```

It doesn’t matter where this is marked public or private. 

`friend` can also grant access to classes:

```c++
class Bar {
	friend class Baz; 
}
```

Pay attention that friend is not mutual. If Class A declares Class B as friend. Class B can access Class A’s private member, but the other way around doesn’t work.

### ~~Inheritance and Memory Map~~

~~Skipped. See[Memory Layout of C++ Object in Different Scenarios](http://www.vishalchovatiya.com/memory-layout-of-cpp-object/).~~

### ~~Multiple Inheritance & The Diamond Problem~~

~~Skipped. See [Multiple Inheritance](https://en.wikipedia.org/wiki/Multiple_inheritance).~~



## Virtuousness and Polymorphism

### Problem: Static Binding

Consider the following example.

```c++
class IntSet {
public:
    void insert(int i) { cout << "IntSet\n"; }
};

class SortedIntSet : public IntSet {
public:
    void insert(int i) { cout << "SortedIntSet\n"; }
};

void insert100(IntSet& set) { set.insert(100); }

int main() {
    SortedIntSet set;
    set.insert(10);
    insert100(set);
}
```

Now in `insert100()`, the method `insert()` is called on object set. set is an instance of `IntSet`. In this case, the compiler will choose the function `IntSet::Insert()`. Remember that the compiler have no idea what is actually referenced by set. When it compiles `insert100`, all it knows is that set refer to an object of `IntSet`. It doesn’t care if this object is part of a larger object. In fact, up till this point, when you make a function call in the code, the actual function being called is always know at compile time. The process of binding a function call to the actual definition is static.

The output is thus

```c++
SortedIntSet
IntSet
```

Consider the apparent type and actual type:

- Apparent Type: Apparent type is the type annotated by the type system. It is the static type information. It is the you remarked to the compiler.
- Actual Type: It is the data type of the actual instance. It is the data type that describes what exactly is in the memory.

In our previous example, in function `insert100()`, the apparent type of the variable set is `IntSet`, while what’s in the memory is actually a `SortedIntSet` (The actual type).

### Dynamic Polymorphism

#### `virtual` keyword

What we want is dynamic function binding, the ability to bind a function call based on an object’s actual type, instead of the apparent type. This is done through the virtual keyword. Using the previous example:

```c++
class IntSet {
public:
	virtual void insert(int i) {
        //...
    }
};
```

The above syntax marks insert as a `virtual` function.

The syntax marks insert as a virtual function (method).

Virtual methods are methods replaceable by subclasses. When a method call is made, if the method you are calling is a virtual function (based on the apparent type), the language bind the call according to the actual type. In this way, the function `insert100` achieves dynamic polymorphism, the ability to change its behavior based on the actual type of the argument.

#### `override` keyword

The act of replacing a function is called overriding a base class method. The syntax is as follows.

```c++
void insert(int i) override {
    //...
}
```

`override` cause the compiler to verify if a function is indeed overriding a base class method. If the base class method is not a virtual function, compiler will complain. The keyword is introduced in C++11. It is considered a best practice always mark override whenever possible.

Now, consider the adapted previous example:

```c++
class IntSet {
public:
    virtual void insert(int i) { cout << "IntSet\n"; }
};

class SortedIntSet : public IntSet {
public:
    virtual void insert(int i) override { cout << "SortedIntSet\n"; }
    // Note: It's good coding style to add `virtual` here.
};

void insert100(IntSet& set) { set.insert(100); }

int main() {
    SortedIntSet set;
    set.insert(10);
    insert100(set);
}
```

The output is now:

```
SortedIntSet
SortedIntSet
```

#### ~~`final` keyword~~

~~Skipped. See [final specifier (since C++11)](https://en.cppreference.com/w/cpp/language/final).~~

### ~~Virtual Table~~

~~Skipped.~~

~~Virtual function comes with cost in performance.~~ 

- ~~The cost of one extra layer of indirectness. There exists one more pointer dereference to find the target function. That’s one more memory access.~~
- ~~Cost of unknown call target. Modern processors will “prefetch”, or guess the future instructions and execute them in advance. Since the function call target is unknown, this will not be possible for virtual functions~~
- ~~Cost of unable to inline methods. For simple methods, compiler will try to inline them. Since the binding happens at runtime for virtual methods, this is no longer possible.~~

~~Using the `final` keyword will help. If the compiler is able to determine the actual type, it may choose to preform de-virtualization. Those costs could be quite huge if the method is used frequently. In old time the cost is often not durable. Modern computers are more powerful, things get better.~~

### Casting: `dynamic_cast` ~~& `const_cast`~~

A cast is an operator that forces one data type to be converted into another data type.

[Type erasure](https://en.wikipedia.org/wiki/Type_erasure) could be a problem. Consider when you pop something out of the container. The container only knows that the value is of type `Base*`. But you know it is actually an instance of `Derived*`. And most likely you need to use it as a `Derived` object. You need to transform a base class pointer to a derived class pointer.

In C++, dynamic casting is primarily used to safely downcast like casting a base class pointer (or reference) to a derived class pointer (or reference). It can also be used for upcasting, i.e. casting a derived class pointer (or reference) to a base class pointer (or reference).

* To use `dynamic_cast<new_type>(ptr)`, the base class should contain at least one virtual function.

* Dynamic casting checks consistency at runtime; hence, it is slower than static cast.

Below is an example.

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

~~See [const_cast](<https://en.cppreference.com/w/cpp/language/const_cast>) for its usage, it is skipped for now.~~



## Interfaces and Invariant

### Classes as Interfaces

Recall the two main advantages of an ADT:

1. Information hiding: we don't need to know the details of how the object is represented, nor do we need to know how the operations on those objects are implemented.
2. Encapsulation: the objects and their operations are defined in the same place; the ADT combines both data and operation in one entity.

To the caller, an ADT is only an interface, which is the contract for using things of this type.

The class mechanism failed to be a perfect interface. It mixes details of the implementation with the definition of the interface.

The method implementations can be written separately from the class definition and are usually in two separate files.  Unfortunately, the data members still must be part of the class definition. Since any programmer using your class see that definition, those programmers know something about the implementation.

What we prefer is to create an "interface-only" class as a base class, from which an implementation can be derived. Such a base class is called an *Abstract Base Class*, or sometimes a *Virtual Base Class*.

- Note: classes must contain their data members, so this class cannot have an real implementation.	

### Pure Virtual

It is possible that we do not supply a implementation when defining a base class. ~~In this case, the corresponding entry in the VTable would simply be left unfilled:~~

```c++
/* IntSet */ virtual void insert(int i) = 0;
```

In this case we say the method is pure virtual. 

If a class contains one or more pure virtual methods, we say the class is a pure virtual class. You only need to have one pure virtual function for a class to be “purely virtual”. Pure virtual class are also called abstract base classes, or interfaces.  It is often that the name abstract base classes starts with a case letter `I` for interface.

Note that **you can’t instantiate a pure virtual class.** This is one way to prevent users from instantiate your class (The other way is to make the constructor protected). However, you can always define references and pointers to an abstract class. 

*Abstract Base Classes* are often used to model abstract concepts. E.g. we would like to say things like Matrices are subclass of summable object. We would like to increase code reuse. Consider the following class:

```c++
class ISummable { 
public:
	/* Add item x to itself */
	virtual void add(ISummable& x) = 0; 
};
```

This class models the objects that are summable. Based on this modeling, we could write the following very general function: 

```c++
void sum(ISummable elem[],size_t size, ISummable& rst) {
	for (int i = 0; i < size; ++i) 
		rst.add(elem[i]); 
}
```

This will work for anything that is Summable object. When a class derives from an interface and provides an implementation, we say it implements the interface.

### Summary

Here is an comprehensive exercise. What would be the output?

```c++
struct Foo {
    void f() { cout << "a"; };
    virtual void g() = 0;
    virtual void c() const = 0;
};

struct Bar : public Foo {
    void f() { cout << "b"; };
    void g() { cout << "c"; };
    void c() const { cout << "d"; };
    void h() { cout << "e"; };
};

struct Baz : public Bar {
    void f() { cout << "f"; };
    void g() { cout << "g"; };
    void c() { cout << "h"; };
    virtual void h() { cout << "i"; };
};

struct Qux : public Baz {
    void f() { cout << "j"; };
    void h() { cout << "k"; };
};

int main() {
    Bar bar; bar.g();
    Qux qux; qux.g();
    Baz baz; baz.h();
    Foo& f1 = qux; f1.f(); f1.g();
    Bar& b1 = qux; b1.h();
    Baz& b2 = qux; b2.h();
    Bar* b3 = &qux; b3->h();
    Baz* b4 = &qux; b4->h();
    const Foo& f2 = *b3; f2.c();
    Baz& b5 = *b4; b5.c();
}
```

Answer would be `cgiagekekdh`.

### Invariant

An invariant is a set of conditions that must always evaluate to true at certain well-defined points; otherwise, the program is incorrect. For ADT, there is so called representation invariant.

It describes the conditions that must hold on those members for the representation to correctly implement the abstraction. It must hold immediately before exiting each method of that implementation, including the constructor.
Each method in the class can assume that the invariant is true on entry if the following 2 conditions hold:

- The representation invariant holds immediately before exiting each method (including the constructor);
- Each data element is truly private.

Writing some private  `bool isInvariant()` functions for *defensive programming* to check whether all invariants are true (before exiting, or after entering, each method):

Next, add assertions like `assert(isInvariant());` right before returning from any function that modifies any of the representation.



# Lecture 17: Dynamic Memory Allocation

## ~~Memory Management~~

~~Each running program has its own memory layout, separated from other programs. The layout consists of a lot of segments, including:~~

- ~~`stack`: stores local variables~~
- ~~`heap`: dynamic memory for programmer to allocate~~
- ~~`data`: stores global variables, separated into initialized and uninitialized~~
- ~~`text`: stores the code being executed~~

~~In order to pinpoint each memory location in a program’s memory, we assign each byte of memory an “address”. The addresses go from 0 all the way to the largest possible address, depending on the machine. As the figure below, the `text`, `data`, and `stack` segments have low address numbers, while the `stack` memory has higher addresses.~~

![img](https://courses.engr.illinois.edu/cs225/sp2020/assets/notes/stack_heap_memory/memory_layout.png)

## `new` & `delete`

Mostly, a fixed-sized structure is undesired. Yet, VLA is forbidden in c++.

```c++
int num = 100;
int array[num]; // Error
```

This leads to:

```bash
warning: ISO C++ forbids variable length array 'array' [-Wvla]
```

In ISO c++ standard, it's not allowed to have variable length array. Although G++ allows this as an "extension" (because C allows it), if you add `-pedantic` to the compiling option, it will have warning.

`man g++`:

```bash
-Wpedantic
	-pedantic
  	Issue all the warnings demanded by strict ISO C and ISO C++; reject
    all programs that use forbidden extensions, and some other programs
		that do not follow ISO C and ISO C++.
```

It's not allowed to use variable length array in c++, especially if you want your code to be as portable as possible. This is where we need dynamic length array.

```c++
int num = 100;
int *array = new intnum;
delete [] array;
```

new and new[] does the following:

* Allocates space in heap (for one or a number of objects).
* Constructs object in-place (including, but not limited to ctor).
* Returns the “first” address.

The syntax for new operator are very simple.

```c++
Type* obj0 = new Type; // Default construction
Type* obj1 = new Type(); // Default construction
Type* obj2 = new Type(arg1, arg2);
Type* objA0 = new Type[size]; // Default cons each elt
Type* objA1 = new Type[size](); // Same as obj A0
```

Since `new` allocates memory from the heap, they essentially requested (and occupies) resources from the system. For long running programs resources must always be returned (or released) when the program is finished with them, otherwise the program will end up draining all system resources, in our case running out of memory.

`delete` and `delete[]` releases the objects allocated from `new` and `new[]` respectively. They does the following:

* Destroy the object (each object in the array) being released (by calling the destructor of the object).
* Returns the memory to the system. 

We must emphasize that deletion is not idempotent, i.e. `delete` an object more than once, or delete an array allocated using `new[]` by `delete` instead of `delete[]` cause UB! 

### Destructor

The destructors for any ADTs declared locally within a block of code are called automatically when the block ends.

```c++
{
	IntSet ip = IntSet(50);
	...		
} // ip will be destroyed by calling its destructor
```

Destructor of ADT will also be called when using `delete`. A effective destructors should:

* Be named as `~ClassName`
* Takes no argument and returns nothing (not even void)
* If one expect the class to be inherited the destructor should be declared as `virtual`
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

## Memory Leaks

If an object is allocated, but not released after the program is done with it, the system would assume the resource is still being used (since it won’t examine the program), but the program will never use it. Thus resource is “leaked”, i.e. no longer available for using. In our case the leaked resource is memory.

`valgrind` is not a tool that only looks for memory leaks. It actually looks for for all sorts of memory related problems, including:

- Memory Leaks
- Invalid accesses
  - Array out-of-range
  - Use of freed memory
- Double free problems

Consider the following examples. Which implementation if free of leakage and why?

1. Memory Leaks.

```c++
class Base {
protected:
	int *p;
public:
	Base() : p(new int(10)) {}
	~Base() {delete p;}
};

class Derived : public Base {
	int *q;
public:
	Derived() : Base(), q(new int(20)) {}
	~Derived() {delete q;}
};

/* A */
void main() {
	Base* ptrA = new Derived;
	delete ptrA;
}

/* B */
void main() {
	Derived* ptrB = new Derived;
	delete ptrB;
}
```

2. Double Deletion.

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
	Base* ptrA = new Derived;
	delete ptrA;
}

/* B */
void main() {
	Derived* ptrB = new Derived;
	delete ptrB;
}
```

How to correct the codes?

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
    virtual ~Derived() override {delete q;}
};
```



# Lecture 18: Deep Copy

## Shallow Copy & Deep Copy

Because C++ does not know much about your class, the default copy constructor and default assignment operators it provides use a copying method known as a member-wise copy, also known as a *shallow copy*.

![Shallow](https://media.geeksforgeeks.org/wp-content/uploads/shallow-copy.jpg)

This works well if the fields are values, but may not be what you want for fields that point to dynamically allocated memory. The pointer will be copied. but the memory it points to will not be copied: the field in both the original object and the copy will then point to the same dynamically allocated memory, this causes problem at erasure, causing dangling pointers.

Instead, a *deep copy* copies all fields, and makes copies of dynamically allocated memory pointed to by the fields.



![Deep](https://media.geeksforgeeks.org/wp-content/uploads/deep-copy.jpg)

### The Rule of the Big 3/5

If you have any dynamically allocated storage in a class, you must follow this Rule of the Big X, where X = 3 traditionally and X = 5 after c++11.

> Whenever an object owns resources, any resources, not just memory, it should implement 5 methods: A ctor and a dtor, A copy ctor, a move ctor, a copy assignment operator, and a move assignment operator.

These are 5 typical situations where resource management and ownership is critical. You should never leave them unsaid whenever dynamic allocation is involved. Traditionally constructor/destructor/copy assignment operator forms a rule of 3. Move semantics is a feature available after C++11, which is not in the scope of this course. Learn more about them in EECS 381.

If you want to use the version synthesized by the compiler, you can use `= default`:

```c++
Type(const Type& type) = default;
Type& operator=(Type&& type) = default;
```

Usually, we would need to implement some private helper functions `removeAll()` and `copyFrom()`, and use them in the big 3. Consider the `Dlist` example.

* A destructor

```c++
template <class T>
Dlist<T>::~Dlist() {
    removeAll();
}
```

* A copy constructor

```c++
template <class T> 
Dlist<T>::Dlist(const Dlist &l): first(nullptr), last(nullptr) {
  copyAll(l); 
}
```

* An assignment operator

```c++
template <class T>
Dlist<T> &Dlist<T>::operator=(const Dlist &l) {
    if (this != &l) {
        removeAll();
        copyAll(l);
    }
    return *this;
}
```

### Example

Recall binary tree and in-order traversal. We define that a good tree is a binary tree with ascending in-order traversal. How to deep copy a template good tree provided interface:

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
```

You may use `removeAll` and `insert` in your `copyAll` method.

---

The sample answer is as follows.

```c++
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

### ~~Exception Safety~~

~~Skipped. See [Lessons Learned from Specifying Exception-Safety for the C++ Standard Library](<https://www.boost.org/community/exception_safety.html>).~~



# Lecture 19: Dynamic Resizing

In many applications, we do not know the length of a list in advance, and may need to grow the size of it when running the program. In this kind of situation, we may need dynamic resizing. 

## Array

If the implementation of the list is a dynamically allocated array, we need the following steps to grow it:

- Make a new array with desired size. For example, 

  ```c++
  int *tmp = new int[new_size];
  ```

- Copy the elements from the original array to the new array iteratively. Suppose the original array is `arr` with size `size`.

  ```c++
  for (int i = 0; i < size; i++){
      tmp[i] = arr[i];
  }
  ```

- Replace the variable with the new array and delete the original array. Suppose the original array is `arr`:

  ```c++
  delete [] arr;
  arr = tmp;
  ```

- Make sure all necessary parameters are updated. For example, if the `size` of array is maintained, then we can do:

  ```cpp
  size = new_size;
  ```

Common selections of `new_size` can be:

- `size + 1`: This approach is simplest but most inefficient. Inserting `N` elements from capacity 1 needs `N(N-1)/2` number of copies.
- `2*size`: Much more efficient than `size+1`. The number of copies for inserting `N` elements becomes smaller than `2N`.
- What about even larger (eg: `size^2`)? Usually not good, for it occupies far too much memory.

Learn more about amortized complexity in VE281/EECS281.

## Linked lists

To enlarge a list implemented by linked list, you can simply add a node at the end of the linked list. 

The good thing about this is that no copy is required. Details in later discussions.



# Lecture 20: Linked List

Recall what you have implemented in lab 9-10 & project 5.

## Single-Ended & Doubly-Ended

Linked lists could be either single ended or doubly linked, depending on the the number of node pointers in the container.

In a singly ended list, we only need a `first`.

```c++
class IntList {
    node *first;
    //...
};
```

In a doubly ended list, we need also a `last`.

```c++
class IntList {
    node *first;
    node *last;
    //...
};
```

Especially, when handling a singly ended list, you need to be concerned about the special situation where

* size = 0: `first` is `nullptr`
* size = 1: `first` is the last and only node in the list. 

In a doubly ended list, the `last` makes it slightly more complicated:

- size = 0: `first` and `last` is `nullptr`
- size = 1: `first` is connecting to `last`. 

## Singly-Linked & Doubly-Linked

Linked lists could be either single linked or doubly linked, depending on the the number of directional pointers in `node`.

In a singly linked list, we only need a `next`.

```c++
struct node {
	node *next;
	int value;
};
```

![Singly-linked-list.svg](https://upload.wikimedia.org/wikipedia/commons/thumb/6/6d/Singly-linked-list.svg/408px-Singly-linked-list.svg.png)

In a doubly linked list, we need also a `prev`.

```c++
struct node {
	node *next;
	node *prev;
	int value;
};
```

![Doubly-linked-list.svg](https://upload.wikimedia.org/wikipedia/commons/thumb/5/5e/Doubly-linked-list.svg/610px-Doubly-linked-list.svg.png)



## Linked List Methods

### Insertion

Insertion at ends:

![img](https://www.cs.cmu.edu/~adamchik/15-121/lectures/Linked%20Lists/pix/prepend.bmp)

Insertion after:

![img](https://www.cs.cmu.edu/~adamchik/15-121/lectures/Linked%20Lists/pix/after.bmp)

Insertion before:

![img](https://www.cs.cmu.edu/~adamchik/15-121/lectures/Linked%20Lists/pix/before.bmp)



### Deletion

![img](https://www.cs.cmu.edu/~adamchik/15-121/lectures/Linked%20Lists/pix/delete.bmp)

# Lecture 21: Template & Container

### Template: Code reuse; polymorphism

### Container of pointers: 1 invariant & 3 rules

- *At-most-once invariant*: any object can be linked to at most one container at any time through pointer.

1. *Existence*: An object must be dynamically allocated before a pointer to it is inserted.
2. *Ownership*: Once a pointer to an object is inserted, that object becomes the property of the container. No one else may use or modify it in any way.
3. *Conservation*: When a pointer is removed from a container, either the pointer must be inserted into some container, or its referent must be deleted.

```c++
template <class T>
class Set {
    T **elts; // An array of T *
    int numElts;
    int sizeElts;    
public:
    bool isEmpty();
    void insert(T *vp);
    T *remove();
    Set(int sizeElts = MAXELTS);
    Set(const Set &s);
    Set &operator=(const Set &s);
    ~Set();
};

// where needs to put <T>
Set<T>::Set(){...}
Set<T>::Set(const Set<T> &s){...}
Set<T> &Set<T>::operator=(const Set<T> &s){...}
Set<T>::~Set(){...}
```



**Which invariant/rule is violated?**

```c++
// 1
Set<T>::Set(const Set<T> &s){
    for(int i = 0; i < s.numElts; ++i){
        insert(s[i]);
    }
}

// 2
Set<T>::~Set(){
    while(numElts > 0){
        remove();
    }
}

// -----
Set<int> s1;
Set<int> s2;

int *v1;
int *v2 = new int(5);
int *v3 = new int(6);

// 3
s1.insert(v1);
for(int i = 0; i < 3; ++i){
    s2.insert(&i);
}

// 4
s1.insert(v2);
*v2 = 3;

// 5
int *v3 = new int(*(s1.remove()));
s2.insert(v3);
```



Answer:

1. At-most-once invariant
2. Conservation rule
3. Existence rule
4. Ownership rule
5. Conservation rule



### Polymorphic Container

```c++
class BigThing : public Object {
...
};

Set<Object> s;
BigThing *bp1 = new BigThing;
s.insert(bp1); // Legal due to substitution rule

Object *op;
BigThing *bp2;
op = s.remove();
bp2 = dynamic_cast<BigThing *>(op);
// if the actual type of `op` is either pointer to `BigThing` or some pointer to derived class of `BigThing`, `bp2` will be assigned a pointer to `BigThing`; Otherwise, `bp2` will be a null pointer
assert(bp2); 
```



# Lecture 22: Operator Overload

For full explanations see [Operators](<https://en.cppreference.com/w/cpp/language/operators>).

C++ lets us redefine the meaning of the operators when applied to objects of class type. This is known as operator overloading.

Like any other function, an overloaded operator has a return type and a parameter list.

## Unary operators

```c++
A A::operator-() const;
A& A::operator++();    // ++a
A A::operator++(int);  // a++
A& A::operator--();    // --a
A A::operator--(int);  // a--
```

## Binary operators

```c++
A& A::operator= (const A& rhs);
A& A::operator+= (const A& rhs);
A& A::operator-= (const A& rhs);
A operator+ (const A& lhs, const A& rhs);
istream& operator>> (istream& is, A& rhs);
ostream& operator<< (ostream& os, const A& rhs);
bool operator== (const A& lhs, const A& rhs);
bool operator!= (const A& lhs, const A& rhs);
bool operator< (const A& lhs, const A& rhs);
bool operator<= (const A& lhs, const A& rhs);
bool operator> (const A& lhs, const A& rhs);
bool operator>= (const A& lhs, const A& rhs);

// Especially:
const T& A::operator[] (size_t pos) const;
T& A::operator[] (size_t pos);
```



# Lecture 23: Linear List; Stack

## 1. Linear List

The main idea thing is that the operations are based by position. And if the position that you are going to access are invalid, you should throw `BoundsError` exception.

## 2. Stack

Property: last in, first out (*LIFO*).

### Methods of Stack

- `size()`: number of elements in the stack.
- `isEmpty()`: check if stack has no elements.
- `push(Object o)`: add object o to the **top** of the stack.
- `pop()`: remove the **top** object if stack is not empty; otherwise, throw `stackEmpty`.
- `Object &top()`: returns a reference to the top element.

### Implementation

#### Using Arrays

Need an `int size` to record the size of the stack.

- `size()`: `return size;`
- `isEmpty()`: `return (size == 0);`
- `push(Object o)`: add object o to the **top** of the stack and increment `size`. Allocate more space if necessary.
- `pop()`: If `isEmpty()`, throw `stackEmpty`; otherwise, decrement `size`.
- `Object &top()`: returns a reference to the top element `Array[size-1]`.

#### Using Linked Lists

- `size()`: `LinkedList::size();`
- `isEmpty()`: `LinkedList::isEmpty();`
- `push(Object o)`: insert object at the beginning `LinkedList::insertFirst(Object o);`.
- `pop()`: remove the first node `LinkedList::removeFirst();`
- `Object &top()`: returns a reference to the object stored in the first node.

#### Comparison: memory and time trade-off

1. Linked List:
   - memory efficient: a new item just needs extra constant amount of memory
   - time inefficient for `size()` operation because need to traverse the whole list
2. Array:
   - time efficient for `size()`.
   - memory inefficient: need to allocate a big enough array

### Applications

1. Function calls in C++
2. Web browser's "back" feature
3. Parentheses Matching

# Lecture 24: Queue

Very commonly used data structure. Basic principle: "First In Frist Out" (`FIFO`).

## Methods of Queue

Most important methods (almost all kinds of queues has these methods):

- `enqueue(Object o)`: add object o to the rear of the
  queue. (Usually returns nothing.)
- `dequeue()`: remove the front object of the queue if not
  empty; otherwise, throw an exception. (Usually returns the object that is removed.)
- `size()`: returns number of elements in the queue.
- `isEmpty()`: check if queue has no elements.

Other possible methods:

- `Object &front()`: returns a reference to the front
  element of the queue.
- `Object &rear()`: returns a reference to the rear element
  of the queue.

## Queues Using Linked Lists

How to implement the mothods using linked lists:

- `enqueue(Object o)`: add a node to the end of the linked list.
- `dequeue()`: remove a node from the head of the linked list.
- `size()`: can iterate through the linked list and count the number of nodes.
- `isEmpty()`: check if the pointer to the linked list is `NULL`.
- `Object &front()`: returns a reference to the node at the head of the linked list.
- `Object &rear()`: returns a reference to the node at the end of the linked list.

## Queues Using Arrays

- Let the elements "drift" within the array. 

- Maintain two integers to indicate the front and the rear of the queue (advance `front` when dequeuing; advance `rear` when inserting).

- Use a circular array (more space efficient):

  ![alt text](https://github.com/xiejinglei/links/blob/master/queue_arr.JPG?raw=true)

  When inserting a new element, advance `rear` circurlarly; when popping out an element, advance `front` circularly.

  Can be realized by 

  ```cpp
  front = (front+1) % MAXSIZE;
  rear = (rear+1) % MAXSIZE;
  ```

- Solve the problem of distinguishing an empty queue and full queue:

  ![alt text](https://github.com/xiejinglei/links/blob/master/queue_arr_2.JPG?raw=true)

  Maintain a `flag` indicating empty or full, or a `count` on the number of elements in the queue.

We can see that using array can be more complicated than linked list, and the size can be restricted by `MAXSIZE` of array. However, it can be easier to access the elements by index. For example, the index of the second element can be `front+1` (if not exceeding the capacity of array). Still, accessing elements by index is not very useful in queues.

## Deque

Property: Items can be inserted and removed from both ends of the list.

Methods:

- `push_front(Object o)`
- `push_back(Object o)`
- `pop_front()`
- `pop_back()`

The implementation can be more complicated than queue. Only use it if inserting and removing from both ends are truely necessary.

# Lecture 25, 26: STL

Three kinds of containers:

- **Sequential Containers**: let the programmer control the order in which the elements are stored and accessed. The order doesn't depend on the values of the elements.
- **Associative Containers**: store elements based on their *values*.
- **Container Adaptors**: take an existing container type and make it act like a different type

## Sequential Containers:

1. [vector](http://www.cplusplus.com/reference/vector/vector/): based on arrays.
   - fast random access
   - fast insert/delete at the back
   - inserting / deleting ar other position is slow
2. [deque](http://www.cplusplus.com/reference/deque/deque/) (double-ended queue): based on arrays.
   - fast random access (operator[])
   - fast insert/delete at front or back
3. [list](http://www.cplusplus.com/reference/list/list/): based on doubly-linked lists.
   - only bidirectional sequential access (no operator[])
   - fast insert/delete at any point in the list

### I. Vector

1. How to use it

```cpp
#include <vector>
using namespace std;

vector<int> ivec; // holes ints
vector<IntSet> isvec; // holds IntSets
```

1. [Initialization](http://www.cplusplus.com/reference/vector/vector/vector/)

```cpp
vector<T> v1; // empty vector v1
vector<T> v2(v1); // copy constructor
vector<T> v3(n,t); // construct v3 that has n elements with value t
```

1. Size

- `v.size()` returns a value of *size_type* corresponding to the vector type.

- `vector<int>::size_type`

  - a companion type of vector (why: to make the type machine-independent)

  - essentially an unsigned type

    - you can convert it into `unsigned int` but not `int`:

      ```cpp
      unsigned int s = v.size();
      ```

  - not `vector::size_type`

- check whether empty: `v.empty()`

1. Add/Remove

- `v.push_back(t)`: add element `t` to the end of `v`
  - container elements are copies: no relationship between the element in the container and the value from which it was copied
- `v.pop_back()`: remove the last element in `v`. `v` must be non-empty

1. Subscripting Vector

```cpp
vector<int>::size_type n;
v[n] = 0; //must ensure that the v.size() > n

for (n = 0; n != v.size(); ++n) {
    v[n] = 0;
}
```

1. other operations:

```cpp
v1 = v2;
v.clear();
v.front(); //non-empty
v.back(); //non-empty
```

#### Iterator

All of the library containers define iterator types, but only a few of them support subscripting.

1. Declaratino:
   `vector<int>::iterator it;`

2. - `v.begin()` returns an iterator pointing to the first element of vector
   - `v.end()` returns an iterator positioning to **one-past-the-end** of the vector
     - usually used to indicate when we have processed all the elements in the vector
     - If the vector is empty, the iterator returned by `begin` is the same as the iterator returned by `end`, e.g.

3. Operations:

   - dereference: can read/write through `*iter` (cannot dereference the iterator returned by `end()`)

   - `++iter, iter++`: next item (cannot increment the iterator returned by `end()`); 

     `--iter, iter--` go back to the previous item

   - `iter == iter1` and `iter != iter1`: check whether two iterators point to the same data item

   ```cpp
   vector<int>::iterator begin = ivec.begin();
   vector<int>::iterator end = ivec.end();
   while (begin != end) {
       cout << *begin++ << " ";
       // 1. get the value of *begin
       // 2. cout << *begin << " ";
       // 3. begin++;
   }
   ```

4. `const_iterator`: cannot change the value of the element it refers to. 

   - Declaration: `vector<int>::const_iterator it;`
   - check `cbegin()` and `cend()`, which will return const iterator.

5. Iterator Arithmetic

   **Not all** containers support! Check random access iterator [here](https://en.cppreference.com/w/cpp/iterator) for example.

   - `iter+n, iter-n`, where `n` is an integer
   - example: go to the middle

   ```cpp
   vector<int>::iterator mid;
   mid = v.begin() + v.size()/2;
   ```

6. Relational Operation: >, >=, <, <=

   **Not all** containers support!

   - To compare, iterators must refer to elements in the same container or one past the end of the container (`c.end()`)

7. More about initilization of vector
   `vector<T> v(b,e)`: create vector `v` with a copy of the elements from the range denoted by iterators `b` and `e`. 

   - **[b,e)**

   - check the constructor of the containers, [vector](http://www.cplusplus.com/reference/vector/vector/vector/) for example.

     ```cpp
     vector<int> front(v.begin(), mid);
     ```

   - You can use deque to initialize vector, e.g.

     ```cpp
     deque<string> ds(10, "abc");
     vector<string> vs(ds.begin(), ds.end());
     ```

   - Use array to initialize vector:

     ```cpp
     int a[] = {1, 2, 3, 4};
     unsigned int sz = sizeof(a) / sizeof(int);
     vector<int> vi(a, a+sz);
     ```

8. `v.insert(p, t)` 

   - inserts element with value `t` **right before** the element referred to by iterator `p`.
   - returns an iterator referring to the element that was added

9. `v.erase(p)` 

   - removes element refered to by iterator `p`.
   - returns an iterator referring to the elemtn after the one deleted, or an **off-the-end** iterator if `p` referred to the last element.

### II. Deque

1. `#include <deque>`
2. Similarities with vector:
   - [Initialization](http://www.cplusplus.com/reference/deque/deque/deque/):
     - `deque<T> d; deque<T> d(d1);`
     - `deque<T> d(n,t)`: create `d` with `n` elements, each with value `t`.
     - `deque<T> d(b,e)`: create `d` with a copy of the elements from the range denoted by iterators `b` and `e`.
   - `size(), empty()`
   - `push_back(), pop_back()`
   - random access through `d[k]`
   - `begin(), end(), insert(p,t), erase(p)`
   - operations on iterators: `*iter, ++iter, --iter, iter != iter2, iter == iter2`......
3. Difference with vector:
   - `d.push_front(t)`
   - `d.pop_front(t)`

### III. List

1. `#include <list>`
2. only bidirectonal sequential access
3. Similarities with vector:
   - [Initialization](http://www.cplusplus.com/reference/list/list/list/):
     - `list<T> l; list<T> l(l1);`
     - `list<T> l(n,t)`: create `l` with `n` elements, each with value `t`.
     - `list<T> l(b,e)`: create `l` with a copy of the elements from the range denoted by iterators `b` and `e`.
   - `size(), empty()`
   - `push_back(), pop_back()`
   - `begin(), end(), insert(p,t), erase(p)`
   - operations on iterators: `*iter, ++iter, --iter, iter != iter2, iter == iter2`......
4. Difference with vectors
   - not suppoert subscripting
   - not suppoer iterator arithmetic, i.e. cannot do `it+3`, you can only use `++/--`
   - no relational operation <, <=, >, >=, you can only use == and != to compare
   - `l.push_front(t)`
   - `l.pop_front(t)`

### Choose appropriate containers

1. Use vector, unless have other good reasons
2. require random access: vector or deque
3. insert or delete elements in the middle: list
4. insert or delete elements at the front and the back: deque
5. others: check the predominant operations

## Container Adaptors

e.g. [stack](http://www.cplusplus.com/reference/stack/stack/), [queue](http://www.cplusplus.com/reference/queue/queue/), priority_queue (will be learned in 281)

1. `#include <stack>` and `#include <queue>`
2. By default, there are implemented using deque. So if you initializa it in this way: `stack<int> stk(deq);`, `deq` must be a deque. But you can also use vector or list to build stack:

```cpp
// Assume ivec is vector<int>
stack<int, vector<int> > stk(ivec); 
//                    ^ theres is a space here   
```

1. Notice that for queue, you can use deque and list to build it (no vector here). Check the link.

2. Be aware that the names of the operations are different with previous ones. Check the link.

   |    stack     |     queue     |
   | :----------: | :-----------: |
   |  s.empty()   |   q.empty()   |
   |   s.size()   |   q.size()    |
   |   s.pop()    |    q.pop()    |
   | s.push(item) | q.push(item)  |
   | **s.top()**  | **q.front()** |



## Associative Container

### ADT: Dictionary

1. quickly add (key, value) pair and retrieve value by key
2. Methods
   - Value find(Key K): return the value whose key is K. Return Null if none.
   - void insert(Key K, Value V): Insert a pair (K, V) into the dictionary. If the pair with key as K already exists, **update** the value.
   - Value remove(Key K): Remove the pair with key as K from the dictionary and return its value. Return Null if none.
   - int size(): return number of pairs in the dictionary.
3. Implementation: array or linked list.

### Applications:

1. map: dictionary, elements are (key, value) pairs
2. set: contains only a key and supports efficient queries to whether a gicen key is present.

### [Map: associative array](http://www.cplusplus.com/reference/map/map/)

Important: key cannot be duplicate

1. `#include <map>`

2. [Constructors](http://www.cplusplus.com/reference/map/map/map/):

   - `map<k, v> m;` // create an empty map named m
   - `map<k, v> m(m1);` // create m as a copy of m1, the two maps must have the same key and value types
   - `map<k, v> m(b, e)` // create m as a copy of the elemtns from the range denoted by iterators b and e

3. Elements are sorted by keys, so the key type should has: strick weak ordering (<)

4. iterators: `map<string, int>::iterator it = word_count.begin()`, then `*it` is a reference to a `pair<const string, int>`.

   - Please notice that `it->first` is const, so we cannot write `it->first = "new key";`.
   - To access the value, use `it->second`, you can assign new value to it.
   - Note that here we are using arrows (->) to access its key or value.

5. Adding elements to a map

   - use subscript operator (different with `vector`)

     - if the key is already there in the map, then there is nothing new. You can read or update the value using `m[k]=v`.
     - if the key is not there, `m[k] = v` will
       1. search the key `k` and don't find it.
       2. insert (k, default_v) to the map. If `v` is `int`, it will insert (k, 0).
       3. update (k, default_v) to (k, v)

   - use [insert](http://www.cplusplus.com/reference/map/map/insert/) member: 

     - `m.insert(e)`, where `e` is a (key, value) pair. If the key is not in m, then insert the pair. Otherwise, does nothing.
     - returns a **pair** of (map iterator, bool)
       - map iterator refers to the element with key
       - bool indicates whether the element was inserted or not

     ```cpp
     #include <iostream>
     #include <map>
     
     int main (){
         std::map<char,int> mymap;
     
         // first insert function version (single parameter):
         mymap.insert ( std::pair<char,int>('a',100) ); 
         // can also use mymap.insert(std::make_pair('a', 100))
         // remember to #include <utility> if you use make_pair
         mymap.insert ( std::pair<char,int>('z',200) );
     
         std::pair<std::map<char,int>::iterator,bool> ret;
         ret = mymap.insert ( std::pair<char,int>('z',500) );
         if (ret.second==false) {
             std::cout << "element 'z' already existed";
             std::cout << " with a value of " << ret.first->second << '\n';
         }
     }
     ```

6. find elements: `m.find(k)`

   - returns an iterator to the element indexed by key k if there is one
   - else, returns an off-the-end iterator: compare with `end()` to check whether the key is there

   ```cpp
   int occurs = 0;
   map<string, int>::iterator it = world_count.find("abc");
   if (it != world_count.end()) occurs = it->second;
   ```

7. remove elements:

   - `m.erase(iter)` 
     - removes element referred to by the iterator `iter` from `m`. `iter` muse refer to an actual element in `m`; it must not be `m.end()`
     - returns void
   - `m.erase(k)`
     - removes the element with key k from m if it exists
     - otherwise, do nothing
     - returns the number of elements removed, either 0 or 1 for map.

8. iterate across a map: When we use a niterator to traverse a map, the iterators yield elements in ascending key order.

   ```cpp
   map<string, int>::iterator it;
   for(it = word_count.begin(); it != word_count.end(); ++it) {
       cout << it->first <<" occurs" << it->second << " times";
   }
   ```

   For the STL part, please search the thing you need in www.cplusplus.com/reference/ or en.cppreference.com/w/ often