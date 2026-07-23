========================================================================
  EXERCISE 00: Conversion of scalar types
========================================================================

TABLE OF CONTENTS
-----------------
  1. What is this exercise about?
  2. What are C++ casts?
  3. What is a ScalarConverter?
  4. Type detection logic
  5. Conversion rules
  6. File-by-file explanation
  7. How to compile and run
  8. What you will see when you run it
  9. Common mistakes and tips


========================================================================
1. WHAT IS THIS EXERCISE ABOUT?
========================================================================

This exercise teaches you about C++ type casting. You need to create
a class called "ScalarConverter" that can convert a string literal
to different scalar types: char, int, float, and double.

The program must:
  - Detect the type of the input string (char, int, float, or double)
  - Convert the string to that type
  - Convert it to all other types
  - Display the results


========================================================================
2. WHAT ARE C++ CASTS?
========================================================================

C++ has 4 types of casts:

  1. static_cast<type>(value)
     - The most common cast
     - Used for compile-time type conversions
     - Example: static_cast<int>(3.14) gives 3

  2. dynamic_cast<type>(value)
     - Used for runtime type checking in inheritance
     - Requires polymorphic classes (with virtual functions)

  3. const_cast<type>(value)
     - Used to add or remove const
     - Example: const_cast<char*>(constStr)

  4. reinterpret_cast<type>(value)
     - Used for low-level reinterpreting of bits
     - Example: reinterpret_cast<int*>(ptr)

In this exercise, we use static_cast for most conversions.


========================================================================
3. WHAT IS A SCALARCONVERTER?
========================================================================

ScalarConverter is a class that:
  - Cannot be instantiated (you cannot create objects from it)
  - Has only static methods
  - Contains one main method: convert()

The convert() method:
  1. Takes a string as input
  2. Detects what type the string represents
  3. Converts it to that type
  4. Converts it to all other scalar types
  5. Prints the results

Example:
  Input: "42"
  Output:
    char: '*'     (ASCII 42)
    int: 42
    float: 42.0f
    double: 42.0


========================================================================
4. TYPE DETECTION LOGIC
========================================================================

The class must detect which type the input string represents:

  CHAR:
    - Single character that is printable
    - Examples: 'c', 'a', 'Z'
    - NOT digits (0-9 are not char literals)

  INT:
    - Optional sign (+ or -) followed by digits
    - Examples: 0, -42, 42, +100

  FLOAT:
    - Decimal number ending with 'f'
    - Examples: 0.0f, -4.2f, 4.2f
    - Special: -inff, +inff, nanf

  DOUBLE:
    - Decimal number without 'f'
    - Examples: 0.0, -4.2, 4.2
    - Special: -inf, +inf, nan

Detection order:
  1. Check if it's a char (single printable non-digit)
  2. Check if it's a float (has 'f' at end, has decimal point)
  3. Check if it's a double (has decimal point, no 'f')
  4. Check if it's an integer (optional sign, all digits)
  5. Otherwise, it's impossible to convert


========================================================================
5. CONVERSION RULES
========================================================================

When converting, follow these rules:

  char conversion:
    - If value is not displayable (not in range 32-126)
      => print "Non displayable"
    - If value is out of char range
      => print "impossible"

  int conversion:
    - If value is out of int range
      => print "impossible"

  float conversion:
    - If value is too large for float
      => print "impossible"
    - If value has no decimal part
      => print with ".0f" (e.g., "42.0f")
    - Otherwise
      => print with 'f' suffix

  double conversion:
    - If value has no decimal part
      => print with ".0" (e.g., "42.0")
    - Otherwise
      => print normally

Special values:
  - nan, nanf => "impossible" for char and int
  - +inf, -inf, +inff, -inff => "impossible" for char and int


========================================================================
6. FILE-BY-FILE EXPLANATION
========================================================================

--- ScalarConverter.hpp ---

  This file declares the ScalarConverter class.

  Key points:
    - Private constructor prevents instantiation
    - All methods are static
    - Helper methods for type detection and conversion

--- ScalarConverter.cpp ---

  This file implements the ScalarConverter class.

  Type detection methods:
    isChar()   - Checks if string is a single printable character
    isInt()    - Checks if string is an integer
    isFloat()  - Checks if string is a float (ends with 'f')
    isDouble() - Checks if string is a double

  Conversion methods:
    convertFromChar()   - Converts char to all types
    convertFromInt()    - Converts int to all types
    convertFromFloat()  - Converts float to all types
    convertFromDouble() - Converts double to all types

  Main method:
    convert() - Detects type and calls appropriate converter

--- main.cpp ---

  This file tests the ScalarConverter class.

  It takes a command-line argument and passes it to convert().


========================================================================
7. HOW TO COMPILE AND RUN
========================================================================

Open a terminal and navigate to the ex00 directory.

  Step 1: Compile
    Type: make
    This creates an executable called "convert".

  Step 2: Run
    Type: ./convert <literal>
    Example: ./convert 42

  Other commands:
    make clean   -> Removes .o files
    make fclean  -> Removes .o files and executable
    make re      -> Full rebuild


========================================================================
8. WHAT YOU WILL SEE WHEN YOU RUN IT
========================================================================

Examples:

  $ ./convert 0
  char: Non displayable
  int: 0
  float: 0.0f
  double: 0.0

  $ ./convert nan
  char: impossible
  int: impossible
  float: nanf
  double: nan

  $ ./convert 42.0f
  char: '*'
  int: 42
  float: 42.0f
  double: 42.0

  $ ./convert -42
  char: impossible
  int: -42
  float: -42.0f
  double: -42.0

  $ ./convert a
  char: 'a'
  int: 97
  float: 97.0f
  double: 97.0


========================================================================
9. COMMON MISTAKES AND TIPS
========================================================================

  1. Forgetting to handle special values (nan, inf)
     - These are valid literals and must be handled

  2. Not checking for overflow
     - Values outside type ranges must print "impossible"

  3. Wrong detection order
     - Float must be checked before double (because of 'f' suffix)

  4. Forgetting the '.0' for whole numbers
     - 42 should print as "42.0f" and "42.0", not "42f" and "42"

  5. Not using static methods
     - The class cannot be instantiated, all methods are static

  6. Using C functions like atoi/atof
     - These are allowed in this exercise (see subject)

========================================================================