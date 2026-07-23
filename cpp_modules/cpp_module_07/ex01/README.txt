========================================================================
  EXERCISE 01: Iter
========================================================================

TABLE OF CONTENTS
-----------------
  1. What is this exercise about?
  2. What is iter?
  3. Function pointers
  4. Template functions as parameters
  5. Const vs non-const
  6. File-by-file explanation
  7. How to compile and run
  8. What you will see when you run it
  9. Common mistakes and tips


========================================================================
1. WHAT IS THIS EXERCISE ABOUT?
========================================================================

This exercise teaches you about function templates, function pointers,
and how to apply functions to arrays. You need to create an iter()
function template that applies a function to every element of an array.

The program must:
  - Create a function template iter() that takes 3 parameters
  - The first parameter is an array (pointer to first element)
  - The second parameter is the array length (const)
  - The third parameter is a function to apply to each element
  - The iter() function must work with any type of array
  - The function parameter must work with both const and non-const


========================================================================
2. WHAT IS ITER?
========================================================================

The name "iter" comes from "iterate" - to repeat over each element.

iter(array, length, function)
  - Takes an array (pointer to first element)
  - Takes the number of elements
  - Takes a function to call on each element
  - Calls that function on every element in the array

Example:
  void print(int &x) { std::cout << x << " "; }

  int arr[] = {1, 2, 3, 4, 5};
  iter(arr, 5, print);
  Output: 1 2 3 4 5

This is similar to what modern languages call "forEach" or "map".

Why is this useful?
  - You can apply any operation to an array
  - The operation is defined separately (separation of concerns)
  - You can reuse the same iter() with different functions


========================================================================
3. FUNCTION POINTERS
========================================================================

A function pointer is a variable that stores the address of a function.

Syntax:
  returnType (*pointerName)(parameterTypes)

Example:
  void print(int &x) { std::cout << x; }

  void (*fp)(int &) = &print;  // fp points to print
  fp(x);                        // Calls print(x)

In iter(), the third parameter is a function pointer:
  template <typename T>
  void iter(T *array, int length, void (*f)(T &))

  - f is a function that takes T& and returns void
  - iter() calls f on each element

You can also use the shorthand:
  void iter(T *array, int length, void f(T &))
  // The (*f) and f are equivalent in function parameters


========================================================================
4. TEMPLATE FUNCTIONS AS PARAMETERS
========================================================================

The function passed to iter() can be a template function itself.

Example:
  template <typename T>
  void print(T &elem)
  {
      std::cout << elem << " ";
  }

  int intArr[] = {1, 2, 3};
  iter(intArr, 3, print);  // Compiler generates print<int>

  std::string strArr[] = {"a", "b", "c"};
  iter(strArr, 3, print);  // Compiler generates print<std::string>

The compiler generates the right version of print() for each type.


========================================================================
5. CONST VS NON-CONST
========================================================================

The subject says:
  "The function passed as the third parameter may take its argument
   by const reference or non-const reference, depending on the context."

This means iter() must handle both cases:
  - void f(T &elem)       - Non-const reference (can modify)
  - void f(const T &elem) - Const reference (cannot modify)

Solution: Provide TWO versions of iter():
  template <typename T>
  void iter(T *array, int length, void (*f)(T &))

  template <typename T>
  void iter(const T *array, int length, void (*f)(const T &))

This allows:
  - Non-const arrays with non-const functions
  - Const arrays with const functions
  - Any combination that makes sense


========================================================================
6. FILE-BY-FILE EXPLANATION
========================================================================

--- iter.hpp ---

  This file contains the iter() function template.

  Two versions:
    1. For non-const arrays:
       void iter(T *array, int length, void (*f)(T &))
       - Takes a non-const pointer
       - Calls f with non-const reference

    2. For const arrays:
       void iter(const T *array, int length, void (*f)(const T &))
       - Takes a const pointer
       - Calls f with const reference

  Both versions:
    - Loop through the array
    - Call f on each element
    - Return nothing (void)

--- main.cpp ---

  This file tests the iter() function template.

  Helper functions:
    - printElement() - Prints an element followed by a space
    - multiplyByTwo() - Multiplies an integer by 2
    - toUpperCase() - Converts a char to uppercase

  Tests:
    1. Integer array with printElement
    2. Integer array with multiplyByTwo (modification)
    3. String array with printElement
    4. Char array with toUpperCase (modification)
    5. Double array with printElement
    6. Const integer array with printElement


========================================================================
7. HOW TO COMPILE AND RUN
========================================================================

Open a terminal and navigate to the ex01 directory.

  Step 1: Compile
    Type: make
    This creates an executable called "iter".

  Step 2: Run
    Type: ./iter

  Other commands:
    make clean   -> Removes .o files
    make fclean  -> Removes .o files and executable
    make re      -> Full rebuild


========================================================================
8. WHAT YOU WILL SEE WHEN YOU RUN IT
========================================================================

Example output:

  === Test 1: Integer array ===
  Original: 1 2 3 4 5
  After multiplyByTwo: 2 4 6 8 10

  === Test 2: String array ===
  Original: hello world templates

  === Test 3: Char array ===
  Original: h e l l o
  After toUpperCase: H E L L O

  === Test 4: Double array ===
  Original: 1.1 2.2 3.3

  === Test 5: Const array ===
  Const array: 10 20 30


========================================================================
9. COMMON MISTAKES AND TIPS
========================================================================

  1. Only providing one version of iter()
     - Need TWO versions: one for non-const, one for const
     - Otherwise, const arrays won't work

  2. Forgetting the template keyword
     - Must have: template <typename T>
     - Without it, T is not defined

  3. Wrong function pointer syntax
     - Must be: void (*f)(T &)
     - Not: void *f(T &) (that's a function returning void*)

  4. Not using const for the length parameter
     - Subject says: "passed as a const value"
     - Use: int length (const is implicit for value parameters)
     - Or: const int length

  5. Forgetting to include the template in the header
     - Templates must be defined in header files
     - Otherwise, linker errors occur

  6. Using C++11 features
     - This exercise uses C++98 standard
     - No lambdas, no auto, no range-based for

========================================================================