========================================================================
  EXERCISE 02: Mutated abomination
========================================================================

TABLE OF CONTENTS
-----------------
  1. What is this exercise about?
  2. What is std::stack?
  3. Why is std::stack not iterable?
  4. What is inheritance?
  5. Adding iterators to std::stack
  6. File-by-file explanation
  7. How to compile and run
  8. What you will see when you run it
  9. Common mistakes and tips


========================================================================
1. WHAT IS THIS EXERCISE ABOUT?
========================================================================

This exercise teaches you about class inheritance, the std::stack
container, and how to add missing functionality to existing classes.

You need to create a MutantStack class that:
  - Inherits from std::stack
  - Offers all std::stack member functions
  - Adds iterator support (making it iterable)
  - Works like std::list when iterated

The goal: make std::stack iterable by "butchering" it with inheritance.


========================================================================
2. WHAT IS STD::STACK?
========================================================================

std::stack is a container adapter that provides LIFO (Last In, First Out)
access to elements.

Declaration:
  std::stack<int> s;

Key operations:
  - s.push(value)   Add element to top
  - s.pop()         Remove top element
  - s.top()         Access top element
  - s.empty()       Check if empty
  - s.size()        Get number of elements

Why use std::stack?
  - Simple interface for LIFO behavior
  - Used in parsing, undo systems, etc.
  - Efficient O(1) operations

Problem:
  - std::stack does NOT have iterators
  - You cannot iterate through elements
  - This is what this exercise fixes!


========================================================================
3. WHY IS STD::STACK NOT ITERABLE?
========================================================================

std::stack is a "container adapter" - it wraps another container
and provides a restricted interface.

By default, std::stack uses std::deque as its underlying container.
However, it only exposes:
  - push(), pop(), top(), empty(), size()

It does NOT expose:
  - begin(), end() (iterators)
  - Any way to access elements except the top

This is by design - a stack should only access the top element.
But sometimes you need to iterate (for debugging, printing, etc.).


========================================================================
4. WHAT IS INHERITANCE?
========================================================================

Inheritance allows a new class to reuse code from an existing class.

Syntax:
  class Derived : public Base
  {
      // Derived class has all Base features
  };

Example:
  class MutantStack : public std::stack<int>
  {
      // MutantStack has all std::stack features
      // Plus our added features (iterators)
  };

Benefits:
  - Code reuse (don't rewrite stack functionality)
  - Can add new features to existing classes
  - Maintains compatibility (can still use as std::stack)

In this exercise:
  - MutantStack inherits from std::stack<T>
  - Gets all std::stack methods for free
  - We add begin(), end(), rbegin(), rend() iterators


========================================================================
5. ADDING ITERATORS TO STD::STACK
========================================================================

The key insight: std::stack uses std::deque internally.

std::stack has a protected member: c (the underlying container)
  - c is the std::deque that stores the elements
  - It's protected, so derived classes can access it
  - std::deque HAS iterators!

Solution:
  class MutantStack : public std::stack<T>
  {
  public:
      typedef typename std::deque<T>::iterator iterator;

      iterator begin() { return this->c.begin(); }
      iterator end() { return this->c.end(); }
  };

Now we can iterate:
  MutantStack<int> ms;
  ms.push(1);
  ms.push(2);

  MutantStack<int>::iterator it = ms.begin();
  while (it != ms.end())
  {
      std::cout << *it << std::endl;
      ++it;
  }

We can also add:
  - const_iterator (for const MutantStack)
  - reverse_iterator (for reverse traversal)
  - const_reverse_iterator (for const reverse traversal)


========================================================================
6. FILE-BY-FILE EXPLANATION
========================================================================

--- MutantStack.hpp ---

  This file defines the MutantStack class template.

  Class declaration:
    template <typename T>
    class MutantStack : public std::stack<T>

  Public:
    - Default constructor
    - Copy constructor
    - Destructor
    - Assignment operator

  Type aliases (typedefs):
    - iterator: std::deque<T>::iterator
    - const_iterator: std::deque<T>::const_iterator
    - reverse_iterator: std::deque<T>::reverse_iterator
    - const_reverse_iterator: std::deque<T>::const_reverse_iterator

  Iterator methods:
    - begin(): returns iterator to first element
    - end(): returns iterator past last element
    - rbegin(): returns reverse iterator to last element
    - rend(): returns reverse iterator past first element
    - const versions of all above

  Note: This is a header-only implementation (all in .hpp)
  because it's a template class.

--- main.cpp ---

  This file tests the MutantStack class.

  Tests:
    1. Basic push/pop/top operations
    2. Iterator traversal (forward)
    3. Copy to std::stack
    4. Const iterator
    5. Reverse iterator
    6. String MutantStack (different type)
    7. Assignment operator

  The test matches the subject's example code.


========================================================================
7. HOW TO COMPILE AND RUN
========================================================================

Open a terminal and navigate to the ex02 directory.

  Step 1: Compile
    Type: make
    This creates an executable called "ex02".

  Step 2: Run
    Type: ./ex02

  Other commands:
    make clean   -> Removes .o files
    make fclean  -> Removes .o files and executable
    make re      -> Full rebuild


========================================================================
8. WHAT YOU WILL SEE WHEN YOU RUN IT
========================================================================

Example output:

  === Test 1: Basic MutantStack operations ===
  Top: 17
  Size after pop: 1

  === Test 2: Iterator traversal ===
  5
  3
  5
  737
  0

  === Test 3: Copy to std::stack ===
  Copy size: 5

  === Test 4: Const iterator ===
  5
  3
  5
  737
  0

  === Test 5: Reverse iterator ===
  0
  737
  5
  3
  5

  === Test 6: String MutantStack ===
  Hello
  World
  Templates

  === Test 7: Assignment operator ===
  5
  3
  5
  737
  0


========================================================================
9. COMMON MISTAKES AND TIPS
========================================================================

  1. Not inheriting from std::stack
     - Must be: class MutantStack : public std::stack<T>
     - Not a standalone stack implementation

  2. Not accessing the underlying container
     - Must use this->c to access the deque
     - c is protected in std::stack

  3. Forgetting typedefs for iterators
     - Must define iterator, const_iterator, etc.
     - Use typename std::deque<T>::iterator

  4. Not implementing all iterator operations
     - begin(), end() are required
     - rbegin(), rend() are nice to have
     - const versions needed for const objects

  5. Not testing with different types
     - Must work with int, string, etc.
     - Template must be generic

  6. Not matching the subject's example
     - The subject provides specific test code
     - Your output should match exactly

  7. Using C++11 features
     - This exercise uses C++98 standard
     - No auto, no range-based for, no nullptr

  8. Not providing Orthodox Canonical Form
     - Must have copy constructor and assignment operator
     - Must handle deep copy correctly

========================================================================