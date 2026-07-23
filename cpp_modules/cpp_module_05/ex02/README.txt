========================================================================
  EXERCISE 02: No, you need form 28B, not 28C...
========================================================================

TABLE OF CONTENTS
-----------------
  1. What is this exercise about?
  2. Quick recap of ex00 and ex01
  3. What is "inheritance"?
  4. What is an "abstract class"?
  5. What is a "pure virtual function"?
  6. The AForm class (abstract base class)
  7. The three concrete form classes
  8. How execution works
  9. The Bureaucrat update: executeForm()
  10. Complete class diagrams
  11. File-by-file explanation
  12. How to compile and run
  13. What you will see when you run it
  14. Common mistakes and tips


========================================================================
1. WHAT IS THIS EXERCISE ABOUT?
========================================================================

In ex00, we created a Bureaucrat (a person with a rank).
In ex01, we added Form (a document that can be signed).

In ex02, we make forms MORE INTERESTING by adding:
  - Different TYPES of forms (like different types of documents)
  - Each type does something DIFFERENT when executed
  - Forms can now be EXECUTED (not just signed)

This introduces two important C++ concepts:
  - INHERITANCE: One class can "inherit" from another class
  - ABSTRACT CLASSES: A class that cannot be instantiated directly


========================================================================
2. QUICK RECAP OF EX00 AND EX01
========================================================================

  Bureaucrat:
    - Has a name and grade (1-150)
    - Can increment/decrement grade
    - Can sign forms (signForm method)

  Form (from ex01):
    - Has a name, signed status, and two grade requirements
    - Can be signed by a bureaucrat with high enough grade
    - has beSigned() and signForm() methods

  What's new in ex02:
    - Form becomes AForm (Abstract Form) -- a base class
    - Three new form types INHERIT from AForm
    - Each form type has its own unique ACTION when executed
    - Bureaucrat gets a new method: executeForm()


========================================================================
3. WHAT IS "INHERITANCE"?
========================================================================

Inheritance is like a family tree. A child class INHERITS everything
from its parent class, and can ADD or OVERRIDE things.

Think of it like this:

  ANIMAL (parent class)
    - Has: name, age
    - Can: eat(), sleep()

  DOG (child class, inherits from ANIMAL)
    - Has: all of ANIMAL's stuff (name, age)
    - Can: all of ANIMAL's stuff (eat, sleep) PLUS bark()
    - Can also: OVERRIDE eat() to eat dog food specifically

In C++, inheritance looks like this:

  class Animal
  {
  public:
      void eat();
      void sleep();
  protected:
      std::string name;
      int age;
  };

  class Dog : public Animal    // <-- Dog inherits from Animal
  {
  public:
      void bark();            // <-- Dog adds its own method
  };

The "public" before Animal means Dog inherits Animal's public
and protected members as public. (Don't worry about the details
of "protected" for now -- just know it means "accessible to
child classes but not to the outside world").

WHAT THIS MEANS IN PRACTICE:
  Dog rex;
  rex.eat();      // Works! (inherited from Animal)
  rex.sleep();    // Works! (inherited from Animal)
  rex.bark();     // Works! (Dog's own method)
  rex.name;       // Works! (inherited from Animal, if public/protected)


========================================================================
4. WHAT IS AN "ABSTRACT CLASS"?
========================================================================

An abstract class is a class that CANNOT be used to create objects
directly. It is meant to be a TEMPLATE for other classes.

Think of it like this:
  - "Shape" is abstract. You cannot draw a generic "shape".
    You can only draw specific shapes: circle, square, triangle.
  - "Vehicle" is abstract. You cannot drive a generic "vehicle".
    You can only drive a car, motorcycle, truck, etc.

In C++, a class becomes abstract when it has at least one PURE
VIRTUAL FUNCTION (see next section).

WHY USE ABSTRACT CLASSES?
  - To define a common interface (common methods) for related classes
  - To force child classes to implement certain methods
  - To prevent creating meaningless generic objects


========================================================================
5. WHAT IS A "PURE VIRTUAL FUNCTION"?
========================================================================

A pure virtual function is a function that has NO implementation
in the base class. It MUST be implemented by child classes.

In C++, it is declared like this:

  class AForm
  {
  public:
      virtual void action() const = 0;
      //                     ^^^
      //    The "= 0" means "pure virtual"
      //    This function has NO body in AForm
      //    Child classes MUST implement it
  };

The "virtual" keyword means: "This method might be overridden
by child classes. When called, use the CHILD's version, not
the parent's version."

The "= 0" at the end means: "This is pure virtual. There is no
implementation here. Child classes MUST provide their own."

WHAT HAPPENS IF YOU TRY TO CREATE AN OBJECT OF AN ABSTRACT CLASS?

  AForm form("test", 1, 1);   // COMPILER ERROR!
  // AForm is abstract, you cannot create an AForm object

  But you CAN create objects of child classes:
  ShrubberyCreationForm shrub("home");   // OK! This is concrete
  RobotomyRequestForm robot("Bender");   // OK! This is concrete


========================================================================
6. THE AFORM CLASS (ABSTRACT BASE CLASS)
========================================================================

AForm is the ABSTRACT base class that all specific forms inherit from.
It is like a "template" for all forms.

  ┌──────────────────────────────────────────────────────────────┐
  │                     AFORM (abstract)                        │
  ├──────────────────────────────────────────────────────────────┤
  │ PRIVATE:                                                    │
  │   const std::string _name                                   │
  │   bool _signed                                              │
  │   const int _signGrade                                      │
  │   const int _execGrade                                      │
  │   virtual void action() const = 0;   <-- PURE VIRTUAL      │
  ├──────────────────────────────────────────────────────────────┤
  │ PUBLIC:                                                     │
  │   AForm()                                                  │
  │   AForm(name, signGrade, execGrade)                         │
  │   AForm(const AForm &src)                                   │
  │   virtual ~AForm()              <-- NOTE: virtual destructor│
  │   operator=(const AForm &rhs)                               │
  │   getName() const -> const std::string&                     │
  │   getSigned() const -> bool                                 │
  │   getSignGrade() const -> int                               │
  │   getExecGrade() const -> int                               │
  │   beSigned(const Bureaucrat &b) -> void                     │
  │   execute(const Bureaucrat &executor) -> void  <-- NEW!     │
  │   class GradeTooHighException                               │
  │   class GradeTooLowException                                │
  │   class FormNotSignedException     <-- NEW!                 │
  └──────────────────────────────────────────────────────────────┘

KEY DIFFERENCES FROM ex01's Form:

  1. Class name is AForm (not Form)
     - The "A" stands for "Abstract"

  2. Has a PURE VIRTUAL FUNCTION:
     virtual void action() const = 0;
     - This makes AForm abstract
     - Child classes MUST implement action()

  3. Has a VIRTUAL DESTRUCTOR:
     virtual ~AForm();
     - This is VERY IMPORTANT for inheritance
     - When you delete a child class through a base class pointer,
       the virtual destructor ensures the child's destructor is called
     - Without "virtual", only the base destructor would run,
       causing memory leaks

  4. Has a NEW exception class:
     FormNotSignedException
     - Thrown when you try to execute a form that hasn't been signed

  5. Has a NEW method:
     execute(const Bureaucrat &executor) const
     - This checks if the form is signed and if the executor has
       a high enough grade, then calls action()

  6. The action() function is PRIVATE
     - Only the AForm class and its friends can call it
     - The execute() method calls action() internally
     - This prevents external code from calling action() directly


THE execute() METHOD IN DETAIL:

  void AForm::execute(const Bureaucrat &executor) const
  {
      if (!_signed)
          throw AForm::FormNotSignedException();
      if (executor.getGrade() > _execGrade)
          throw AForm::GradeTooLowException();
      action();
  }

  Steps:
    1. Check if the form is signed. If not, throw FormNotSignedException.
    2. Check if the executor's grade is high enough. If not, throw
       GradeTooLowException.
    3. If both checks pass, call action() (the pure virtual function).

  The action() method is implemented differently by each child class.


========================================================================
7. THE THREE CONCRETE FORM CLASSES
========================================================================

These are the "real" forms that can actually be created and used.
Each one inherits from AForm and implements its own action().

--- 7a. ShrubberyCreationForm ---

  PURPOSE: Creates a file containing ASCII art of trees.

  NAME REQUIREMENTS:
    - Sign grade: 145 (almost anyone can sign it)
    - Exec grade: 137 (most people can execute it)

  WHAT HAPPENS WHEN EXECUTED:
    - Creates a file named "<target>_shrubbery"
    - Fills it with ASCII art trees like this:

              ,
             _\/_
          ,  /  \  ,
         /\/    \/\
        /  \    /  \
       /    \  /    \
      /      \/      \
             ||
             ||
             ||
            _||_
           |____|

    - The <target> is whatever you specify (e.g., "home", "garden")
    - So if target is "home", it creates "home_shrubbery"

  EXAMPLE:
    ShrubberyCreationForm shrub("home");
    Bureaucrat bob("Bob", 1);
    bob.signForm(shrub);       // Signs the form
    bob.executeForm(shrub);    // Creates home_shrubbery file

  FILES NEEDED:
    - #include <fstream> (for file creation)
    - The action() method uses std::ofstream to create and write the file


--- 7b. RobotomyRequestForm ---

  PURPOSE: "Robotomizes" a target (a humorous procedure from
  "The Hitchhiker's Guide to the Galaxy").

  GRADE REQUIREMENTS:
    - Sign grade: 72 (requires a mid-level bureaucrat)
    - Exec grade: 45 (requires a fairly high-ranking bureaucrat)

  WHAT HAPPENS WHEN EXECUTED:
    - Prints drilling noises:
        "* DRILLING NOISES *"
        "BZZZZZZZT!"
    - Then, with a 50% success rate:
        - 50% chance: "<target> has been robotomized successfully"
        - 50% chance: "The robotomy of <target> failed"

  EXAMPLE:
    RobotomyRequestForm robot("Bender");
    Bureaucrat alice("Alice", 1);
    alice.signForm(robot);
    alice.executeForm(robot);
    // Output might be:
    // "* DRILLING NOISES *"
    // "Bender has been robotomized successfully"
    // or:
    // "* DRILLING NOISES *"
    // "The robotomy of Bender failed"

  IMPORTANT: The result is RANDOM. Each execution has a 50/50
  chance of success or failure. This is achieved using std::rand()
  and std::srand() for random number generation.

  HOW THE RANDOMNESS WORKS:
    - std::srand(std::time(NULL)) seeds the random number generator
      with the current time (called once at the start of main)
    - std::rand() generates a random number
    - if (std::rand() % 2) picks either 0 or 1 (50/50)


--- 7c. PresidentialPardonForm ---

  PURPOSE: Informs the target that they have been pardoned by
  the President of the Galaxy (Zaphod Beeblebrox from "The
  Hitchhiker's Guide to the Galaxy").

  GRADE REQUIREMENTS:
    - Sign grade: 25 (requires a high-ranking bureaucrat)
    - Exec grade: 5 (requires a very high-ranking bureaucrat,
      almost the top)

  WHAT HAPPENS WHEN EXECUTED:
    - Prints: "<target> has been pardoned by Zaphod Beeblebrox"

  EXAMPLE:
    PresidentialPardonForm pardon("Ford Prefect");
    Bureaucrat president("Zaphod", 1);
    president.signForm(pardon);
    president.executeForm(pardon);
    // Output: "Ford Prefect has been pardoned by Zaphod Beeblebrox"

  This is the simplest of the three forms -- it just prints a
  message. No files, no randomness.


========================================================================
8. HOW EXECUTION WORKS (STEP BY STEP)
========================================================================

When a bureaucrat tries to execute a form, here is the full
sequence of events:

  STEP 1: Bureaucrat::executeForm(form) is called
    - This is the new method on Bureaucrat
    - It wraps the form's execute() in a try/catch block

  STEP 2: form.execute(bureaucrat) is called
    - Inside AForm::execute(), three checks happen:

    CHECK 1: Is the form signed?
      if (!_signed)
          throw FormNotSignedException();
      - If the form hasn't been signed yet, execution fails

    CHECK 2: Does the executor have a high enough grade?
      if (executor.getGrade() > _execGrade)
          throw GradeTooLowException();
      - Remember: lower number = higher rank
      - So executor's grade must be <= execGrade

    CHECK 3: Call the action()
      action();
      - This calls the SPECIFIC implementation in the child class
      - Each child class does something different

  STEP 3: If any check fails, the exception is caught by
    executeForm() and a friendly message is printed

  STEP 4: If all checks pass, the action is performed and
    a success message is printed

  VISUAL FLOW:
  ┌──────────────────────────────────────────────────────────┐
  │  bob.executeForm(shrub)                                  │
  │       |                                                  │
  │       v                                                  │
  │  AForm::execute(bob)                                     │
  │       |                                                  │
  │       +-- Is form signed? --NO--> throw FormNotSigned    │
  │       |                                                  │
  │       +-- Is grade high enough? --NO--> throw TooLow     │
  │       |                                                  │
  │       +-- Call action()                                  │
  │              |                                           │
  │              +-- ShrubberyCreationForm::action()         │
  │              |   -> Creates ASCII tree file              │
  │              |                                           │
  │              +-- OR RobotomyRequestForm::action()        │
  │              |   -> Prints drill noises, 50% success     │
  │              |                                           │
  │              +-- OR PresidentialPardonForm::action()     │
  │                  -> Prints pardon message                │
  └──────────────────────────────────────────────────────────┘


========================================================================
9. THE BUREAUCRAT UPDATE: executeForm()
========================================================================

The Bureaucrat class gains a new method in ex02:

  void executeForm(const AForm &form) const;

  Implementation:
    void Bureaucrat::executeForm(const AForm &form) const
    {
        try
        {
            form.execute(*this);
            std::cout << _name << " executed " << form.getName()
                      << std::endl;
        }
        catch (std::exception &e)
        {
            std::cout << _name << " couldn't execute " << form.getName()
                      << " because " << e.what() << std::endl;
        }
    }

  This is very similar to signForm() -- it tries to execute the form,
  and prints a success or failure message.

  Note: The parameter is "const AForm &" -- it takes a reference to
  the abstract base class. Thanks to polymorphism, it will work with
  any child class (ShrubberyCreationForm, RobotomyRequestForm, or
  PresidentialPardonForm).


========================================================================
10. COMPLETE CLASS DIAGRAMS
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
  │   signForm(Form &form) const -> void                    │
  │   executeForm(const AForm &form) const -> void  <-- NEW │
  │   class GradeTooHighException                           │
  │   class GradeTooLowException                            │
  └──────────────────────────────────────────────────────────┘

  ┌──────────────────────────────────────────────────────────┐
  │              AFORM (abstract, cannot instantiate)       │
  ├──────────────────────────────────────────────────────────┤
  │ PRIVATE:                                                │
  │   const std::string _name                               │
  │   bool _signed                                          │
  │   const int _signGrade                                  │
  │   const int _execGrade                                  │
  │   virtual void action() const = 0;  <-- PURE VIRTUAL   │
  ├──────────────────────────────────────────────────────────┤
  │ PUBLIC:                                                 │
  │   AForm()                                              │
  │   AForm(name, signGrade, execGrade)                     │
  │   AForm(const AForm &src)                               │
  │   virtual ~AForm()                                      │
  │   operator=(const AForm &rhs)                           │
  │   getName() const -> const std::string&                 │
  │   getSigned() const -> bool                             │
  │   getSignGrade() const -> int                           │
  │   getExecGrade() const -> int                           │
  │   beSigned(const Bureaucrat &b) -> void                 │
  │   execute(const Bureaucrat &executor) -> void           │
  │   class GradeTooHighException                           │
  │   class GradeTooLowException                            │
  │   class FormNotSignedException                          │
  └──────────────────────────────────────────────────────────┘

          ┌──────────────────────┐
          │       AFORM          │
          │    (abstract)        │
          └──────────┬───────────┘
                     │ inherits
        ┌────────────┼────────────────┐
        │            │                │
        v            v                v
  ┌───────────┐ ┌───────────┐ ┌───────────────────┐
  │ Shrubbery │ │ Robotomy  │ │ Presidential      │
  │ Creation  │ │ Request   │ │ Pardon            │
  │ Form      │ │ Form      │ │ Form              │
  └───────────┘ └───────────┘ └───────────────────┘
  sign: 145     sign: 72      sign: 25
  exec: 137     exec: 45      exec: 5

  Each concrete class:
    - Inherits _name, _signed, _signGrade, _execGrade from AForm
    - Inherits beSigned() and execute() from AForm
    - Adds a private _target attribute
    - Adds getTarget() method
    - Implements action() with its own unique behavior


========================================================================
11. FILE-BY-FILE EXPLANATION
========================================================================

--- AForm.hpp ---

  The abstract base class declaration.

  Key points:
    - Same attributes as ex01's Form (_name, _signed, _signGrade, _execGrade)
    - Has virtual destructor: virtual ~AForm()
    - Has pure virtual function: virtual void action() const = 0;
    - Has new method: execute(const Bureaucrat &executor) const
    - Has new exception: FormNotSignedException

  The action() function is PRIVATE and pure virtual.
  This means:
    - Only AForm and its friends can call action()
    - Child classes MUST implement action()
    - External code cannot call action() directly


--- AForm.cpp ---

  Implements the AForm methods.

  Key implementation:
    execute():
      void AForm::execute(const Bureaucrat &executor) const
      {
          if (!_signed)
              throw FormNotSignedException();
          if (executor.getGrade() > _execGrade)
              throw GradeTooLowException();
          action();
      }

    - Validates before calling action()
    - action() is called at the end -- it will use the child's version
      thanks to the "virtual" keyword

  beSigned():
    Same as ex01 -- checks if bureaucrat's grade is good enough.


--- ShrubberyCreationForm.hpp / .cpp ---

  Header:
    class ShrubberyCreationForm : public AForm
    {
    public:
        ShrubberyCreationForm(void);
        ShrubberyCreationForm(const std::string &target);
        ShrubberyCreationForm(const ShrubberyCreationForm &src);
        ~ShrubberyCreationForm(void);
        ShrubberyCreationForm &operator=(const ShrubberyCreationForm &rhs);
        const std::string &getTarget() const;
    private:
        std::string _target;
        void action() const;
    };

  Implementation of action():
    void ShrubberyCreationForm::action() const
    {
        std::ofstream file((_target + "_shrubbery").c_str());
        // ... writes ASCII trees to the file ...
        file.close();
    }

  How the file creation works:
    - _target + "_shrubbery" concatenates the strings
      e.g., "home" + "_shrubbery" = "home_shrubbery"
    - .c_str() converts std::string to a C-style string (const char*)
      because std::ofstream needs a C-style string
    - std::ofstream creates/opens a file for writing
    - << is used to write text to the file (same as cout, but to file)
    - file.close() closes the file

  Constructor:
    ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
        : AForm("ShrubberyCreationForm", 145, 137), _target(target)
    {
    }
    - Calls AForm's constructor with fixed name and grades
    - Sets the _target to the provided target
    - The grades 145/137 are HARDCODED -- every shrubbery form
      has the same requirements


--- RobotomyRequestForm.hpp / .cpp ---

  Header:
    class RobotomyRequestForm : public AForm
    {
    public:
        RobotomyRequestForm(void);
        RobotomyRequestForm(const std::string &target);
        RobotomyRequestForm(const RobotomyRequestForm &src);
        ~RobotomyRequestForm(void);
        RobotomyRequestForm &operator=(const RobotomyRequestForm &rhs);
        const std::string &getTarget() const;
    private:
        std::string _target;
        void action() const;
    };

  Implementation of action():
    void RobotomyRequestForm::action() const
    {
        std::cout << "* DRILLING NOISES *" << std::endl;
        if (std::rand() % 2)
            std::cout << _target << " has been robotomized successfully"
                      << std::endl;
        else
            std::cout << "The robotomy of " << _target << " failed"
                      << std::endl;
    }

  How the randomness works:
    - std::rand() returns a random integer
    - % 2 gives the remainder when divided by 2, which is 0 or 1
    - 0 is "falsy" in C++, 1 is "truthy"
    - So if (std::rand() % 2) is true 50% of the time

  IMPORTANT: std::srand(std::time(NULL)) must be called ONCE at
  the start of the program to seed the random number generator.
  Without this, the "random" results would be the same every time.


--- PresidentialPardonForm.hpp / .cpp ---

  Header:
    class PresidentialPardonForm : public AForm
    {
    public:
        PresidentialPardonForm(void);
        PresidentialPardonForm(const std::string &target);
        PresidentialPardonForm(const PresidentialPardonForm &src);
        ~PresidentialPardonForm(void);
        PresidentialPardonForm &operator=(const PresidentialPardonForm &rhs);
        const std::string &getTarget() const;
    private:
        std::string _target;
        void action() const;
    };

  Implementation of action():
    void PresidentialPardonForm::action() const
    {
        std::cout << _target << " has been pardoned by Zaphod Beeblebrox"
                  << std::endl;
    }

  The simplest implementation -- just prints a message.


--- Bureaucrat.hpp / .cpp ---

  Same as ex01, with the addition of:
    void executeForm(const AForm &form) const;

  Note the parameter type: const AForm &
  This takes a REFERENCE to the abstract base class. Because of
  polymorphism, it works with any child class.


--- main.cpp ---

  Tests all the functionality.

  Test 1: Shrubbery Creation
    - Bob (grade 1) signs and executes ShrubberyCreationForm
    - Creates "home_shrubbery" file with ASCII trees

  Test 2: Robotomy Request (multiple attempts)
    - Alice (grade 1) signs and executes RobotomyRequestForm 4 times
    - Shows the 50/50 success rate
    - Some will succeed, some will fail (randomly)

  Test 3: Presidential Pardon
    - Zaphod (grade 1) signs and executes PresidentialPardonForm
    - Prints pardon message for "Ford Prefect"

  Test 4: Execute unsigned form
    - Dave (grade 1) tries to execute a ShrubberyCreationForm
      that hasn't been signed
    - Expected: FormNotSignedException

  Test 5: Sign with low grade
    - Eve (grade 100) tries to sign PresidentialPardonForm
      (requires grade 25)
    - Expected: GradeTooLowException

  Test 6: Execute with low grade
    - Boss (grade 1) signs ShrubberyCreationForm (sign: 145)
    - Eve (grade 140) tries to execute it (exec: 137)
    - 140 <= 137? NO! -> GradeTooLowException

  Test 7: Invalid form grades
    - Shows that each form type has its own fixed grade requirements
    - ShrubberyCreationForm: 145/137
    - RobotomyRequestForm: 72/45
    - PresidentialPardonForm: 25/5


========================================================================
12. HOW TO COMPILE AND RUN
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
13. WHAT YOU WILL SEE WHEN YOU RUN IT
========================================================================

  --- Test 1: Shrubbery Creation ---
  ShrubberyCreationForm signed: no, sign grade: 145, exec grade: 137
  Bob signed ShrubberyCreationForm
  Bob executed ShrubberyCreationForm
  (A file called "home_shrubbery" is created with ASCII trees)

  --- Test 2: Robotomy Request (multiple attempts) ---
  Alice signed RobotomyRequestForm
  Alice executed RobotomyRequestForm
  * DRILLING NOISES *
  Bender has been robotomized successfully
  Alice executed RobotomyRequestForm
  * DRILLING NOISES *
  The robotomy of Bender failed
  Alice executed RobotomyRequestForm
  * DRILLING NOISES *
  Bender has been robotomized successfully
  Alice executed RobotomyRequestForm
  * DRILLING NOISES *
  The robotomy of Bender failed

  --- Test 3: Presidential Pardon ---
  PresidentialPardonForm signed: no, sign grade: 25, exec grade: 5
  Zaphod signed PresidentialPardonForm
  Zaphod executed PresidentialPardonForm
  Ford Prefect has been pardoned by Zaphod Beeblebrox

  --- Test 4: Execute unsigned form ---
  Dave couldn't execute ShrubberyCreationForm because form not signed

  --- Test 5: Sign with low grade ---
  Eve couldn't sign PresidentialPardonForm because grade too low

  --- Test 6: Execute with low grade ---
  Boss signed ShrubberyCreationForm
  Eve couldn't execute ShrubberyCreationForm because grade too low

  --- Test 7: Invalid form grades ---
  ShrubberyCreationForm: valid grades (145/137)
  RobotomyRequestForm: valid grades (72/45)
  PresidentialPardonForm: valid grades (25/5)


========================================================================
14. COMMON MISTAKES AND TIPS
========================================================================

  1. Forgetting "virtual" on the destructor
     - MUST be: virtual ~AForm()
     - Without it, deleting a child through a base pointer causes
       undefined behavior (usually memory leaks)

  2. Forgetting "= 0" on action()
     - Without it, AForm is NOT abstract and you can create AForm objects
     - The whole point is that AForm cannot be instantiated

  3. Making action() public
     - It should be PRIVATE in AForm
     - Only execute() should call action()
     - Child classes can access private members of their parent

  4. Not calling the parent constructor in child constructors
     - Each child class MUST call AForm's constructor in its initializer
       list: AForm("name", signGrade, execGrade)

  5. Forgetting to include <fstream> for ShrubberyCreationForm
     - Needed for std::ofstream (file creation)

  6. Forgetting std::srand(std::time(NULL)) in main()
     - Without it, RobotomyRequestForm always gives the same result

  7. Using the wrong grade requirements
     - ShrubberyCreationForm: 145/137
     - RobotomyRequestForm: 72/45
     - PresidentialPardonForm: 25/5
     - These are HARDCODED in each class's constructor

  8. Not checking for _signed before calling action()
     - The execute() method in AForm checks this
     - Do NOT skip this check in your implementation

  9. Confusing the two grade checks
     - beSigned() checks: bureaucrat's grade <= _signGrade
     - execute() checks: executor's grade <= _execGrade
     - These are DIFFERENT grades!

  10. Forgetting that action() is PRIVATE in AForm
      - Child classes CAN call it (because they inherit from AForm)
      - External code CANNOT call it directly
      - This is correct behavior -- only execute() should call action()

========================================================================
