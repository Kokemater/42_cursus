========================================================================
  EXERCISE 00: Mommy, when I grow up, I want to be a bureaucrat!
========================================================================

TABLE OF CONTENTS
-----------------
  1. What is this exercise about?
  2. C++ Basics (for people who know nothing)
  3. What is a "class"?
  4. What is the Bureaucrat class?
  5. How does the grade system work?
  6. What are exceptions?
  7. What is the Orthodox Canonical Form?
  8. File-by-file explanation
  9. How to compile and run
  10. What you will see when you run it
  11. Common mistakes and tips


========================================================================
1. WHAT IS THIS EXERCISE ABOUT?
========================================================================

This exercise simulates a silly government office (a "bureaucracy").
You create a class called "Bureaucrat" -- imagine a person who works
in an office and has a rank (grade). The higher their rank (lower
number), the more important they are.

For example:
  - Grade 1  = The boss (very important!)
  - Grade 150 = The lowest intern (not important at all)

The program must:
  - Let you create bureaucrats with a name and grade
  - Prevent invalid grades (nothing below 1, nothing above 150)
  - Let you promote (increment) or demote (decrement) a bureaucrat
  - Print the bureaucrat's info to the screen


========================================================================
2. C++ BASICS (FOR PEOPLE WHO KNOW NOTHING)
========================================================================

If you have never seen C++ before, here is a quick crash course:

--- What is C++? ---
C++ is a programming language. You write code in text files, then a
"compiler" turns that code into a program you can run.

--- What is a ".hpp" file? ---
A .hpp file is a HEADER file. Think of it as a "blueprint" or "menu".
It declares what a class looks like (its ingredients) but does NOT
contain the actual recipe (the code that makes it work).

Example of a .hpp file:
  class Dog
  {
  public:                          // Anyone can use these
      void bark();                 // This method makes the dog bark
      int getAge();                // This method returns the dog's age
  private:                         // Only the class itself can use these
      std::string name;            // The dog's name (stored inside)
      int age;                     // The dog's age (stored inside)
  };

--- What is a ".cpp" file? ---
A .cpp file is where the actual code lives. It implements (writes the
recipe for) the methods declared in the .hpp file.

Example of a .cpp file:
  void Dog::bark()
  {
      std::cout << "Woof!" << std::endl;
  }

--- What is "main"? ---
Every C++ program needs a main() function. It is the starting point.
When you run the program, the computer starts executing code from
main().

--- What is "std::cout"? ---
std::cout is how you print text to the screen.
  std::cout << "Hello!" << std::endl;
This prints "Hello!" and then moves to a new line.

--- What is "#include"? ---
#include is like telling the compiler: "Go get that file and pretend
it is part of mine." For example:
  #include <iostream>    // Gives you std::cout (printing)
  #include <string>      // Gives you std::string (text)
  #include <stdexcept>   // Gives you exception handling

--- What is "const"? ---
const means "constant" or "unchangeable". If you declare something
as const, you CANNOT modify it later. For example:
  const std::string name = "Bob";
  name = "Alice";   // ERROR! You cannot change a const value!

--- What is a "reference" (&)? ---
A reference is an alias for an existing variable. Instead of creating
a copy, you work with the original. For example:
  void printName(const std::string &name)
This function receives a reference to a string. The "const" means
it promises not to change it.

--- What is "private" vs "public"? ---
  - public: Anyone outside the class can access these members.
  - private: ONLY the class itself can access these members.

This is called "encapsulation" -- you hide the internal data and
only expose what is necessary through public methods.

--- What is "void"? ---
void means "returns nothing". A function declared as void does not
give back any value when it finishes.

--- What is "int"? ---
int means "integer" -- a whole number like 1, 42, -7, 150, etc.


========================================================================
3. WHAT IS A "CLASS"?
========================================================================

A class is a BLUEPRINT for creating objects. Think of it like this:

  - A CLASS is like a cookie cutter (the mold).
  - An OBJECT is like the cookie made from that mold.

You define the class once, then you can create as many objects
from it as you want.

In this exercise, the class is called "Bureaucrat". Every bureaucrat
has:
  - A name (like "Bob" or "Alice")
  - A grade (a number from 1 to 150)

Here is a simplified version of what the class looks like:

  class Bureaucrat
  {
  public:
      // These are things anyone can call:
      const std::string &getName() const;   // Get the name
      int getGrade() const;                 // Get the grade
      void increment();                     // Promote (grade goes down by 1)
      void decrement();                     // Demote (grade goes up by 1)

  private:
      // These are hidden inside the class:
      const std::string _name;   // The bureaucrat's name (cannot change)
      int _grade;                // The bureaucrat's grade (can change)
  };

The underscore prefix (like _name, _grade) is a convention used in
this project to indicate that these are private member variables.


========================================================================
4. WHAT IS THE BUREAUCRAT CLASS?
========================================================================

The Bureaucrat class represents a person in a bureaucracy with:

  ATTRIBUTES (data stored inside the object):
  ┌─────────────────────────┬────────────────────────────────────┐
  │ Attribute               │ Description                        │
  ├─────────────────────────┼────────────────────────────────────┤
  │ _name (const string)    │ The bureaucrat's name. Once set,   │
  │                         │ it CANNOT be changed (it's const). │
  ├─────────────────────────┼────────────────────────────────────┤
  │ _grade (int)            │ The bureaucrat's rank, from 1 to   │
  │                         │ 150. Grade 1 is highest, 150 is    │
  │                         │ lowest. This CAN change.           │
  └─────────────────────────┴────────────────────────────────────┘

  METHODS (functions the object can perform):
  ┌─────────────────────┬────────────────────────────────────────┐
  │ Method              │ Description                            │
  ├─────────────────────┼────────────────────────────────────────┤
  │ getName()           │ Returns the bureaucrat's name.         │
  │                     │ Returns a const reference (no copy).   │
  ├─────────────────────┼────────────────────────────────────────┤
  │ getGrade()          │ Returns the bureaucrat's grade.        │
  ├─────────────────────┼────────────────────────────────────────┤
  │ increment()         │ Promotes the bureaucrat by 1.          │
  │                     │ Grade 3 becomes 2, 2 becomes 1, etc.  │
  │                     │ If already at 1, throws an exception.  │
  ├─────────────────────┼────────────────────────────────────────┤
  │ decrement()         │ Demotes the bureaucrat by 1.           │
  │                     │ Grade 148 becomes 149, 149 becomes     │
  │                     │ 150, etc. If already at 150, throws.   │
  └─────────────────────┴────────────────────────────────────────┘

  CONSTRUCTORS (ways to create a Bureaucrat):
  ┌───────────────────────────────┬──────────────────────────────┐
  │ Constructor                   │ What it does                 │
  ├───────────────────────────────┼──────────────────────────────┤
  │ Bureaucrat()                  │ Default: name="default",     │
  │                               │ grade=150 (lowest rank).     │
  ├───────────────────────────────┼──────────────────────────────┤
  │ Bureaucrat(name, grade)       │ Creates with given name and  │
  │                               │ grade. Validates the grade!  │
  ├───────────────────────────────┼──────────────────────────────┤
  │ Bureaucrat(const Bureaucrat&) │ Copy constructor: creates a  │
  │                               │ new bureaucrat that is an    │
  │                               │ exact copy of another one.   │
  └───────────────────────────────┴──────────────────────────────┘

  OPERATOR OVERLOAD:
  The << operator is overloaded so you can print a Bureaucrat like:
    std::cout << bob << std::endl;
  Output: "Bob, bureaucrat grade 42."


========================================================================
5. HOW DOES THE GRADE SYSTEM WORK?
========================================================================

IMPORTANT: The numbering is COUNTER-INTUITIVE!

  Grade 1  = HIGHEST rank (the boss, very powerful)
  Grade 150 = LOWEST rank (the intern, not powerful at all)

  - increment() DECREASES the grade number (e.g., 3 -> 2)
    This is a PROMOTION -- you become more important.

  - decrement() INCREASES the grade number (e.g., 2 -> 3)
    This is a DEMOTION -- you become less important.

Think of it like military ranks:
  - A general has a low number (high rank)
  - A private has a higher number (low rank)

The valid range is ALWAYS 1 to 150 (inclusive on both ends).

  ┌──────────────────────────────────────────────────────────┐
  │  INVALID:  grade < 1  or  grade > 150                   │
  │  VALID:    grade >= 1  AND  grade <= 150                 │
  └──────────────────────────────────────────────────────────┘


========================================================================
6. WHAT ARE EXCEPTIONS?
========================================================================

An exception is a way to HANDLE ERRORS. Instead of crashing the
program, you "throw" an exception, and somewhere else you "catch" it.

Think of it like a fire alarm:
  - When there is a fire, you PUSH the alarm (throw).
  - Someone else HEARS the alarm and responds (catch).

In C++, exceptions work like this:

  // THROWING (inside a function):
  if (grade < 1)
      throw GradeTooHighException();    // "We have a problem!"

  // CATCHING (outside the function):
  try
  {
      Bureaucrat bob("Bob", 0);    // This will throw!
  }
  catch (std::exception &e)         // This catches the problem
  {
      std::cout << "Error: " << e.what() << std::endl;
  }

The Bureaucrat class defines TWO custom exception classes:

  1. GradeTooHighException
     - Thrown when someone tries to set a grade BELOW 1
     - Also thrown when incrementing grade 1 (can't go higher)
     - Message: "grade too high"

  2. GradeTooLowException
     - Thrown when someone tries to set a grade ABOVE 150
     - Also thrown when decrementing grade 150 (can't go lower)
     - Message: "grade too low"

These exceptions are defined INSIDE the Bureaucrat class itself
(they are "nested classes"). This is a common C++ pattern.

The "what()" method returns a human-readable error message.
The "throw()" after the method signature means this function
promises to NEVER throw its own exception.


========================================================================
7. WHAT IS THE ORTHODOX CANONICAL FORM?
========================================================================

The Orthodox Canonical Form (OCF) is a rule in C++ that says every
class MUST have these 4 special member functions:

  1. Default Constructor
     - Called when you create an object without arguments:
         Bureaucrat a;
     - Sets default values (name="default", grade=150)

  2. Copy Constructor
     - Called when you create a new object FROM an existing one:
         Bureaucrat b(a);    // b is a copy of a
     - Makes a new object with the same data

  3. Copy Assignment Operator
     - Called when you copy data FROM one existing object to another:
         Bureaucrat c("Leo", 100);
         c = b;              // c now has b's data
     - Note: c already existed, we are just updating its data

  4. Destructor
     - Called automatically when an object goes out of scope or is
       deleted. Used to clean up resources.
     - In this exercise, there is nothing to clean up, so it is empty.

Why is this important?
  In C++, when you create copies of objects, you need to be careful
  about HOW they are copied. The Orthodox Canonical Form ensures
  your class behaves correctly when copied or destroyed.

IMPORTANT NOTE: The _name is const (cannot change), so:
  - The copy constructor COPIES the name into the new object
  - The copy assignment operator CANNOT change the name (it is const),
    so it only copies the grade

  Bureaucrat &operator=(const Bureaucrat &rhs)
  {
      if (this != &rhs)               // Don't copy yourself!
          this->_grade = rhs._grade;  // Only grade can change
      return (*this);
  }


========================================================================
8. FILE-BY-FILE EXPLANATION
========================================================================

--- Bureaucrat.hpp (the blueprint file) ---

  This file declares what the Bureaucrat class looks like.

  Line by line:
    #ifndef BUREAUCRAT_HPP          // "If this flag is not set..."
    # define BUREAUCRAT_HPP          // "...set it now." (prevents
                                     //  including this file twice)

    # include <iostream>             // Needed for printing (cout)
    # include <string>               // Needed for std::string
    # include <stdexcept>            // Needed for exception handling

    class Bureaucrat                 // Start defining the class
    {
    public:                          // Everything below is public
        Bureaucrat(void);            // Default constructor
        Bureaucrat(const std::string &name, int grade);  // Parameterized
        Bureaucrat(const Bureaucrat &src);               // Copy constructor
        ~Bureaucrat(void);           // Destructor (the ~ means destructor)

        Bureaucrat &operator=(const Bureaucrat &rhs);    // Assignment operator

        const std::string &getName() const;  // Get name (const = won't change anything)
        int getGrade() const;                // Get grade

        void increment();   // Promote by 1
        void decrement();   // Demote by 1

        // Nested exception classes:
        class GradeTooHighException : public std::exception
        {
        public:
            virtual const char *what() const throw();
        };

        class GradeTooLowException : public std::exception
        {
        public:
            virtual const char *what() const throw();
        };

    private:                         // Everything below is private
        const std::string _name;     // Name (const = unchangeable)
        int _grade;                  // Grade (can change)
    };

    // This lets you do: std::cout << myBureaucrat;
    std::ostream &operator<<(std::ostream &o, const Bureaucrat &rhs);

    #endif                          // End of include guard


--- Bureaucrat.cpp (the implementation file) ---

  This file contains the actual code for each method.

  Default Constructor:
    Bureaucrat::Bureaucrat(void) : _name("default"), _grade(150)
    {
    }
    - Uses "initializer list" (the : part) to set _name and _grade
    - _name is "default", _grade is 150 (lowest rank)
    - The { } is empty because there is nothing else to do

  Parameterized Constructor:
    Bureaucrat::Bureaucrat(const std::string &name, int grade)
        : _name(name), _grade(grade)
    {
        if (grade < 1)
            throw Bureaucrat::GradeTooHighException();
        if (grade > 150)
            throw Bureaucrat::GradeTooLowException();
    }
    - Sets _name to the provided name
    - Sets _grade to the provided grade
    - VALIDATES the grade: if invalid, throws an exception
    - Important: The name is set FIRST (initializer list order),
      then the grade is validated in the body

  Copy Constructor:
    Bureaucrat::Bureaucrat(const Bureaucrat &src)
        : _name(src._name), _grade(src._grade)
    {
    }
    - Creates a new Bureaucrat that is an exact copy of src
    - Copies both name and grade from the source

  Destructor:
    Bureaucrat::~Bureaucrat(void)
    {
    }
    - Empty because there is nothing to clean up (no dynamically
      allocated memory, no files opened, etc.)

  Assignment Operator:
    Bureaucrat &Bureaucrat::operator=(const Bureaucrat &rhs)
    {
        if (this != &rhs)               // Guard against self-assignment
            this->_grade = rhs._grade;  // Copy only the grade
        return (*this);                  // Return reference to self
    }
    - Note: Cannot copy _name because it is const
    - "this" is a pointer to the current object
    - The check "this != &rhs" prevents: a = a; (copying yourself)

  getName():
    const std::string &Bureaucrat::getName() const
    {
        return (this->_name);
    }
    - Returns a CONST REFERENCE to _name (no copy, and cannot modify)
    - The const at the end means this method promises not to modify
      the object

  getGrade():
    int Bureaucrat::getGrade() const
    {
        return (this->_grade);
    }
    - Returns the grade as an integer

  increment():
    void Bureaucrat::increment()
    {
        if (this->_grade - 1 < 1)
            throw Bureaucrat::GradeTooHighException();
        this->_grade--;
    }
    - First checks if the NEXT grade would be too high (< 1)
    - If it would be invalid, throws exception BEFORE changing
    - Otherwise, decreases grade by 1 (promotion)

  decrement():
    void Bureaucrat::decrement()
    {
        if (this->_grade + 1 > 150)
            throw Bureaucrat::GradeTooLowException();
        this->_grade++;
    }
    - First checks if the NEXT grade would be too low (> 150)
    - If it would be invalid, throws exception BEFORE changing
    - Otherwise, increases grade by 1 (demotion)

  Exception what() methods:
    const char *Bureaucrat::GradeTooHighException::what() const throw()
    {
        return ("grade too high");
    }
    const char *Bureaucrat::GradeTooLowException::what() const throw()
    {
        return ("grade too low");
    }
    - These return human-readable error messages
    - The "throw()" means these functions will never throw exceptions

  Operator<< (free function, not a member):
    std::ostream &operator<<(std::ostream &o, const Bureaucrat &rhs)
    {
        o << rhs.getName() << ", bureaucrat grade " << rhs.getGrade() << ".";
        return (o);
    }
    - This is a FREE FUNCTION (not inside the class)
    - It allows you to print a Bureaucrat with std::cout <<
    - Example output: "Bob, bureaucrat grade 42."


--- main.cpp (the test file) ---

  This file tests all the functionality of the Bureaucrat class.

  Test 1: Valid construction
    - Creates 3 bureaucrats with valid grades (1, 150, 75)
    - Prints them all
    - Expected: All print successfully

  Test 2: Grade too high
    - Tries to create a bureaucrat with grade 0 (invalid)
    - Expected: Catches GradeTooHighException, prints "grade too high"

  Test 3: Grade too low
    - Tries to create a bureaucrat with grade 151 (invalid)
    - Expected: Catches GradeTooLowException, prints "grade too low"

  Test 4: Increment
    - Creates a bureaucrat with grade 3
    - Increments 3 times: 3 -> 2 -> 1 -> exception
    - Expected: Prints grades 3, 2, 1, then catches exception

  Test 5: Decrement
    - Creates a bureaucrat with grade 148
    - Decrements 3 times: 148 -> 149 -> 150 -> exception
    - Expected: Prints grades 148, 149, 150, then catches exception

  Test 6: Increment too high
    - Creates a bureaucrat with grade 1 (already highest)
    - Tries to increment (would go to 0, which is invalid)
    - Expected: Catches exception

  Test 7: Decrement too low
    - Creates a bureaucrat with grade 150 (already lowest)
    - Tries to decrement (would go to 151, which is invalid)
    - Expected: Catches exception

  Test 8: Copy constructor and assignment
    - Creates bureaucrat "Jack" with grade 50
    - Creates "k" as a copy of "Jack" (copy constructor)
    - Creates "Leo" with grade 100, then assigns Jack's data to Leo
    - Prints all three
    - Expected: All show grade 50 (Jack, k, and l all have same grade)


========================================================================
9. HOW TO COMPILE AND RUN
========================================================================

Open a terminal and navigate to the ex00 directory.

  Step 1: Compile
    Type: make
    This compiles all .cpp files and creates an executable called
    "bureaucrat".

  Step 2: Run
    Type: ./bureaucrat
    This runs the program and shows all the test results.

  Other useful commands:
    make clean     -> Removes .o files (intermediate build files)
    make fclean    -> Removes .o files AND the executable
    make re        -> Does fclean + make (full rebuild)

--- Understanding the Makefile ---

  The Makefile is a script that tells the compiler how to build
  your program. You don't need to understand every line, but here
  are the key variables:

    CXX        = c++         (the compiler being used)
    CXXFLAGS   = -Wall -Wextra -Werror -std=c++98
                 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                 -Wall      = Show all warnings
                 -Wextra    = Show extra warnings
                 -Werror    = Treat warnings as errors
                 -std=c++98 = Use the C++98 standard (an older but
                              valid version of C++)

  The -Werror flag means that if the compiler gives ANY warning,
  it will refuse to compile. This forces you to write clean code.


========================================================================
10. WHAT YOU WILL SEE WHEN YOU RUN IT
========================================================================

After building with "make" and running "./bureaucrat", you should
see output like this (exact output depends on your implementation):

  --- Test 1: Valid construction ---
  Jbutragu, bureaucrat grade 1.
  Peter Parker, bureaucrat grade 150.
  Spiderman, bureaucrat grade 75.

  --- Test 2: Grade too high ---
  Exception: grade too high

  --- Test 3: Grade too low ---
  Exception: grade too low

  --- Test 4: Increment ---
  Frank, bureaucrat grade 3.
  Frank, bureaucrat grade 2.
  Frank, bureaucrat grade 1.
  Exception: grade too high

  --- Test 5: Decrement ---
  Grace, bureaucrat grade 148.
  Grace, bureaucrat grade 149.
  Grace, bureaucrat grade 150.
  Exception: grade too low

  --- Test 6: Increment too high ---
  Henry, bureaucrat grade 1.
  Exception: grade too high

  --- Test 7: Decrement too low ---
  Ivy, bureaucrat grade 150.
  Exception: grade too low

  --- Test 8: Copy constructor and assignment ---
  Jack, bureaucrat grade 50.
  Jack, bureaucrat grade 50.
  Jack, bureaucrat grade 50.


========================================================================
11. COMMON MISTAKES AND TIPS
========================================================================

  1. Forgetting the include guard (#ifndef / #define / #endif)
     - Without it, including the header twice causes "redefinition" errors

  2. Not using initializer lists for const members
     - _name is const, so it MUST be set in the initializer list
     - You CANNOT assign it in the constructor body

  3. Throwing BEFORE changing the grade
     - Always validate FIRST, then modify
     - Wrong:  _grade--; if (_grade < 1) throw ...
     - Right:  if (_grade - 1 < 1) throw ...; _grade--;

  4. Forgetting the const qualifier on getName()/getGrade()
     - These methods should not modify the object

  5. Not checking for self-assignment in operator=
     - Always check: if (this != &rhs)

  6. Not returning *this from operator=
     - Must return *this to allow chaining: a = b = c;

  7. Using "namespace" in header files
     - Never put "using namespace std;" in .hpp files
     - It pollutes the global namespace

  8. Forgetting the virtual destructor
     - In this exercise, the destructor is not virtual (no inheritance)
     - In later exercises with inheritance, it WILL need to be virtual

========================================================================
