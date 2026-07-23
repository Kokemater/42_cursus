========================================================================
  EXERCISE 00: Bitcoin Exchange
========================================================================

TABLE OF CONTENTS
-----------------
  1. What is this exercise about?
  2. What is a container?
  3. std::map container
  4. File parsing
  5. Date validation
  6. File-by-file explanation
  7. How to compile and run
  8. What you will see when you run it
  9. Common mistakes and tips


========================================================================
1. WHAT IS THIS EXERCISE ABOUT?
========================================================================

This exercise teaches you about STL containers, file I/O, and string
parsing. You need to create a program that reads bitcoin prices from
a CSV database and calculates values based on input dates.

The program must:
  - Read a CSV database of bitcoin prices (data.csv)
  - Read an input file with dates and values
  - Find the closest date in the database
  - Calculate and display the value
  - Handle various error cases

Container used: std::map (cannot be reused in later exercises)


========================================================================
2. WHAT IS A CONTAINER?
========================================================================

A container is a data structure that stores a collection of elements.
The C++ STL (Standard Template Library) provides several containers:

  Sequence containers:
    - std::vector  (dynamic array)
    - std::list    (doubly-linked list)
    - std::deque   (double-ended queue)

  Associative containers:
    - std::set     (sorted unique elements)
    - std::map     (sorted key-value pairs)
    - std::multiset  (sorted, allows duplicates)
    - std::multimap  (sorted, allows duplicate keys)

  Container adapters:
    - std::stack   (LIFO)
    - std::queue   (FIFO)
    - std::priority_queue

In this exercise, we use std::map because:
  - We need to store date -> price pairs
  - We need fast lookup by date
  - We need to find the closest date (lower_bound)


========================================================================
3. STD::MAP CONTAINER
========================================================================

std::map is an associative container that stores key-value pairs
sorted by key.

Declaration:
  std::map<std::string, float> database;

Key operations:
  - database[key] = value;     Insert or update
  - database.find(key);        Find an element
  - database.lower_bound(key); Find first element not less than key
  - database.begin();          Iterator to first element
  - database.end();            Iterator past last element

Why use std::map for this exercise?
  - Dates are keys (strings like "2011-01-03")
  - Prices are values (floats like 0.3)
  - We can quickly look up prices by date
  - lower_bound helps find the closest date

Example:
  std::map<std::string, float> db;
  db["2011-01-03"] = 0.3;
  db["2011-01-10"] = 0.35;

  std::map<std::string, float>::iterator it = db.lower_bound("2011-01-05");
  // it points to "2011-01-10" (first date not less than "2011-01-05")
  // We need to go back one to get "2011-01-03" (closest lower date)


========================================================================
4. FILE PARSING
========================================================================

The program reads two files:

  1. Database file (data.csv):
     Format: date,exchange_rate
     Example:
       date,exchange_rate
       2009-01-02,0
       2011-01-03,0.3

  2. Input file:
     Format: date | value
     Example:
       date | value
       2011-01-03 | 3
       2011-01-09 | 1

Parsing steps:
  1. Open the file
  2. Read each line
  3. Find the delimiter (',' for CSV, '|' for input)
  4. Extract date and value
  5. Validate the data
  6. Process it


========================================================================
5. DATE VALIDATION
========================================================================

A valid date must:
  - Be in format: YYYY-MM-DD (exactly 10 characters)
  - Have '-' at positions 4 and 7
  - Year must be > 0
  - Month must be 1-12
  - Day must be 1-31 (depending on month)

Special cases:
  - February has 28 days (29 in leap years)
  - April, June, September, November have 30 days
  - Leap year: divisible by 4, except centuries unless divisible by 400

Example:
  2011-01-03  Valid
  2001-42-42  Invalid (month 42, day 42)
  2012-02-30  Invalid (February 30)


========================================================================
6. FILE-BY-FILE EXPLANATION
========================================================================

--- BitcoinExchange.hpp ---

  This file declares the BitcoinExchange class.

  Private members:
    - _database: std::map storing date -> price pairs

  Public methods:
    - Constructor: loads database from CSV file
    - processInputFile(): processes input file and outputs results

  Private methods:
    - loadDatabase(): reads CSV file into _database
    - isValidDate(): validates date format
    - isValidValue(): validates value range (0-1000)
    - findClosestDate(): finds closest date using lower_bound

--- BitcoinExchange.cpp ---

  This file implements the BitcoinExchange class.

  loadDatabase():
    - Opens CSV file
    - Skips header line
    - Reads each line and extracts date,price
    - Stores in _database map

  processInputFile():
    - Opens input file
    - Reads each line
    - Parses "date | value" format
    - Validates date and value
    - Finds closest date in database
    - Calculates and displays result

  findClosestDate():
    - Uses lower_bound to find first date not less than input
    - If exact match, returns it
    - Otherwise, goes back one (lower date, not upper)

--- main.cpp ---

  This file:
    - Checks for correct number of arguments
    - Creates BitcoinExchange with data.csv
    - Calls processInputFile with input file


========================================================================
7. HOW TO COMPILE AND RUN
========================================================================

Open a terminal and navigate to the ex00 directory.

  Step 1: Compile
    Type: make
    This creates an executable called "btc".

  Step 2: Run
    Type: ./btc input.txt

  Other commands:
    make clean   -> Removes .o files
    make fclean  -> Removes .o files and executable
    make re      -> Full rebuild


========================================================================
8. WHAT YOU WILL SEE WHEN YOU RUN IT
========================================================================

Example output:

  $> ./btc input.txt
  2011-01-03 => 3 = 0.9
  2011-01-03 => 2 = 0.6
  2011-01-03 => 1 = 0.3
  2011-01-03 => 1.2 = 0.36
  2011-01-09 => 1 = 0.32
  Error: not a positive number.
  Error: bad input => 2001-42-42
  2012-01-11 => 1 = 7.1
  Error: too large a number.


========================================================================
9. COMMON MISTAKES AND TIPS
========================================================================

  1. Not using std::map
     - The subject requires at least one container
     - std::map is perfect for date -> price pairs

  2. Wrong closest date logic
     - Must use lower date, not upper
     - Use lower_bound and go back if no exact match

  3. Not handling leap years
     - February 29 is valid in leap years
     - Must check for leap year correctly

  4. Forgetting to skip header line
     - CSV file has "date,exchange_rate" as first line
     - Skip it when reading

  5. Not validating date format
     - Must check format: YYYY-MM-DD
     - Must check ranges for year, month, day

  6. Not handling error cases
     - Negative numbers
     - Numbers > 1000
     - Invalid dates
     - Missing pipe character

========================================================================