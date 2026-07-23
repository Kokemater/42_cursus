========================================================================
  EXERCISE 01: Serialization
========================================================================

TABLE OF CONTENTS
-----------------
  1. What is this exercise about?
  2. What is serialization?
  3. What is reinterpret_cast?
  4. What is uintptr_t?
  5. File-by-file explanation
  6. How to compile and run
  7. What you will see when you run it
  8. Common mistakes and tips


========================================================================
1. WHAT IS THIS EXERCISE ABOUT?
========================================================================

This exercise teaches you about serialization and reinterpret_cast.
You need to create a class called "Serializer" that can convert
a pointer to an integer and back.

The program must:
  - Create a Data structure with data members
  - Serialize a pointer to uintptr_t
  - Deserialize it back to a pointer
  - Verify the pointers are equal


========================================================================
2. WHAT IS SERIALIZATION?
========================================================================

Serialization is the process of converting an object into a format
that can be stored or transmitted, then reconstructed later.

In this exercise:
  - We convert a pointer (memory address) to an integer
  - We can then store or transmit that integer
  - We convert it back to a pointer
  - The pointer should point to the original object

This is useful for:
  - Saving object state to files
  - Sending objects over networks
  - Storing objects in databases


========================================================================
3. WHAT IS REINTERPRET_CAST?
========================================================================

reinterpret_cast is a C++ cast that reinterprets the bit pattern
of a value as a different type.

  uintptr_t raw = reinterpret_cast<uintptr_t>(ptr);
  Data *ptr2 = reinterpret_cast<Data *>(raw);

This is the LOWEST-LEVEL cast. It:
  - Does not change the actual bits
  - Just tells the compiler to treat them differently
  - Is implementation-defined (depends on the system)

When to use:
  - When you need to convert between pointer and integer types
  - When you need to access raw memory
  - When other casts cannot help

WARNING:
  - This cast is dangerous if used incorrectly
  - The converted value might not be usable
  - Always ensure the conversion makes sense


========================================================================
4. WHAT IS UINTPTR_T?
========================================================================

uintptr_t is an unsigned integer type that is guaranteed to hold
a pointer. It is defined in <stdint.h> or <cstdint>.

  - It is large enough to hold any pointer
  - On 32-bit systems: typically 32 bits (4 bytes)
  - On 64-bit systems: typically 64 bits (8 bytes)

Why use it:
  - Standard way to convert pointers to integers
  - Guaranteed to work on any platform
  - Defined in the C++ standard

Example:
  Data *ptr = new Data();
  uintptr_t raw = reinterpret_cast<uintptr_t>(ptr);
  // raw now contains the memory address of the Data object


========================================================================
5. FILE-BY-FILE EXPLANATION
========================================================================

--- Serializer.hpp ---

  This file declares the Serializer class and Data structure.

  Data structure:
    - name (string): A name for the data
    - value (int): An integer value
    - amount (float): A floating-point value

  Serializer class:
    - Cannot be instantiated (private constructor)
    - Has two static methods: serialize() and deserialize()

--- Serializer.cpp ---

  This file implements the Serializer class.

  serialize():
    - Takes a Data pointer
    - Uses reinterpret_cast to convert it to uintptr_t
    - Returns the uintptr_t value

  deserialize():
    - Takes a uintptr_t value
    - Uses reinterpret_cast to convert it back to Data pointer
    - Returns the Data pointer

--- main.cpp ---

  This file tests the Serializer class.

  Steps:
    1. Create a Data object with values
    2. Print original data and address
    3. Serialize the pointer
    4. Deserialize it back
    5. Verify the pointers are equal


========================================================================
6. HOW TO COMPILE AND RUN
========================================================================

Open a terminal and navigate to the ex01 directory.

  Step 1: Compile
    Type: make
    This creates an executable called "serializer".

  Step 2: Run
    Type: ./serializer

  Other commands:
    make clean   -> Removes .o files
    make fclean  -> Removes .o files and executable
    make re      -> Full rebuild


========================================================================
7. WHAT YOU WILL SEE WHEN YOU RUN IT
========================================================================

Example output:

  === Original Data ===
  Address: 0x7ffd5e8a3b40
  Name: Test Data
  Value: 42
  Amount: 3.14

  === Serialization ===
  Serialized value: 140725184357704

  === Deserialization ===
  Deserialized address: 0x7ffd5e8a3b40
  Name: Test Data
  Value: 42
  Amount: 3.14

  === Verification ===
  SUCCESS: Pointers are equal!

Note: The address and serialized value will vary between runs.


========================================================================
8. COMMON MISTAKES AND TIPS
========================================================================

  1. Using static_cast instead of reinterpret_cast
     - static_cast cannot convert between pointer and integer
     - You MUST use reinterpret_cast for this

  2. Forgetting to include <stdint.h>
     - uintptr_t is defined in <stdint.h> or <cstdint>

  3. Not verifying the pointers are equal
     - Always check that deserialize(serialize(ptr)) == ptr

  4. Using the wrong integer type
     - Must be uintptr_t (unsigned integer that can hold a pointer)
     - Not int, not size_t, not unsigned int

  5. Not creating a non-empty Data structure
     - The subject requires data members in Data
     - At least one member variable is needed

  6. Deleting the Data object before verification
     - Keep the object alive until after verification

========================================================================