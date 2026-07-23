========================================================================
  EXERCISE 03: At least this beats coffee-making
========================================================================

TABLE OF CONTENTS
-----------------
  1. What is this exercise about?
  2. Quick recap of ex00, ex01, and ex02
  3. What is an "Intern"?
  4. What is a "factory function"?
  5. How does the Intern work?
  6. What are "static member functions"?
  7. What is an array of function pointers?
  8. Memory management: new and delete
  9. Complete class diagrams
  10. File-by-file explanation
  11. How to compile and run
  12. What you will see when you run it
  13. Common mistakes and tips


========================================================================
1. WHAT IS THIS EXERCISE ABOUT?
========================================================================

In ex02, we created three different form types:
  - ShrubberyCreationForm (creates ASCII trees)
  - RobotomyRequestForm (robotomizes a target, 50% success)
  - PresidentialPardonForm (pardons a target)

To use these forms, we had to write code like:
  ShrubberyCreationForm shrub("home");
  RobotomyRequestForm robot("Bender");
  PresidentialPardonForm pardon("Ford");

But what if we want to create forms BASED ON A NAME?
For example, a user types "robotomy request" and we need to
create the right form automatically.

THIS IS WHAT THE INTERN DOES!

The Intern is a class that can create AForm objects by name.
You give it a form name and a target, and it returns a pointer
to the newly created form.

  Intern intern;
  AForm *form = intern.makeForm("robotomy request", "Bender");
  // form now points to a RobotomyRequestForm targeting "Bender"

This is called a FACTORY PATTERN -- a way to create objects
without knowing their exact type at compile time.


========================================================================
2. QUICK RECAP OF EX00, EX01, AND EX02
========================================================================

  ex00: Bureaucrat (person with a rank)
    - Name, grade (1-150)
    - increment(), decrement()

  ex01: Form (document that can be signed)
    - Name, signed status, sign grade, exec grade
    - beSigned() by a bureaucrat
    - signForm() on Bureaucrat

  ex02: AForm (abstract base) + 3 concrete forms
    - AForm: abstract class with pure virtual action()
    - ShrubberyCreationForm: creates ASCII tree files
    - RobotomyRequestForm: robotomizes with 50% success
    - PresidentialPardonForm: pardons the target
    - Bureaucrat gains executeForm()

  ex03: Intern (form creator)
    - Has makeForm(name, target) method
    - Creates and returns the right form based on the name
    - The Intern has NO name, NO grade -- it is very simple


========================================================================
3. WHAT IS AN "INTERN"?
========================================================================

In real life, an intern is a junior employee who does basic tasks.
In this exercise, the Intern's only job is to CREATE FORMS.

The Intern class is intentionally SIMPLE:
  - It has NO name
  - It has NO grade
  - It has NO special characteristics
  - Its ONLY purpose is to create forms

Think of it like a vending machine:
  - You put in a request (form name + target)
  - The vending machine (Intern) dispenses the right form
  - You don't need to know HOW the vending machine works internally

The Intern:
  - Has a default constructor (creates an intern)
  - Has a copy constructor (copies an intern)
  - Has an assignment operator
  - Has a destructor
  - Has ONE important method: makeForm()


========================================================================
4. WHAT IS A "FACTORY FUNCTION"?
========================================================================

A factory function is a function that CREATES OBJECTS for you,
without you needing to know the exact type.

Instead of you writing:
  if (name == "shrubbery")
      form = new ShrubberyCreationForm(target);
  else if (name == "robotomy")
      form = new RobotomyRequestForm(target);
  else if (name == "presidential")
      form = new PresidentialPardonForm(target);

The Intern's makeForm() does this for you:
  form = intern.makeForm("shrubbery creation", "home");

BENEFITS:
  - You don't need to know which class to use
  - You just provide a name, and the Intern figures it out
  - Adding new form types only requires changing the Intern's code
  - The rest of your code stays the same

This is a common pattern in software engineering called the
"Factory Pattern" or "Factory Method Pattern".


========================================================================
5. HOW DOES THE INTERN WORK?
========================================================================

The Intern has ONE public method:

  AForm *makeForm(const std::string &formName, const std::string &target);

  PARAMETERS:
    - formName: The name of the form to create
      Must be one of:
        "shrubbery creation"
        "robotomy request"
        "presidential pardon"

    - target: The target for the form
      (e.g., "home", "Bender", "Ford Prefect")

  RETURN VALUE:
    - A pointer to the newly created AForm object
    - Returns NULL if the form name is unknown

  HOW IT WORKS INTERNALLY:
    1. The Intern has a list of known form names
    2. It compares the input formName with each known name
    3. If it finds a match, it creates the corresponding form
    4. If no match is found, it prints an error and returns NULL

  IMPORTANT: The caller is responsible for DELETING the form
  when done (because makeForm uses "new" to allocate memory).

  Example usage:
    Intern intern;
    AForm *form = intern.makeForm("robotomy request", "Bender");
    if (form)
    {
        // Use the form...
        Bureaucrat bob("Bob", 1);
        bob.signForm(*form);
        bob.executeForm(*form);
        delete form;    // <-- MUST delete when done!
    }


========================================================================
6. WHAT ARE "STATIC MEMBER FUNCTIONS"?
========================================================================

A static member function is a function that belongs to the CLASS
itself, not to any specific object.

Normal (non-static) function:
  // Called on an object
  Bureaucrat bob;
  bob.getGrade();    // Called on the "bob" object

Static function:
  // Called on the class itself
  Bureaucrat::someStaticFunction();   // No object needed!

In the Intern class, the creator functions are static:

  class Intern
  {
  private:
      static AForm *_createShrubbery(const std::string &target);
      static AForm *_createRobotomy(const std::string &target);
      static AForm *_createPresidential(const std::string &target);
  };

  WHY STATIC?
    - These functions don't need access to any specific Intern object
    - They just create and return a new form
    - Making them static allows them to be stored in an array
      of function pointers (see next section)

  HOW THEY WORK:
    static AForm *_createShrubbery(const std::string &target)
    {
        return (new ShrubberyCreationForm(target));
    }

    - Simply creates a new ShrubberyCreationForm with the given target
    - Returns a pointer to it
    - The "new" keyword allocates memory on the heap


========================================================================
7. WHAT IS AN ARRAY OF FUNCTION POINTERS?
========================================================================

This is the most advanced concept in this exercise. Let me explain
step by step.

--- What is a pointer? ---
A pointer is a variable that stores a MEMORY ADDRESS (the location
of something in the computer's memory).

  int x = 42;
  int *ptr = &x;    // ptr now stores the ADDRESS of x

--- What is a function pointer? ---
A function pointer is a pointer that stores the ADDRESS of a function.
This lets you call a function through a pointer.

  // Normal way to call a function:
  _createShrubbery(target);

  // Using a function pointer:
  AForm *(*creator)(const std::string &) = &_createShrubbery;
  creator(target);    // Same as calling _createShrubbery(target)

--- What is an array of function pointers? ---
An array of function pointers stores MULTIPLE function addresses.
This lets you choose WHICH function to call at runtime.

  // Array of function pointers:
  AForm *(*creators[])(const std::string &) = {
      &_createShrubbery,
      &_createRobotomy,
      &_createPresidential
  };

  // Array of form names:
  const std::string names[] = {
      "shrubbery creation",
      "robotomy request",
      "presidential pardon"
  };

  // Finding the right function:
  for (int i = 0; i < 3; i++)
  {
      if (formName == names[i])
          return creators[i](target);   // Call the matching function
  }

--- Why use this instead of if/else? ---
Without function pointers, you would write:

  if (formName == "shrubbery creation")
      return new ShrubberyCreationForm(target);
  else if (formName == "robotomy request")
      return new RobotomyRequestForm(target);
  else if (formName == "presidential pardon")
      return new PresidentialPardonForm(target);

With function pointers, you write a CLEANER loop:

  for (int i = 0; i < 3; i++)
  {
      if (formName == names[i])
          return creators[i](target);
  }

The function pointer approach is:
  - Easier to extend (just add to the arrays)
  - Cleaner (no long if/else chains)
  - More professional (common in real-world code)


========================================================================
8. MEMORY MANAGEMENT: NEW AND DELETE
========================================================================

In C++, when you create an object normally:

  Bureaucrat bob("Bob", 1);
  // bob lives on the "stack"
  // It is automatically destroyed when it goes out of scope

But when you use "new":

  AForm *form = new ShrubberyCreationForm("home");
  // form lives on the "heap" (dynamic memory)
  // It is NOT automatically destroyed
  // You MUST manually delete it when done

  delete form;    // <-- You must do this!

WHY USE "new"?
  - The Intern doesn't know what type of form to create at compile time
  - It needs to return a POINTER (not an object) because the object
    is created inside makeForm() and needs to survive after the
    function returns
  - If the Intern created a local object, it would be destroyed
    when makeForm() returns, and the caller would get a dangling pointer

  // WRONG (would crash!):
  AForm *makeForm(...)
  {
      ShrubberyCreationForm form(target);
      return (&form);    // DANGER: form is destroyed when function returns!
  }

  // RIGHT (uses heap):
  AForm *makeForm(...)
  {
      return (new ShrubberyCreationForm(target));  // Heap memory persists
  }

MEMORY LEAK WARNING:
  Every "new" MUST have a matching "delete"!
  If you forget to delete, you have a MEMORY LEAK.

  // WRONG: Memory leak!
  AForm *form = intern.makeForm("robotomy request", "Bender");
  // ... use form ...
  // Forgot to delete! Memory is leaked!

  // RIGHT:
  AForm *form = intern.makeForm("robotomy request", "Bender");
  // ... use form ...
  delete form;    // Memory is freed


========================================================================
9. COMPLETE CLASS DIAGRAMS
========================================================================

  ┌──────────────────────────────────────────────────────────┐
  │                    INTERN                               │
  ├──────────────────────────────────────────────────────────┤
  │ PRIVATE (static methods):                               │
  │   static AForm *_createShrubbery(const string &target)  │
  │   static AForm *_createRobotomy(const string &target)   │
  │   static AForm *_createPresidential(const string &t)    │
  ├──────────────────────────────────────────────────────────┤
  │ PUBLIC:                                                 │
  │   Intern()                                              │
  │   Intern(const Intern &src)                             │
  │   ~Intern()                                             │
  │   operator=(const Intern &rhs)                          │
  │   makeForm(formName, target) -> AForm*                  │
  └──────────────────────────────────────────────────────────┘

  Note: The Intern has NO member variables at all! It is a very
  simple class. It only has methods.

  The three private static methods are "helper functions" that
  create specific form types. They are static because they don't
  need access to any Intern object's data.

  The makeForm() method is the public interface. It:
    1. Compares formName with known names
    2. Calls the matching static helper function
    3. Returns the result (or NULL if unknown)

  COMPLETE SYSTEM DIAGRAM:

  ┌──────────────────────────────────────────────────────────┐
  │                    INTERN                               │
  │                                                         │
  │   makeForm("robotomy request", "Bender")                │
  │       |                                                 │
  │       +-- Compare with "shrubbery creation" -> NO       │
  │       +-- Compare with "robotomy request" -> YES!       │
  │       |                                                 │
  │       +-- Call _createRobotomy("Bender")                │
  │       |     |                                           │
  │       |     +-- return new RobotomyRequestForm("Bender")│
  │       |                                                 │
  │       +-- Return pointer to RobotomyRequestForm         │
  └──────────────────────────────────────────────────────────┘


========================================================================
10. FILE-BY-FILE EXPLANATION
========================================================================

--- Intern.hpp ---

  The blueprint for the Intern class.

  Key points:
    - No member variables (no _name, no _grade, nothing!)
    - One public method: makeForm()
    - Three private static helper methods
    - Standard OCF methods (constructor, copy, assignment, destructor)

  class Intern
  {
  public:
      Intern(void);
      Intern(const Intern &src);
      ~Intern(void);
      Intern &operator=(const Intern &rhs);

      AForm *makeForm(const std::string &formName,
                       const std::string &target);
  private:
      static AForm *_createShrubbery(const std::string &target);
      static AForm *_createRobotomy(const std::string &target);
      static AForm *_createPresidential(const std::string &target);
  };

  Note the "static" keyword on the private methods. This means
  they don't have access to "this" (the current object) because
  they don't operate on any specific object.


--- Intern.cpp ---

  Implements all the Intern methods.

  Constructors/Destructor/Assignment:
    All are empty or do nothing meaningful (because the Intern
    has no data to initialize or clean up).

    Intern::Intern(void)
    {
    }

    Intern::Intern(const Intern &src)
    {
        (void)src;    // Explicitly ignore the parameter
    }

    Intern::~Intern(void)
    {
    }

    Intern &Intern::operator=(const Intern &rhs)
    {
        (void)rhs;
        return (*this);
    }

    The (void)src and (void)rhs lines are used to suppress
    "unused parameter" warnings. Since the Intern has no data,
    there is nothing to copy or assign.


  Static helper functions:
    AForm *Intern::_createShrubbery(const std::string &target)
    {
        return (new ShrubberyCreationForm(target));
    }

    AForm *Intern::_createRobotomy(const std::string &target)
    {
        return (new RobotomyRequestForm(target));
    }

    AForm *Intern::_createPresidential(const std::string &target)
    {
        return (new PresidentialPardonForm(target));
    }

    Each function simply creates a new form of the appropriate type
    and returns a pointer to it.


  makeForm():
    AForm *Intern::makeForm(const std::string &formName,
                             const std::string &target)
    {
        const std::string names[] = {
            "shrubbery creation",
            "robotomy request",
            "presidential pardon"
        };
        AForm *(*creators[])(const std::string &) = {
            &_createShrubbery,
            &_createRobotomy,
            &_createPresidential
        };

        for (int i = 0; i < 3; i++)
        {
            if (formName == names[i])
            {
                std::cout << "Intern creates " << formName << std::endl;
                return (creators[i](target));
            }
        }
        std::cout << "Intern cannot create form \"" << formName
                  << "\": unknown form name." << std::endl;
        return (NULL);
    }

  STEP-BY-STEP:
    1. Define an array of known form names
    2. Define an array of function pointers (one for each form type)
    3. Loop through the names:
       - If formName matches names[i], call creators[i](target)
       - Print a success message
       - Return the newly created form
    4. If no match found, print an error message and return NULL

  The arrays are PARALLEL -- names[0] corresponds to creators[0],
  names[1] corresponds to creators[1], etc.


--- main.cpp ---

  Tests all the Intern functionality.

  Test 1: Intern creates shrubbery creation
    - Creates a ShrubberyCreationForm via the Intern
    - Signs it with Bob (grade 1)
    - Executes it (creates "home_shrubbery" file)
    - Deletes the form (memory management!)

  Test 2: Intern creates robotomy request
    - Creates a RobotomyRequestForm via the Intern
    - Signs and executes it with Alice (grade 1)
    - Deletes the form

  Test 3: Intern creates presidential pardon
    - Creates a PresidentialPardonForm via the Intern
    - Signs and executes it with President (grade 1)
    - Deletes the form

  Test 4: Intern creates unknown form
    - Tries to create "tax return" (not a known form name)
    - Expected: Intern prints error, returns NULL
    - Code checks: if (!form) -> prints "No form created."

  Test 5: Copy intern
    - Creates an Intern, copies it
    - Uses the COPY to create a form
    - Expected: Works normally (the copy is identical)

  Test 6: Full workflow
    - Creates all three form types using one Intern
    - Signs and executes all three with Boss (grade 1)
    - Deletes all three forms
    - This is the "complete" test showing everything working together


========================================================================
11. HOW TO COMPILE AND RUN
========================================================================

  Step 1: Compile
    Type: make

  Step 2: Run
    Type: ./bureaucrat

  Other commands:
    make clean     -> Removes .o files
    make fclean    -> Removes .o files AND executable
    make re        -> Full rebuild


========================================================================
12. WHAT YOU WILL SEE WHEN YOU RUN IT
========================================================================

  --- Test 1: Intern creates shrubbery creation ---
  Intern creates shrubbery creation
  ShrubberyCreationForm signed: no, sign grade: 145, exec grade: 137
  Bob signed ShrubberyCreationForm
  Bob executed ShrubberyCreationForm
  (File "home_shrubbery" is created with ASCII trees)

  --- Test 2: Intern creates robotomy request ---
  Intern creates robotomy request
  RobotomyRequestForm signed: no, sign grade: 72, exec grade: 45
  Alice signed RobotomyRequestForm
  Alice executed RobotomyRequestForm
  * DRILLING NOISES *
  Bender has been robotomized successfully
  (or "The robotomy of Bender failed" -- it's random)

  --- Test 3: Intern creates presidential pardon ---
  Intern creates presidential pardon
  PresidentialPardonForm signed: no, sign grade: 25, exec grade: 5
  President signed PresidentialPardonForm
  President executed PresidentialPardonForm
  Ford Prefect has been pardoned by Zaphod Beeblebrox

  --- Test 4: Intern creates unknown form ---
  Intern cannot create form "tax return": unknown form name.
  No form created.

  --- Test 5: Copy intern ---
  Intern creates robotomy request
  RobotomyRequestForm signed: no, sign grade: 72, exec grade: 45

  --- Test 6: Full workflow ---
  Intern creates shrubbery creation
  Intern creates robotomy request
  Intern creates presidential pardon
  Boss signed ShrubberyCreationForm
  Boss executed ShrubberyCreationForm
  Boss signed RobotomyRequestForm
  Boss executed RobotomyRequestForm
  * DRILLING NOISES *
  Bender has been robotomized successfully
  Boss signed PresidentialPardonForm
  Boss executed PresidentialPardonForm
  Arthur Dent has been pardoned by Zaphod Beeblebrox


========================================================================
13. COMMON MISTAKES AND TIPS
========================================================================

  1. Forgetting to delete the form after use
     - Every "new" must have a matching "delete"
     - Forgetting causes memory leaks
     - Use "delete form;" when you're done with it

  2. Not checking if makeForm() returned NULL
     - Always check: if (form) { ... delete form; }
     - If you don't check and form is NULL, dereferencing it
       (like *form) causes a crash

  3. Using the wrong form names (case-sensitive!)
     - Must be exactly: "shrubbery creation", "robotomy request",
       "presidential pardon"
     - "Shrubbery Creation" (capital S) would NOT work
     - "robotomyrequest" (no space) would NOT work

  4. Forgetting the static keyword on helper functions
     - Without static, the function pointers won't work correctly
     - The static keyword is required for the array of function
       pointers approach

  5. Not including all necessary headers in Intern.cpp
     - Need: ShrubberyCreationForm.hpp, RobotomyRequestForm.hpp,
       PresidentialPardonForm.hpp

  6. Confusing the pointer with the object
     - makeForm() returns a POINTER (*), not an object
     - You need to use -> to access methods, or * to dereference
     - form->getName() or (*form).getName()

  7. Using the Intern's copy constructor incorrectly
     - The copy constructor should work even though there's nothing
       to copy (the Intern has no data)

  8. Not seeding the random number generator
     - std::srand(std::time(NULL)) must be called in main()
     - Needed for RobotomyRequestForm's random behavior

  9. Deleting a form that was never created
     - If makeForm() returned NULL, do NOT try to delete it
     - Always check: if (form) delete form;

  10. Using "new" when you shouldn't
      - The Intern MUST use "new" because it returns a pointer
      - But elsewhere in your code, prefer stack allocation when
        possible (it's faster and safer)

========================================================================
