Exercise 02: No, you need form 28B, not 28C...

Objective:
  Create three concrete form classes derived from an abstract base
  class AForm. Each form performs a specific action when executed.

Abstract Base Class: AForm
  Attributes (private):
    - const std::string _name      : form name
    - bool _signed                 : signed status
    - const int _signGrade         : grade required to sign
    - const int _execGrade         : grade required to execute

  Member Functions:
    - getName()       : returns the name
    - getSigned()     : returns signed status
    - getSignGrade()  : returns sign grade
    - getExecGrade()  : returns exec grade
    - beSigned()      : signs form if bureaucrat grade is high enough
    - execute()       : checks requirements, then calls action()
    - action()        : pure virtual function (implemented by subclasses)

Concrete Classes:
  1. ShrubberyCreationForm (sign: 145, exec: 137)
     - Creates <target>_shrubbery file with ASCII trees

  2. RobotomyRequestForm (sign: 72, exec: 45)
     - Makes drilling noises, 50% success rate

  3. PresidentialPardonForm (sign: 25, exec: 5)
     - Informs target has been pardoned by Zaphod Beeblebrox

Class: Bureaucrat (updated)
  New Member Function:
    - executeForm() : attempts to execute form, prints success/failure

Files:
  - Bureaucrat.hpp/cpp           : Bureaucrat class
  - AForm.hpp/cpp                : Abstract Form base class
  - ShrubberyCreationForm.hpp/cpp
  - RobotomyRequestForm.hpp/cpp
  - PresidentialPardonForm.hpp/cpp
  - main.cpp                     : tests
  - Makefile

Compilation:
  make        -> builds the executable
  make clean  -> removes object files
  make fclean -> removes object files and executable
  make re     -> rebuilds everything

Testing:
  Run ./bureaucrat after building to see all test cases.
