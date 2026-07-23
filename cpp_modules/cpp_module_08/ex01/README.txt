========================================================================
  EXERCISE 01: Span
========================================================================

TABLE OF CONTENTS
-----------------
  1. What is this exercise about?
  2. What is a Span?
  3. Orthodox Canonical Form
  4. STL algorithms
  5. Range of iterators
  6. File-by-file explanation
  7. How to compile and run
  8. What you will see when you run it
  9. Common mistakes and tips


========================================================================
1. WHAT IS THIS EXERCISE ABOUT?
========================================================================

This exercise teaches you about STL algorithms, containers, and
exception handling. You need to create a Span class that stores
integers and can find the shortest and longest distances between them.

The program must:
  - Create a Span class with a maximum capacity
  - Add numbers one at a time or via iterator range
  - Find shortest span (minimum difference)
  - Find longest span (maximum difference)
  - Handle overflow and empty/span-too-small errors

Container used: std::vector (cannot be reused in later exercises)


========================================================================
2. WHAT IS A SPAN?
========================================================================

A Span is the distance (difference) between two numbers.

Example:
  Numbers: {6, 3, 17, 9, 11}

  All pairs and their spans:
    |6 - 3| = 3
    |6 - 17| = 11
    |6 - 9| = 3
    |6 - 11| = 5
    |3 - 17| = 14
    |3 - 9| = 6
    |3 - 11| = 8
    |17 - 9| = 8
    |17 - 11| = 6
    |9 - 11| = 2

  Shortest span: 2 (between 9 and 11)
  Longest span: 14 (between 3 and 17)

Why is this useful?
  - Finding gaps in data
  - Analyzing distributions
  - Optimization problems
  - Real-world applications (scheduling, resource allocation)


========================================================================
3. ORTHODOX CANONICAL FORM
========================================================================

The Span class follows Orthodox Canonical Form (OCF):

  1. Default constructor
     Span(void) - Creates an empty Span (not used in subject)

  2. Copy constructor
     Span(const Span &src) - Creates a copy of another Span

  3. Assignment operator
     Span &operator=(const Span &rhs) - Copies data from another Span

  4. Destructor
     ~Span(void) - Cleans up (nothing to clean for vector)

Note: The default constructor is private because the subject says
"the only parameter passed to the constructor" is the maximum size.


========================================================================
4. STL ALGORITHMS
========================================================================

This exercise uses several STL algorithms from <algorithm>:

  std::sort:
    - Sorts elements in a range
    - Used to sort numbers for shortest span calculation
    - O(n log n) time complexity

  std::min_element:
    - Finds the smallest element in a range
    - Returns iterator to the minimum
    - Used for longest span calculation

  std::max_element:
    - Finds the largest element in a range
    - Returns iterator to the maximum
    - Used for longest span calculation

Example:
  std::vector<int> vec = {6, 3, 17, 9, 11};

  int min = *std::min_element(vec.begin(), vec.end());  // 3
  int max = *std::max_element(vec.begin(), vec.end());  // 17
  int longest = max - min;                               // 14


========================================================================
5. RANGE OF ITERATORS
========================================================================

The subject requires a member function to add multiple numbers
in a single call using iterator ranges.

Syntax:
  void addNumber(iterator begin, iterator end);

This allows:
  std::vector<int> vec;
  vec.push_back(100);
  vec.push_back(200);
  vec.push_back(300);

  Span sp(10);
  sp.addNumber(vec.begin(), vec.end());

Why is this useful?
  - Faster than adding one by one
  - Can add from any container (vector, list, deque, etc.)
  - More convenient for large datasets

Implementation:
  void Span::addNumber(std::vector<int>::iterator begin,
                        std::vector<int>::iterator end)
  {
      for (std::vector<int>::iterator it = begin; it != end; ++it)
      {
          if (_numbers.size() >= _maxSize)
              throw std::out_of_range("Span is full");
          _numbers.push_back(*it);
      }
  }


========================================================================
6. FILE-BY-FILE EXPLANATION
========================================================================

--- Span.hpp ---

  This file declares the Span class.

  Private members:
    - _numbers: std::vector storing the integers
    - _maxSize: Maximum capacity of the Span

  Public methods:
    - Constructor: creates Span with given capacity
    - addNumber(int): adds a single number
    - addNumber(iterator, iterator): adds range of numbers
    - shortestSpan(): finds minimum difference
    - longestSpan(): finds maximum difference

--- Span.cpp ---

  This file implements the Span class.

  addNumber(int):
    - Checks if Span is full
    - Throws exception if full
    - Adds number to _numbers vector

  addNumber(iterator, iterator):
    - Iterates through the range
    - Adds each element
    - Throws exception if Span becomes full

  shortestSpan():
    - Checks if at least 2 numbers exist
    - Creates a sorted copy of _numbers
    - Finds minimum difference between adjacent elements
    - Returns the shortest span

  longestSpan():
    - Checks if at least 2 numbers exist
    - Uses std::min_element and std::max_element
    - Returns max - min

--- main.cpp ---

  This file tests the Span class.

  Tests:
    1. Basic Span with 5 numbers
    2. Span overflow exception
    3. Not enough elements exception
    4. Range of iterators
    5. Large Span with 10,000 numbers
    6. Copy constructor


========================================================================
7. HOW TO COMPILE AND RUN
========================================================================

Open a terminal and navigate to the ex01 directory.

  Step 1: Compile
    Type: make
    This creates an executable called "ex01".

  Step 2: Run
    Type: ./ex01

  Other commands:
    make clean   -> Removes .o files
    make fclean  -> Removes .o files and executable
    make re      -> Full rebuild


========================================================================
8. WHAT YOU WILL SEE WHEN YOU RUN IT
========================================================================

Example output:

  === Test 1: Basic Span ===
  Shortest span: 2
  Longest span: 14

  === Test 2: Span full exception ===
  Exception: Span is full

  === Test 3: Not enough elements ===
  Exception: Not enough elements to find span

  === Test 4: Range of iterators ===
  Shortest span: 100
  Longest span: 400

  === Test 5: Large Span (10,000 numbers) ===
  Shortest span: 2
  Longest span: 19998

  === Test 6: Copy constructor ===
  Copy shortest span: 10
  Copy longest span: 20


========================================================================
9. COMMON MISTAKES AND TIPS
========================================================================

  1. Not using std::vector
     - The subject requires at least one container
     - std::vector is the natural choice

  2. Not implementing range of iterators
     - Subject says "it would be wonderful to fill your Span using
       a range of iterators"
     - Must implement addNumber with iterator parameters

  3. Wrong shortest span algorithm
     - Must sort first, then compare adjacent elements
     - Not compare all pairs (too slow)

  4. Not using STL algorithms
     - Subject says "You must use the STL"
     - Use std::sort, std::min_element, std::max_element

  5. Forgetting exception handling
     - Must throw when Span is full
     - Must throw when less than 2 numbers

  6. Not testing with 10,000 numbers
     - Subject says "Test your Span with at least 10,000 numbers"
     - Must verify it works with large datasets

  7. Wrong return type for shortestSpan/longestSpan
     - Must return int (the span value)
     - Not iterator or void

  8. Not following Orthodox Canonical Form
     - Must have copy constructor and assignment operator
     - Must handle deep copy correctly

========================================================================