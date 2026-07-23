========================================================================
  EXERCISE 00: Start with a few functions
========================================================================

TABLE OF CONTENTS
-----------------
  1. What is this exercise about?
  2. What are templates?
  3. Function templates
  4. How templates work
  5. File-by-file explanation
  6. How to compile and run
  7. What you will see when you run it
  8. Common mistakes and tips


========================================================================
1. WHAT IS THIS EXERCISE ABOUT?
========================================================================

This exercise teaches you about C++ function templates. You need to
create three function templates: swap, min, and max.

The program must:
  - Create a swap() function that exchanges two values
  - Create a min() function that returns the smaller value
  - Create a max() function that returns the larger value
  - All functions must work with any type (int, float, string, etc.)
  - The two arguments must have the same type


========================================================================
2. WHAT ARE TEMPLATES?
========================================================================

Templates allow you to write code that works with ANY type.
Instead of writing separate functions for int, float, string, etc.,
you write ONE template that works for all.

Without templates:
  int minInt(int a, int b) { return (a < b ? a : b); }
  float minFloat(float a, float b) { return (a < b ? a : b); }
  // ...and so on for every type!

With templates:
  template <typename T>
  T min(T a, T b) { return (a < b ? a : b); }

The compiler automatically generates the right version for each type.

Why are templates useful?
  - Write code once, use it with any type
  - Type-safe (compiler checks types at compile time)
  - No runtime overhead (same performance as manual writing)


========================================================================
3. FUNCTION TEMPLATES
========================================================================

A function template is a blueprint for creating functions.

Syntax:
  template <typename T>
  returnType functionName(parameters)
  {
      // Use T as a type
  }

Example:
  template <typename T>
  void swap(T &a, T &b)
  {
      T tmp = a;
      a = b;
      b = tmp;
  }

How to call:
  int x = 1, y = 2;
  swap(x, y);         // Compiler generates swap<int>

  float f1 = 1.5f, f2 = 2.5f;
  swap(f1, f2);       // Compiler generates swap<float>

The <typename T> part:
  - T is a placeholder for a type
  - You can name it anything (T is conventional)
  - You can have multiple template parameters:
    template <typename T, typename U>

In this exercise:
  - swap(T &a, T &b)  - Swaps two values
  - min(T a, T b)     - Returns the smaller value
  - max(T a, T b)     - Returns the larger value

Note: min and max take parameters by value (not reference).
This means they work with types that don't support copying
by reference (though most do).


========================================================================
4. HOW TEMPLATES WORK
========================================================================

When you write:
  template <typename T>
  T min(T a, T b)
  {
      return (a < b ? a : b);
  }

And call:
  int result = min(42, 10);

The compiler does this:
  1. Sees you're calling min with two ints
  2. Generates a specific version: int min(int a, int b)
  3. Compiles that version
  4. Calls it

This is called "template instantiation". The compiler creates
the actual function code for each type you use.

If you then call:
  float f = min(3.14f, 2.71f);

The compiler generates ANOTHER version: float min(float a, float b)

Each type gets its own version of the function.


========================================================================
5. FILE-BY-FILE EXPLANATION
========================================================================

--- whatever.hpp ---

  This file contains all three function templates.

  swap(T &a, T &b):
    - Takes two references to T
    - Swaps their values using a temporary variable
    - Returns nothing (void)

  min(T a, T b):
    - Takes two values of type T
    - Returns the smaller one
    - If equal, returns the second one

  max(T a, T b):
    - Takes two values of type T
    - Returns the larger one
    - If equal, returns the second one

  Note: These are in a header file because templates must be
  defined where they are used (the compiler needs to see the
  full definition to generate the code).

--- main.cpp ---

  This file tests the templates with different types.

  Tests:
    1. Integer swap, min, max
    2. String swap, min, max

  The output matches the subject's expected output.


========================================================================
6. HOW TO COMPILE AND RUN
========================================================================

Open a terminal and navigate to the ex00 directory.

  Step 1: Compile
    Type: make
    This creates an executable called "whatever".

  Step 2: Run
    Type: ./whatever

  Other commands:
    make clean   -> Removes .o files
    make fclean  -> Removes .o files and executable
    make re      -> Full rebuild


========================================================================
7. WHAT YOU WILL SEE WHEN YOU RUN IT
========================================================================

Example output:

  a = 3, b = 2
  min( a, b ) = 2
  max( a, b ) = 3
  c = chaine2, d = chaine1
  min( c, d ) = chaine1
  max( c, d ) = chaine2

This matches the subject's expected output exactly.


========================================================================
8. COMMON MISTAKES AND TIPS
========================================================================

  1. Putting template implementation in .cpp file
     - Templates MUST be defined in header files
     - The compiler needs to see the full definition
     - Otherwise, you get linker errors

  2. Forgetting the template keyword
     - Must have: template <typename T>
     - Without it, the compiler doesn't know it's a template

  3. Wrong parameter types for swap
     - Must use references: T &a, T &b
     - Without references, you only swap local copies

  4. Using namespace std
     - Forbidden in this project
     - Use std:: prefix instead

  5. Not using the :: prefix when calling
     - The subject calls: ::swap(a, b)
     - This ensures you call YOUR function, not std::swap

  6. Forgetting that min/max return second when equal
     - Subject: "If they are equal, it returns the second one"
     - Make sure your comparison handles this correctly

========================================================================