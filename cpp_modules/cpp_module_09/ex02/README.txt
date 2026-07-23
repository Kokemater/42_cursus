========================================================================
  EXERCISE 02: PmergeMe
========================================================================

TABLE OF CONTENTS
-----------------
  1. What is this exercise about?
  2. What is the Ford-Johnson algorithm?
  3. Merge-insert sort
  4. std::vector and std::deque
  5. Time complexity
  6. File-by-file explanation
  7. How to compile and run
  8. What you will see when you run it
  9. Common mistakes and tips


========================================================================
1. WHAT IS THIS EXERCISE ABOUT?
========================================================================

This exercise teaches you about sorting algorithms, container
performance, and time measurement. You need to implement the
Ford-Johnson algorithm (merge-insert sort) using two different
containers.

The program must:
  - Take a sequence of positive integers as arguments
  - Sort them using merge-insert sort
  - Display before/after sequences
  - Measure and display sorting time for each container

Containers used: std::vector and std::deque (must use both)


========================================================================
2. WHAT IS THE FORD-JOHNSON ALGORITHM?
========================================================================

The Ford-Johnson algorithm (also called merge-insertion sort) is a
sorting algorithm designed to minimize comparisons.

Published in 1959 by Ford and Johnson, it was once thought to be
the most efficient comparison-based sorting algorithm.

Key idea:
  1. Pair up elements and compare pairs
  2. Sort the larger elements of each pair (recursively)
  3. Insert the smaller elements using binary insertion

The algorithm:
  1. Pair adjacent elements
  2. Compare each pair, keep track of larger and smaller
  3. Recursively sort the larger elements
  4. Insert smaller elements using binary search

Why is it interesting?
  - Uses fewer comparisons than merge sort for small arrays
  - Complex to implement
  - Historical significance in algorithm design


========================================================================
3. MERGE-INSERT SORT
========================================================================

The merge-insert sort combines two strategies:

  Merge sort:
    - Divide array in half
    - Recursively sort each half
    - Merge the sorted halves
    - Good for large arrays

  Insertion sort:
    - Insert each element into its correct position
    - Good for small arrays

Hybrid approach:
  - Use merge sort for large divisions
  - Use insertion sort for small subarrays
  - This is what std::introsort does in practice

In this exercise:
  - We implement a merge-insert hybrid
  - We compare performance on std::vector vs std::deque


========================================================================
4. STD::VECTOR AND STD::DEQUE
========================================================================

std::vector:
  - Dynamic array
  - Contiguous memory
  - Fast random access: O(1)
  - Slow insertion in middle: O(n)
  - Good cache performance

std::deque:
  - Double-ended queue
  - Segmented memory
  - Fast random access: O(1)
  - Fast insertion at both ends: O(1)
  - Slower cache performance than vector

Performance comparison:
  - Vector is usually faster for sorting
  - Deque has different memory characteristics
  - This exercise shows the difference


========================================================================
5. TIME COMPLEXITY
========================================================================

Ford-Johnson algorithm:
  - Time complexity: O(n log n) comparisons
  - Space complexity: O(n)

Comparison count:
  - Best case: ~n log n comparisons
  - Worst case: ~n log n comparisons
  - Fewer comparisons than merge sort in practice

In this exercise:
  - We measure actual wall-clock time
  - Include both sorting and data management
  - Show difference between vector and deque


========================================================================
6. FILE-BY-FILE EXPLANATION
========================================================================

--- PmergeMe.hpp ---

  This file declares the PmergeMe class.

  Public methods:
    - sortVector(): sorts a std::vector
    - sortDeque(): sorts a std::deque

  Private methods:
    - mergeInsertSortVector(): merge-insert sort for vector
    - mergeInsertSortDeque(): merge-insert sort for deque
    - insertionSortVector(): insertion sort for small subarrays
    - insertionSortDeque(): insertion sort for small subarrays
    - mergeVector(): merge two sorted halves (vector)
    - mergeDeque(): merge two sorted halves (deque)

--- PmergeMe.cpp ---

  This file implements the PmergeMe class.

  sortVector() / sortDeque():
    - Entry points for sorting
    - Call the appropriate merge-insert sort

  mergeInsertSortVector() / mergeInsertSortDeque():
    - Implement merge-insert sort
    - Use bottom-up approach (iterative, not recursive)
    - Start with small subarrays and merge

  insertionSortVector() / insertionSortDeque():
    - Sort small subarrays using insertion sort
    - Used when subarray size is small

  mergeVector() / mergeDeque():
    - Merge two sorted subarrays
    - Standard merge algorithm

--- main.cpp ---

  This file:
    - Parses command-line arguments
    - Creates vector and deque from input
    - Measures sorting time for each
    - Displays results

  Time measurement:
    - Uses std::clock() for timing
    - Converts to microseconds
    - Displays time for each container


========================================================================
7. HOW TO COMPILE AND RUN
========================================================================

Open a terminal and navigate to the ex02 directory.

  Step 1: Compile
    Type: make
    This creates an executable called "PmergeMe".

  Step 2: Run
    Type: ./PmergeMe 3 5 9 7 4

  Other commands:
    make clean   -> Removes .o files
    make fclean  -> Removes .o files and executable
    make re      -> Full rebuild


========================================================================
8. WHAT YOU WILL SEE WHEN YOU RUN IT
========================================================================

Example output:

  $> ./PmergeMe 3 5 9 7 4
  Before: 3 5 9 7 4
  After: 3 4 5 7 9
  Time to process a range of 5 elements with std::vector : 0.00031 us
  Time to process a range of 5 elements with std::deque : 0.00014 us

  $> ./PmergeMe "-1" "2"
  Error

  $> ./PmergeMe
  Error

  $> ./PmergeMe 1 2 3 4 5 6 7 8 9 10
  Before: 1 2 3 4 5 6 7 8 9 10
  After: 1 2 3 4 5 6 7 8 9 10
  Time to process a range of 10 elements with std::vector : 0.00012 us
  Time to process a range of 10 elements with std::deque : 0.00009 us


========================================================================
9. COMMON MISTAKES AND TIPS
========================================================================

  1. Not using two different containers
     - Must use at least two containers
     - std::vector and std::deque are recommended

  2. Not implementing Ford-Johnson correctly
     - Must use merge-insert sort
     - Not just std::sort or std::stable_sort

  3. Wrong time measurement
     - Must measure sorting time, not just data copying
     - Include all operations in timing

  4. Not handling errors
     - Must check for negative numbers
     - Must check for no arguments

  5. Displaying wrong format
     - Must show Before, After, and times
     - Must specify container names

  6. Not handling large inputs
     - Must handle at least 3000 integers
     - Test with large sequences

  7. Using C++11 features
     - This exercise uses C++98 standard
     - No chrono, no lambda, no auto

========================================================================