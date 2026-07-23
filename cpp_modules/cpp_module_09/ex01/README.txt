========================================================================
  EXERCISE 01: Reverse Polish Notation
========================================================================

TABLE OF CONTENTS
-----------------
  1. What is this exercise about?
  2. What is Reverse Polish Notation?
  3. How RPN works
  4. std::stack container
  5. File-by-file explanation
  6. How to compile and run
  7. What you will see when you run it
  8. Common mistakes and tips


========================================================================
1. WHAT IS THIS EXERCISE ABOUT?
========================================================================

This exercise teaches you about the std::stack container and postfix
notation evaluation. You need to create a program that evaluates
mathematical expressions in Reverse Polish Notation (RPN).

The program must:
  - Take an RPN expression as a command-line argument
  - Evaluate the expression
  - Output the result
  - Handle errors appropriately

Container used: std::stack (cannot be reused in later exercises)


========================================================================
2. WHAT IS REVERSE POLISH NOTATION?
========================================================================

Reverse Polish Notation (RPN) is a mathematical notation where
operators come AFTER their operands. It's also called "postfix notation".

Normal notation (infix):  3 + 4
RPN notation (postfix):   3 4 +

Examples:
  Infix:           RPN:
  3 + 4            3 4 +
  (3 + 4) * 5      3 4 + 5 *
  3 + (4 * 5)      3 4 5 * +

Why use RPN?
  - No need for parentheses
  - No operator precedence rules
  - Easy to evaluate with a stack
  - Used in calculators and compilers


========================================================================
3. HOW RPN WORKS
========================================================================

Algorithm to evaluate RPN:
  1. Read tokens from left to right
  2. If token is a number, push it onto the stack
  3. If token is an operator:
     a. Pop the top two numbers from the stack
     b. Apply the operator
     c. Push the result back onto the stack
  4. At the end, the stack contains one number: the result

Example: "3 4 +"
  - Push 3: stack = [3]
  - Push 4: stack = [3, 4]
  - Apply '+': pop 4, pop 3, compute 3+4=7, push 7
  - Stack = [7]
  - Result = 7

Example: "5 1 2 + 4 * + 3 -"
  - Push 5: [5]
  - Push 1: [5, 1]
  - Push 2: [5, 1, 2]
  - Apply '+': [5, 3]
  - Push 4: [5, 3, 4]
  - Apply '*': [5, 12]
  - Apply '+': [17]
  - Push 3: [17, 3]
  - Apply '-': [14]
  - Result = 14


========================================================================
4. STD::STACK CONTAINER
========================================================================

std::stack is a container adapter that provides LIFO (Last In, First Out)
access to elements.

Declaration:
  std::stack<int> stack;

Key operations:
  - stack.push(value)   Add element to top
  - stack.pop()         Remove top element
  - stack.top()         Access top element
  - stack.empty()       Check if empty
  - stack.size()        Get number of elements

Why use std::stack for RPN?
  - RPN evaluation naturally uses a stack
  - Push numbers, pop for operators
  - Perfect fit for the algorithm

Example:
  std::stack<int> s;
  s.push(3);
  s.push(4);
  int b = s.top(); s.pop();  // b = 4
  int a = s.top(); s.pop();  // a = 3
  s.push(a + b);              // s = [7]


========================================================================
5. FILE-BY-FILE EXPLANATION
========================================================================

--- RPN.hpp ---

  This file declares the RPN class.

  Public methods:
    - evaluate(): static method that evaluates an RPN expression

  Private methods:
    - isOperator(): checks if a token is an operator
    - performOperation(): applies an operator to two numbers

--- RPN.cpp ---

  This file implements the RPN class.

  evaluate():
    - Creates a stack to store numbers
    - Parses the expression token by token
    - If token is a number, pushes it
    - If token is an operator, pops two numbers and applies
    - Returns the final result

  isOperator():
    - Returns true if token is +, -, *, or /

  performOperation():
    - Applies the operator to two operands
    - Handles division by zero

--- main.cpp ---

  This file:
    - Checks for correct number of arguments
    - Calls RPN::evaluate with the expression
    - Catches and displays any errors


========================================================================
6. HOW TO COMPILE AND RUN
========================================================================

Open a terminal and navigate to the ex01 directory.

  Step 1: Compile
    Type: make
    This creates an executable called "RPN".

  Step 2: Run
    Type: ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"

  Other commands:
    make clean   -> Removes .o files
    make fclean  -> Removes .o files and executable
    make re      -> Full rebuild


========================================================================
7. WHAT YOU WILL SEE WHEN YOU RUN IT
========================================================================

Example output:

  $> ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
  42

  $> ./RPN "7 7 * 7 -"
  42

  $> ./RPN "1 2 * 2 / 2 * 2 4 - +"
  0

  $> ./RPN "(1 + 1)"
  Error

  $> ./RPN "3 +"
  Error


========================================================================
8. COMMON MISTAKES AND TIPS
========================================================================

  1. Not using std::stack
     - The subject requires at least one container
     - std::stack is the natural choice for RPN

  2. Wrong operator order
     - First popped is the SECOND operand
     - Example: for "3 4 -", pop 4 first, then 3, compute 3-4

  3. Not handling division by zero
     - Must check if divisor is zero
     - Display error message

  4. Not validating input
     - Check for invalid tokens
     - Check for too many operators
     - Check for not enough operands

  5. Using wrong comparison
     - The subject shows: "Error" for invalid expressions
     - Not "Error: ..." or other messages

  6. Not handling single number
     - A single number is valid RPN (result is that number)
     - Example: "./RPN 42" should output 42

========================================================================