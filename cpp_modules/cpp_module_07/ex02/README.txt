========================================================================
  EXERCISE 02: Array
========================================================================

TABLE OF CONTENTS
-----------------
  1. What is this exercise about?
  2. What is a class template?
  3. Orthodox Canonical Form
  4. Operator overloading
  5. Exception handling
  6. File-by-file explanation
  7. How to compile and run
  8. What you will see when you run it
  9. Common mistakes and tips


========================================================================
1. WHAT IS THIS EXERCISE ABOUT?
========================================================================

This exercise teaches you about class templates. You need to create
a class template Array that stores elements of any type.

The program must:
  - Create a class template Array<T>
  - Support construction with no parameters (empty array)
  - Support construction with a size parameter
  - Support copy construction and assignment
  - Support subscript operator [] for element access
  - Throw an exception when accessing out-of-bounds elements
  - Provide a size() member function
  - Use new[] for memory allocation (no preventive allocation)


========================================================================
2. WHAT IS A CLASS TEMPLATE?
========================================================================

A class template is a blueprint for creating classes that work
with any type.

Syntax:
  template <typename T>
  class ClassName
  {
      T member;
  };

How to use:
  Array<int> intArr(10);        // Array of 10 ints
  Array<std::string> strArr(5); // Array of 5 strings
  Array<float> floatArr;        // Empty array of floats

The compiler generates a specific class for each type:
  - Array<int> with int elements
  - Array<std::string> with string elements
  - etc.

Why are class templates useful?
  - Write code once, use it with any type
  - Type-safe (compiler checks types)
  - Can store multiple values of the same type
  - Can have methods that work with the stored type


========================================================================
3. ORTHODOX CANONICAL FORM
========================================================================

The subject says classes must follow Orthodox Canonical Form (OCF).
This means 4 special member functions:

  1. Default Constructor
     Array(void) - Creates an empty array

  2. Copy Constructor
     Array(const Array &src) - Creates a copy of another array

  3. Copy Assignment Operator
     Array &operator=(const Array &rhs) - Copies data from another array

  4. Destructor
     ~Array(void) - Cleans up allocated memory

Important rules for OCF:
  - Copy constructor must do DEEP copy (allocate new memory)
  - Assignment operator must do DEEP copy
  - Destructor must free allocated memory
  - Modifications to copy must NOT affect original (and vice versa)


========================================================================
4. OPERATOR OVERLOADING
========================================================================

Operator overloading lets you define how operators work for your class.

In this exercise, we overload:
  - operator[] (subscript operator)
  - operator= (assignment operator)

operator[]:
  T &operator[](int index)
  {
      if (index out of bounds)
          throw exception;
      return elements[index];
  }

  This lets you do: arr[0], arr[1], etc.

  Must provide TWO versions:
    1. T &operator[](int index)       - For non-const arrays
    2. const T &operator[](int index) const - For const arrays

operator=:
  Array &operator=(const Array &rhs)
  {
      if (this != &rhs)  // Check for self-assignment
      {
          // Free old memory
          // Allocate new memory
          // Copy elements
      }
      return *this;
  }

  This lets you do: arr1 = arr2;


========================================================================
5. EXCEPTION HANDLING
========================================================================

When accessing an element with [], if the index is out of bounds,
you must throw an std::exception.

Throwing:
  if (index < 0 || index >= size)
      throw std::out_of_range("Index out of bounds");

Catching:
  try
  {
      int x = arr[10];
  }
  catch (std::out_of_range &e)
  {
      std::cout << e.what() << std::endl;
  }

std::out_of_range is derived from std::exception, so you can
catch either one.

Why throw instead of returning an error?
  - C++ convention for error handling
  - Forces the caller to handle errors
  - Prevents using invalid data


========================================================================
6. FILE-BY-FILE EXPLANATION
========================================================================

--- Array.hpp ---

  This file declares the Array class template.

  Key points:
    - Template declaration: template <typename T>
    - Member variables: _elements (T*), _size (int)
    - All OCF functions declared
    - operator[] declared (const and non-const versions)
    - size() function declared

  Note: Includes Array.tpp at the end (template implementation)

--- Array.tpp ---

  This file implements the Array class template methods.

  Why .tpp file?
    - Template implementations must be in header files
    - But putting everything in .hpp makes it hard to read
    - .tpp is a convention for template implementations
    - It's included at the end of Array.hpp

  Methods implemented:
    - Default constructor: creates empty array (NULL, size 0)
    - Size constructor: creates array of n elements (default-initialized)
    - Copy constructor: deep copy of another array
    - Assignment operator: deep copy with self-assignment check
    - Destructor: frees allocated memory
    - operator[] (non-const): returns reference, throws on bounds
    - operator[] (const): returns const reference, throws on bounds
    - size(): returns the size

--- main.cpp ---

  This file tests the Array class template.

  Tests:
    1. Default constructor (empty array)
    2. Constructor with size
    3. Modify elements
    4. Copy constructor
    5. Assignment operator
    6. Verify copies are independent
    7. Index out of bounds exception
    8. String array
    9. Const array


========================================================================
7. HOW TO COMPILE AND RUN
========================================================================

Open a terminal and navigate to the ex02 directory.

  Step 1: Compile
    Type: make
    This creates an executable called "array".

  Step 2: Run
    Type: ./array

  Other commands:
    make clean   -> Removes .o files
    make fclean  -> Removes .o files and executable
    make re      -> Full rebuild


========================================================================
8. WHAT YOU WILL SEE WHEN YOU RUN IT
========================================================================

Example output:

  === Test 1: Default constructor (empty array) ===
  Size: 0

  === Test 2: Constructor with size ===
  Size: 5
  Elements: 0 0 0 0 0

  === Test 3: Modify elements ===
  Modified: 10 20 30 40 50

  === Test 4: Copy constructor ===
  Original: 10 20 30 40 50
  Copy: 10 20 30 40 50

  === Test 5: Assignment operator ===
  Original: 10 20 30 40 50
  Assigned: 10 20 30 40 50

  === Test 6: Modify copy doesn't affect original ===
  Original[0]: 10
  Copy[0]: 999

  === Test 7: Index out of bounds ===
  Exception: Index out of bounds
  Exception: Index out of bounds

  === Test 8: String array ===
  Strings: Hello World Templates

  === Test 9: Const array ===
  Const array: 10 20 30 40 50


========================================================================
9. COMMON MISTAKES AND TIPS
========================================================================

  1. Not doing deep copy
     - Shallow copy shares memory (dangerous!)
     - Must allocate new memory and copy elements

  2. Forgetting self-assignment check
     - Without it: a = a; causes undefined behavior
     - Always check: if (this != &rhs)

  3. Not freeing old memory in assignment
     - Memory leak if you don't delete[] _elements first

  4. Wrong new[] syntax
     - Must use: new T[n]()
     - The () initializes elements to default values
     - Without (): elements are uninitialized (garbage)

  5. Forgetting const version of operator[]
     - Const arrays need const operator[]
     - Otherwise, you can't read elements from const arrays

  6. Not throwing on out-of-bounds
     - Subject requires: "an std::exception is thrown"
     - Use std::out_of_range for better error messages

  7. Using the wrong index type
     - Subject says: "unsigned int n as a parameter"
     - But operator[] should take int (for negative index check)
     - Or use size_t and check for overflow

  8. Putting .tpp in wrong place
     - Include .tpp at the END of .hpp (after class declaration)
     - Not at the beginning

========================================================================