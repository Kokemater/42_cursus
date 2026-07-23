========================================================================
  EXERCISE 01: Form up, maggots!
========================================================================

TABLE OF CONTENTS
-----------------
  1. What is this exercise about?
  2. Quick recap of ex00 (Bureaucrat)
  3. What is a "Form"?
  4. How does signing work?
  5. What changed in Bureaucrat?
  6. The complete class diagrams
  7. File-by-file explanation
  8. How to compile and run
  9. What you will see when you run it
  10. Common mistakes and tips


========================================================================
1. WHAT IS THIS EXERCISE ABOUT?
========================================================================

In the previous exercise (ex00), we created a "Bureaucrat" -- a
person who works in an office with a rank (grade).

In this exercise (ex01), we add a new concept: FORMS.

Imagine a real-life bureaucracy:
  - A bureaucrat (employee) needs to SIGN forms
  - Each form has requirements: only someone with a high enough
    rank is allowed to sign it
  - For example, a "Top Secret" form might require grade 1
    (only the boss can sign it), while a "Public Notice" might
    only require grade 150 (anyone can sign it)

So now we have TWO classes working together:
  1. Bureaucrat (the employee) -- from ex00, with a small addition
  2. Form (the document to be signed) -- NEW in this exercise


========================================================================
2. QUICK RECAP OF EX00 (BUREAUCRAT)
========================================================================

If you haven't done ex00, here is a quick reminder:

  Bureaucrat has:
    - _name (const string): The person's name (cannot change)
    - _grade (int): The person's rank, from 1 (highest) to 150 (lowest)

  Bureaucrat can:
    - getName(): Get the name
    - getGrade(): Get the grade
    - increment(): Promote (grade decreases by 1, e.g., 3 -> 2)
    - decrement(): Demote (grade increases by 1, e.g., 2 -> 3)

  Grade rules:
    - Grade 1 = highest rank (the boss)
    - Grade 150 = lowest rank (the intern)
    - Invalid grades (< 1 or > 150) throw exceptions

  The NEW addition in ex01 is:
    - signForm(Form &form): A method that lets the bureaucrat
      try to sign a form. More on this below.


========================================================================
3. WHAT IS A "FORM"?
========================================================================

A Form is a document that can be signed by a bureaucrat.

Think of it like a permission slip or an official document:
  - A tax form needs to be signed before you can file taxes
  - A building permit needs to be signed before you can build
  - A top-secret document needs to be signed by a general

FORM ATTRIBUTES (data stored inside a Form object):

  ┌──────────────────────┬────────────────────────────────────────┐
  │ Attribute            │ Description                            │
  ├──────────────────────┼────────────────────────────────────────┤
  │ _name (const string) │ The form's name. Cannot change after   │
  │                      │ creation (it's const).                 │
  ├──────────────────────┼────────────────────────────────────────┤
  │ _signed (bool)       │ Whether the form has been signed.      │
  │                      │ false = not signed, true = signed.     │
  │                      │ This CAN change (when someone signs).  │
  ├──────────────────────┼────────────────────────────────────────┤
  │ _signGrade (const    │ The MINIMUM grade a bureaucrat needs   │
  │         int)         │ to sign this form. For example, if     │
  │                      │ signGrade is 50, only a bureaucrat     │
  │                      │ with grade 50 or better (lower number) │
  │                      │ can sign it.                           │
  ├──────────────────────┼────────────────────────────────────────┤
  │ _execGrade (const    │ The MINIMUM grade a bureaucrat needs   │
  │         int)         │ to execute (use) this form. This is    │
  │                      │ not used in ex01, but will be in ex02. │
  └──────────────────────┴────────────────────────────────────────┘

  Note: Both _signGrade and _execGrade are const -- once a form
  is created, these requirements cannot be changed.

  Also note: These must be in the range 1 to 150, just like
  bureaucrat grades. Invalid values throw exceptions.


FORM METHODS (things a Form can do):

  ┌─────────────────────┬────────────────────────────────────────┐
  │ Method              │ Description                            │
  ├─────────────────────┼────────────────────────────────────────┤
  │ getName()           │ Returns the form's name                │
  ├─────────────────────┼────────────────────────────────────────┤
  │ getSigned()         │ Returns whether the form is signed     │
  │                     │ (true/false)                           │
  ├─────────────────────┼────────────────────────────────────────┤
  │ getSignGrade()      │ Returns the grade required to sign     │
  ├─────────────────────┼────────────────────────────────────────┤
  │ getExecGrade()      │ Returns the grade required to execute  │
  ├─────────────────────┼────────────────────────────────────────┤
  │ beSigned(bureaucrat)│ Attempts to sign the form. Checks if   │
  │                     │ the bureaucrat's grade is high enough.  │
  │                     │ If yes, marks form as signed.           │
  │                     │ If no, throws GradeTooLowException.     │
  └─────────────────────┴────────────────────────────────────────┘

  EXAMPLE OF beSigned():
    Form taxForm("Tax Form", 50, 100);
    Bureaucrat bob("Bob", 30);   // Bob has grade 30
    Bureaucrat eve("Eve", 100);  // Eve has grade 100

    taxForm.beSigned(bob);   // Bob has grade 30, which is <= 50
                             // So this WORKS. Form is now signed.

    taxForm.beSigned(eve);   // Eve has grade 100, which is > 50
                             // So this THROWS GradeTooLowException.


FORM CONSTRUCTORS:

  ┌──────────────────────────────────────────────────────────────┐
  │ Form()                                                      │
  │ - Default constructor                                       │
  │ - Sets name to "", signed to false, grades to 1 and 1       │
  ├──────────────────────────────────────────────────────────────┤
  │ Form(name, signGrade, execGrade)                            │
  │ - Parameterized constructor                                 │
  │ - Sets the name, sign grade, and exec grade                 │
  │ - signed starts as false                                    │
  │ - Validates both grades (must be 1-150)                     │
  ├──────────────────────────────────────────────────────────────┤
  │ Form(const Form &src)                                       │
  │ - Copy constructor                                          │
  │ - Creates a new Form that is an exact copy of src           │
  │ - Copies all attributes including signed status             │
  ├──────────────────────────────────────────────────────────────┤
  │ ~Form()                                                     │
  │ - Destructor                                                │
  │ - Called when the Form object is destroyed                   │
  └──────────────────────────────────────────────────────────────┘


========================================================================
4. HOW DOES SIGNING WORK?
========================================================================

There are TWO ways to sign a form:

  WAY 1: Using Bureaucrat::signForm()
    bob.signForm(taxForm);

    This is the "friendly" way. The bureaucrat tries to sign the
    form, and prints a message telling you if it worked or not.

    Internally, signForm() does this:
      1. Calls taxForm.beSigned(*this) to try to sign
      2. If it works: prints "Bob signed Tax Form"
      3. If it fails: prints "Bob couldn't sign Tax Form because..."

  WAY 2: Using Form::beSigned() directly
    taxForm.beSigned(bob);

    This is the "direct" way. You call beSigned() on the form
    directly, passing the bureaucrat as an argument.

    Internally, beSigned() does this:
      1. Checks if bob.getGrade() <= taxForm.getSignGrade()
         (Remember: lower number = higher rank)
      2. If bob's grade is good enough: sets _signed = true
      3. If bob's grade is too low: throws GradeTooLowException

  IMPORTANT DISTINCTION:
    - signForm() is on the BUREAUCRAT class (the person signs)
    - beSigned() is on the FORM class (the form gets signed)
    - They both achieve the same result, but from different perspectives


  VISUAL EXAMPLE:
  ┌──────────────────────────────────────────────────────────┐
  │  Form: "Tax Form"                                       │
  │  Sign Grade Required: 50                                │
  │  Signed: false                                          │
  │                                                          │
  │  Bureaucrat Bob (grade 30) calls signForm(taxForm)      │
  │  -> 30 <= 50? YES! -> Form becomes signed.             │
  │  Output: "Bob signed Tax Form"                          │
  │                                                          │
  │  Bureaucrat Eve (grade 100) calls signForm(taxForm)     │
  │  -> 100 <= 50? NO! -> GradeTooLowException thrown.     │
  │  Output: "Eve couldn't sign Tax Form because...         │
  │           grade too low"                                │
  └──────────────────────────────────────────────────────────┘


========================================================================
5. WHAT CHANGED IN BUREAUCRAT?
========================================================================

Compared to ex00, the Bureaucrat class has ONE new method:

  void signForm(Form &form) const;

This method:
  1. Takes a reference to a Form object
  2. Tries to call form.beSigned(*this) to sign the form
  3. Prints a success or failure message

The implementation looks something like this:

  void Bureaucrat::signForm(Form &form) const
  {
      try
      {
          form.beSigned(*this);
          std::cout << _name << " signed " << form.getName() << std::endl;
      }
      catch (std::exception &e)
      {
          std::cout << _name << " couldn't sign " << form.getName()
                    << " because " << e.what() << std::endl;
      }
  }

  Note the "const" at the end: this method promises not to modify
  the Bureaucrat (it only modifies the Form).

  Also note the "try/catch" block: it catches any exception that
  beSigned() might throw and prints a friendly message instead of
  crashing.


========================================================================
6. THE COMPLETE CLASS DIAGRAMS
========================================================================

  ┌──────────────────────────────────────────────────────────┐
  │                    BUREAUCRAT                           │
  ├──────────────────────────────────────────────────────────┤
  │ PRIVATE:                                                │
  │   const std::string _name                               │
  │   int _grade                                            │
  ├──────────────────────────────────────────────────────────┤
  │ PUBLIC:                                                 │
  │   Bureaucrat()                                          │
  │   Bureaucrat(name, grade)                               │
  │   Bureaucrat(const Bureaucrat &src)                     │
  │   ~Bureaucrat()                                         │
  │   operator=(const Bureaucrat &rhs)                      │
  │   getName() const -> const std::string&                 │
  │   getGrade() const -> int                               │
  │   increment() -> void                                   │
  │   decrement() -> void                                   │
  │   signForm(Form &form) const -> void   <-- NEW!         │
  │   class GradeTooHighException : public std::exception   │
  │   class GradeTooLowException : public std::exception    │
  └──────────────────────────────────────────────────────────┘

  ┌──────────────────────────────────────────────────────────┐
  │                      FORM                               │
  ├──────────────────────────────────────────────────────────┤
  │ PRIVATE:                                                │
  │   const std::string _name                               │
  │   bool _signed                                          │
  │   const int _signGrade                                  │
  │   const int _execGrade                                  │
  ├──────────────────────────────────────────────────────────┤
  │ PUBLIC:                                                 │
  │   Form()                                               │
  │   Form(name, signGrade, execGrade)                      │
  │   Form(const Form &src)                                 │
  │   ~Form()                                               │
  │   operator=(const Form &rhs)                            │
  │   getName() const -> const std::string&                 │
  │   getSigned() const -> bool                             │
  │   getSignGrade() const -> int                           │
  │   getExecGrade() const -> int                           │
  │   beSigned(const Bureaucrat &b) -> void                 │
  │   class GradeTooHighException : public std::exception   │
  │   class GradeTooLowException : public std::exception    │
  └──────────────────────────────────────────────────────────┘

  Note: The Form class has its OWN GradeTooHighException and
  GradeTooLowException. These are SEPARATE from the ones in
  Bureaucrat (different classes, even though they have the same name).


========================================================================
7. FILE-BY-FILE EXPLANATION
========================================================================

--- Bureaucrat.hpp ---

  Same as ex00, with ONE addition:

    # include "Form.hpp"           // <-- Forward declaration is enough
                                   //     for the .hpp, but we need the
                                   //     full include in the .cpp

    void signForm(Form &form) const;  // <-- NEW METHOD

  NOTE: We use "class Form;" as a forward declaration in Bureaucrat.hpp.
  This tells the compiler "Form exists, but we will define it later."
  We do NOT need to include the full Form.hpp in Bureaucrat.hpp because
  signForm only takes a reference (not a copy).

  In the .cpp file, we DO include Form.hpp because we need the full
  definition to call methods on the form.


--- Bureaucrat.cpp ---

  Same as ex00, with the addition of signForm():

    void Bureaucrat::signForm(Form &form) const
    {
        try
        {
            form.beSigned(*this);
            std::cout << _name << " signed " << form.getName()
                      << std::endl;
        }
        catch (std::exception &e)
        {
            std::cout << _name << " couldn't sign " << form.getName()
                      << " because " << e.what() << std::endl;
        }
    }

  Key points:
    - *this: Passes a reference to the current Bureaucrat object
    - The try/catch block handles the case where the grade is too low
    - Prints different messages for success vs failure


--- Form.hpp ---

  This is the blueprint for the Form class.

  Key elements:
    - Private attributes: _name, _signed, _signGrade, _execGrade
    - Public getters for all attributes
    - beSigned() method that takes a Bureaucrat reference
    - Two nested exception classes
    - Operator<< for printing

  The constructor takes name, signGrade, and execGrade.
  The signed status always starts as false.

  Note that _signed is NOT const -- it can change when the form
  is signed. But _name, _signGrade, and _execGrade ARE const.


--- Form.cpp ---

  Implements all the Form methods.

  Constructor:
    Form::Form(const std::string &name, int signGrade, int execGrade)
        : _name(name), _signed(false), _signGrade(signGrade),
          _execGrade(execGrade)
    {
        if (signGrade < 1 || execGrade < 1)
            throw Form::GradeTooHighException();
        if (signGrade > 150 || execGrade > 150)
            throw Form::GradeTooLowException();
    }

    - Uses initializer list to set all attributes
    - _signed starts as false (form is not signed yet)
    - Validates BOTH grades

  beSigned():
    void Form::beSigned(const Bureaucrat &bureaucrat)
    {
        if (bureaucrat.getGrade() > _signGrade)
            throw Form::GradeTooLowException();
        _signed = true;
    }

    - Checks if the bureaucrat's grade is GOOD ENOUGH
    - Remember: LOWER number = HIGHER rank
    - So: bureaucrat.getGrade() must be <= _signGrade
    - If not good enough: throws exception
    - If good enough: marks form as signed

  Operator<<:
    std::ostream &operator<<(std::ostream &o, const Form &rhs)
    {
        o << "Form " << rhs.getName()
          << ", signed: " << (rhs.getSigned() ? "yes" : "no")
          << ", sign grade: " << rhs.getSignGrade()
          << ", exec grade: " << rhs.getExecGrade();
        return (o);
    }

    - Prints the form's info in a readable format
    - Uses a ternary operator: (condition ? value_if_true : value_if_false)
    - Example output: "Form Tax Form, signed: yes, sign grade: 50,
                       exec grade: 100"


--- main.cpp ---

  Tests all the functionality of both Bureaucrat and Form.

  Test 1: Valid Form construction
    - Creates 3 forms with valid grades
    - Prints them all

  Test 2: Form grade too high
    - Creates a form with signGrade 0 (invalid)
    - Expected: GradeTooHighException

  Test 3: Form exec grade too high
    - Creates a form with execGrade 0 (invalid)
    - Expected: GradeTooHighException

  Test 4: Form grade too low
    - Creates a form with signGrade 151 (invalid)
    - Expected: GradeTooLowException

  Test 5: Sign form successfully
    - Bob (grade 50) tries to sign "Tax Form" (signGrade 50)
    - 50 <= 50? YES! -> Form gets signed
    - Expected: "Bob signed Tax Form"

  Test 6: Sign form grade too low
    - Charlie (grade 100) tries to sign "Top Secret" (signGrade 50)
    - 100 <= 50? NO! -> Exception thrown
    - Expected: "Charlie couldn't sign Top Secret because grade too low"

  Test 7: Direct beSigned
    - Dave (grade 1) calls beSigned() directly on "Building Permit"
    - 1 <= 10? YES! -> Form gets signed

  Test 8: Direct beSigned too low
    - Eve (grade 100) calls beSigned() on "Driver License" (signGrade 50)
    - 100 <= 50? NO! -> Exception thrown

  Test 9: Bureaucrat tests
    - Tests increment and decrement (same as ex00)


========================================================================
8. HOW TO COMPILE AND RUN
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
9. WHAT YOU WILL SEE WHEN YOU RUN IT
========================================================================

  --- Test 1: Valid Form construction ---
  Form Medium, signed: no, sign grade: 50, exec grade: 100
  Form Top secret, signed: no, sign grade: 1, exec grade: 1
  Form Public, signed: no, sign grade: 150, exec grade: 150

  --- Test 2: Form grade too high ---
  Exception: grade too high

  --- Test 3: Form exec grade too high ---
  Exception: grade too high

  --- Test 4: Form grade too low ---
  Exception: grade too low

  --- Test 5: Sign form successfully ---
  Bob, bureaucrat grade 50.
  Form Tax Form, signed: no, sign grade: 50, exec grade: 100
  Bob signed Tax Form
  Form Tax Form, signed: yes, sign grade: 50, exec grade: 100

  --- Test 6: Sign form grade too low ---
  Charlie, bureaucrat grade 100.
  Form Top Secret, signed: no, sign grade: 50, exec grade: 100
  Charlie couldn't sign Top Secret because grade too low

  --- Test 7: Direct beSigned ---
  Form Building Permit, signed: no, sign grade: 10, exec grade: 50
  Form Building Permit, signed: yes, sign grade: 10, exec grade: 50

  --- Test 8: Direct beSigned too low ---
  Form Driver License, signed: no, sign grade: 50, exec grade: 50
  Exception: grade too low

  --- Test 9: Bureaucrat tests ---
  Frank, bureaucrat grade 3.
  Frank, bureaucrat grade 2.
  Frank, bureaucrat grade 3.


========================================================================
10. COMMON MISTAKES AND TIPS
========================================================================

  1. Forgetting to include Form.hpp in Bureaucrat.cpp
     - The .hpp file only needs a forward declaration (class Form;)
     - The .cpp file needs the full include to call methods

  2. Reversing the grade comparison in beSigned()
     - WRONG: if (bureaucrat.getGrade() >= _signGrade) ...
     - RIGHT: if (bureaucrat.getGrade() > _signGrade) ...
     - Remember: LOWER number = HIGHER rank!
     - A bureaucrat with grade 10 CAN sign a form requiring grade 50

  3. Not initializing _signed to false in the constructor
     - A new form should always start as unsigned

  4. Forgetting the "const" on signForm()
     - signForm() does NOT modify the Bureaucrat, so it should be const

  5. Not validating both _signGrade and _execGrade in the constructor
     - Both must be in range 1-150

  6. Confusing signForm() with beSigned()
     - signForm() is on Bureaucrat (the person signs)
     - beSigned() is on Form (the form gets signed)
     - signForm() calls beSigned() internally

  7. Forgetting that _name, _signGrade, and _execGrade are const
     - These CANNOT be set in the constructor body
     - They MUST be set in the initializer list

  8. Not handling exceptions in signForm()
     - signForm() should catch exceptions and print friendly messages
     - It should NOT let exceptions propagate to main()

========================================================================
