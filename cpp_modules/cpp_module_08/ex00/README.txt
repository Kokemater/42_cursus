========================================================================
  EXERCISE 00: Easy find
========================================================================

TABLE OF CONTENTS
-----------------
  1. What is this exercise about?
  2. What are STL containers?
  3. What are iterators?
  4. What is std::find?
  5. Function templates
  6. File-by-file explanation
  7. How to compile and run
  8. What you will see when you run it
  9. Common mistakes and tips


========================================================================
1. WHAT IS THIS EXERCISE ABOUT?
========================================================================

This exercise teaches you about STL containers, iterators, and
algorithms. You need to create a function template easyfind that
finds the first occurrence of an integer in a container.

The program must:
  - Create a function template easyfind
  - Accept any container type T (vector, list, deque, etc.)
  - Find the first occurrence of an integer in the container
  - Return an iterator to the found element
  - Throw an exception if not found

Container used: Any STL container (vector, list, deque, etc.)


========================================================================
2. WHAT ARE STL CONTAINERS?
========================================================================

STL containers are data structures that store collections of elements.
The C++ Standard Template Library provides several containers:

  Sequence containers (store elements in order):
    - std::vector    Dynamic array (fast random access)
    - std::list      Doubly-linked list (fast insertion)
    - std::deque     Double-ended queue (fast at both ends)

  Associative containers (store sorted elements):
    - std::set       Sorted unique elements
    - std::map       Sorted key-value pairs
    - std::multiset  Sorted, allows duplicates
    - std::multimap  Sorted, allows duplicate keys

In this exercise, we use sequence containers because:
  - We need to find elements by value
  - We don't need sorting or key-value pairs
  - vector, list, and deque all work with easyfind


========================================================================
3. WHAT ARE ITERATORS?
========================================================================

Iterators are objects that point to elements in a container.
They are like pointers that work with any container type.

Think of them as "cursors" that move through a container:

  std::vector<int> vec;
  vec.push_back(10);
  vec.push_back(20);

  std::vector<int>::iterator it = vec.begin();  // Points to 10
  std::cout << *it;                             // Prints 10
  ++it;                                         // Move to next
  std::cout << *it;                             // Prints 20

Key iterator operations:
  - it++ or ++it    Move to next element
  - it-- or --it    Move to previous element
  - *it             Access the element
  - it == other     Compare iterators
  - it != other     Compare iterators

Iterator types:
  - iterator        Can modify elements
  - const_iterator  Cannot modify elements (read-only)

Every container defines its own iterator type:
  std::vector<int>::iterator
  std::list<int>::iterator
  std::deque<int>::iterator


========================================================================
4. WHAT IS STD::FIND?
========================================================================

std::find is an algorithm from the <algorithm> header that searches
for a value in a range.

Syntax:
  iterator = std::find(begin, end, value);

Parameters:
  - begin: Iterator to the first element
  - end: Iterator past the last element
  - value: The value to search for

Returns:
  - Iterator to the first element equal to value
  - end iterator if value not found

Example:
  std::vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);

  std::vector<int>::iterator it = std::find(vec.begin(), vec.end(), 2);
  if (it != vec.end())
      std::cout << "Found: " << *it;  // Found: 2

Why use std::find?
  - It's the standard way to search in containers
  - Works with any container type
  - Returns an iterator (can get position, modify element, etc.)

In this exercise:
  - We wrap std::find in our easyfind function
  - We add exception handling for not-found case
  - We make it work with any container type (template)


========================================================================
5. FUNCTION TEMPLATES
========================================================================

A function template is a blueprint for creating functions that work
with any type.

Syntax:
  template <typename T>
  returnType functionName(parameters)
  {
      // Use T as a type
  }

In this exercise:
  template <typename T>
  typename T::iterator easyfind(T &container, int value)
  {
      typename T::iterator it = std::find(container.begin(), container.end(), value);
      if (it == container.end())
          throw std::out_of_range("Value not found in container");
      return (it);
  }

Breaking it down:
  - template <typename T>      Template declaration
  - typename T::iterator       Return type (iterator of container T)
  - T &container               Parameter (any container type)
  - int value                  The value to find

We provide TWO versions:
  1. For non-const containers (can modify elements)
  2. For const containers (read-only)


========================================================================
6. FILE-BY-FILE EXPLANATION
========================================================================

--- easyfind.hpp ---

  This file contains the easyfind function template.

  Two versions:
    1. For non-const containers:
       typename T::iterator easyfind(T &container, int value)
       - Returns iterator that can modify elements

    2. For const containers:
       typename T::const_iterator easyfind(const T &container, int value)
       - Returns const_iterator (read-only)

  Both versions:
    - Use std::find to search for the value
    - Throw std::out_of_range if not found
    - Return iterator to the found element

--- main.cpp ---

  This file tests the easyfind function template.

  Tests:
    1. Vector - Find existing value
    2. Vector - Find non-existing value (exception)
    3. List - Find existing value
    4. Deque - Find existing value
    5. Const vector - Find existing value
    6. Find first occurrence (duplicate values)

  Each test:
    - Creates a container with some values
    - Calls easyfind
    - Displays the result or catches the exception


========================================================================
7. HOW TO COMPILE AND RUN
========================================================================

Open a terminal and navigate to the ex00 directory.

  Step 1: Compile
    Type: make
    This creates an executable called "easyfind".

  Step 2: Run
    Type: ./easyfind

  Other commands:
    make clean   -> Removes .o files
    make fclean  -> Removes .o files and executable
    make re      -> Full rebuild


========================================================================
8. WHAT YOU WILL SEE WHEN YOU RUN IT
========================================================================

Example output:

  === Test 1: Vector - Find existing value ===
  Found: 3 at index 2

  === Test 2: Vector - Find non-existing value ===
  Exception: Value not found in container

  === Test 3: List - Find existing value ===
  Found: 20

  === Test 4: Deque - Find existing value ===
  Found: 200

  === Test 5: Const vector ===
  Found: 4

  === Test 6: Find first occurrence ===
  First occurrence: 5 at index 0


========================================================================
9. COMMON MISTAKES AND TIPS
========================================================================

  1. Not using std::find
     - The subject says to use STL algorithms
     - std::find is the standard way to search

  2. Not handling const containers
     - Need two versions of easyfind
     - One for non-const, one for const

  3. Wrong return type
     - Must return typename T::iterator
     - Not T* or int or anything else

  4. Forgetting the exception
     - Subject says "throw an exception or return an error value"
     - Exception is cleaner (std::out_of_range)

  5. Not testing with multiple containers
     - Must test with vector, list, deque
     - Template should work with all sequence containers

  6. Not testing const containers
     - Need to verify const version works
     - Use const_iterator

  7. Forgetting to include <algorithm>
     - std::find is in <algorithm>
     - Without it, you get compilation errors

========================================================================