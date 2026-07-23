========================================================================
  EXERCISE 02: Identify real type
========================================================================

TABLE OF CONTENTS
-----------------
  1. What is this exercise about?
  2. What is polymorphism?
  3. What is dynamic_cast?
  4. What are virtual functions?
  5. File-by-file explanation
  6. How to compile and run
  7. What you will see when you run it
  8. Common mistakes and tips


========================================================================
1. WHAT IS THIS EXERCISE ABOUT?
========================================================================

This exercise teaches you about polymorphism and runtime type
identification. You need to create a Base class and three derived
classes (A, B, C), then identify the actual type at runtime.

The program must:
  - Create a Base class with a virtual destructor
  - Create three empty classes A, B, C that inherit from Base
  - Randomly generate instances of A, B, or C
  - Identify the actual type using pointers and references
  - NOT use std::typeinfo (typeid or dynamic_cast with type_info)


========================================================================
2. WHAT IS POLYMORPHISM?
========================================================================

Polymorphism means "many forms". In C++, it allows you to treat
objects of different types through a common base class.

Example:
  Base *ptr = new A();  // ptr is Base*, but points to A
  Base *ptr2 = new B(); // ptr2 is Base*, but points to B

You can call virtual functions on these pointers, and the correct
version (A's or B's) will be called.

Why is this useful?
  - You can write code that works with any derived class
  - You don't need to know the exact type at compile time
  - You can create collections of different types


========================================================================
3. WHAT IS DYNAMIC_CAST?
========================================================================

dynamic_cast is a C++ cast that performs runtime type checking.
It is used in inheritance hierarchies.

  Base *ptr = new A();
  A *a = dynamic_cast<A *>(ptr);  // Works! a points to A
  B *b = dynamic_cast<B *>(ptr);  // Fails! b is NULL

For pointers:
  - Returns NULL if the cast fails
  - Requires the base class to have at least one virtual function

For references:
  - Throws std::bad_alloc if the cast fails
  - Cannot return NULL (references cannot be NULL)

In this exercise:
  - We use dynamic_cast to identify the actual type
  - We try casting to A, B, and C
  - The one that succeeds tells us the actual type


========================================================================
4. WHAT ARE VIRTUAL FUNCTIONS?
========================================================================

A virtual function is a function declared in a base class that can
be overridden in derived classes.

  class Base
  {
  public:
      virtual ~Base();  // Virtual destructor is essential!
  };

Why do we need a virtual destructor?
  - When you delete a Base pointer that points to a derived class
  - Without virtual, only Base's destructor is called (memory leak!)
  - With virtual, the correct derived destructor is called

Example:
  Base *ptr = new A();
  delete ptr;  // Without virtual: only ~Base() called (LEAK!)
               // With virtual: ~A() then ~Base() called (correct!)


========================================================================
5. FILE-BY-FILE EXPLANATION
========================================================================

--- Base.hpp ---

  This file declares the Base class and its derived classes.

  Base class:
    - Has only a virtual destructor
    - Empty class (no data members, no methods)

  Classes A, B, C:
    - Empty classes that inherit from Base
    - Public inheritance from Base
    - No additional members

  Free functions:
    generate()  - Randomly creates A, B, or C
    identify()  - Two versions: one for pointers, one for references

--- Base.cpp ---

  This file implements the functions.

  ~Base():
    - Virtual destructor (essential for polymorphism)
    - Empty because there's nothing to clean up

  generate():
    - Uses std::rand() to generate 0, 1, or 2
    - Creates and returns a new A, B, or C
    - Returns as Base pointer (polymorphism)

  identify(Base *p):
    - Uses dynamic_cast to check if p is A, B, or C
    - Prints the actual type
    - For pointers: dynamic_cast returns NULL if fails

  identify(Base &p):
    - Uses dynamic_cast to check if p is A, B, or C
    - Prints the actual type
    - For references: dynamic_cast throws if fails
    - Uses try-catch to handle failed casts

--- main.cpp ---

  This file tests the functions.

  Steps:
    1. Seed the random number generator
    2. Generate 10 random objects
    3. Identify each using both pointer and reference versions
    4. Delete each object to prevent memory leaks


========================================================================
6. HOW TO COMPILE AND RUN
========================================================================

Open a terminal and navigate to the ex02 directory.

  Step 1: Compile
    Type: make
    This creates an executable called "identify".

  Step 2: Run
    Type: ./identify

  Other commands:
    make clean   -> Removes .o files
    make fclean  -> Removes .o files and executable
    make re      -> Full rebuild


========================================================================
7. WHAT YOU WILL SEE WHEN YOU RUN IT
========================================================================

Example output:

  === Generating and identifying 10 random objects ===
  Object 1 - Pointer: B
  Object 1 - Reference: B
  Object 2 - Pointer: A
  Object 2 - Reference: A
  Object 3 - Pointer: C
  Object 3 - Reference: C
  Object 4 - Pointer: B
  Object 4 - Reference: B
  Object 5 - Pointer: A
  Object 5 - Reference: A
  Object 6 - Pointer: C
  Object 6 - Reference: C
  Object 7 - Pointer: A
  Object 7 - Reference: A
  Object 8 - Pointer: B
  Object 8 - Reference: B
  Object 9 - Pointer: C
  Object 9 - Reference: C
  Object 10 - Pointer: A
  Object 10 - Reference: A

Note: The output will vary because the selection is random.


========================================================================
8. COMMON MISTAKES AND TIPS
========================================================================

  1. Not using virtual destructor
     - Without it, memory leaks occur when deleting derived objects
     - ALWAYS use virtual destructors in base classes

  2. Using std::typeinfo
     - The subject forbids std::typeinfo
     - Use dynamic_cast instead

  3. Not using try-catch for reference version
     - dynamic_cast with references throws on failure
     - Must use try-catch block

  4. Not deleting generated objects
     - generate() uses new, so you must delete
     - Otherwise, memory leak!

  5. Forgetting to seed the random number generator
     - std::srand(std::time(NULL)) must be called once
     - Otherwise, you get the same sequence every run

  6. Using C++11 features
     - This exercise uses C++98 standard
     - No random library, no auto, no nullptr

  7. Not identifying both pointer and reference
     - The subject requires two identify() functions
     - One for pointers, one for references

========================================================================