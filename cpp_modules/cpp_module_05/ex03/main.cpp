#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"
#include <cstdlib>
#include <ctime>

int	main(void)
{
	std::srand(std::time(NULL));

	std::cout << "--- Test 1: Intern creates shrubbery creation ---" << std::endl;
	{
		Intern intern;
		AForm *form = intern.makeForm("shrubbery creation", "home");
		if (form)
		{
			std::cout << *form << std::endl;
			Bureaucrat bob("Bob", 1);
			bob.signForm(*form);
			bob.executeForm(*form);
			delete form;
		}
	}

	std::cout << "\n--- Test 2: Intern creates robotomy request ---" << std::endl;
	{
		Intern intern;
		AForm *form = intern.makeForm("robotomy request", "Bender");
		if (form)
		{
			std::cout << *form << std::endl;
			Bureaucrat alice("Alice", 1);
			alice.signForm(*form);
			alice.executeForm(*form);
			delete form;
		}
	}

	std::cout << "\n--- Test 3: Intern creates presidential pardon ---" << std::endl;
	{
		Intern intern;
		AForm *form = intern.makeForm("presidential pardon", "Ford Prefect");
		if (form)
		{
			std::cout << *form << std::endl;
			Bureaucrat president("President", 1);
			president.signForm(*form);
			president.executeForm(*form);
			delete form;
		}
	}

	std::cout << "\n--- Test 4: Intern creates unknown form ---" << std::endl;
	{
		Intern intern;
		AForm *form = intern.makeForm("tax return", "me");
		if (!form)
			std::cout << "No form created." << std::endl;
	}

	std::cout << "\n--- Test 5: Copy intern ---" << std::endl;
	{
		Intern original;
		Intern copy(original);
		AForm *form = copy.makeForm("robotomy request", "Leela");
		if (form)
		{
			std::cout << *form << std::endl;
			delete form;
		}
	}

	std::cout << "\n--- Test 6: Full workflow ---" << std::endl;
	{
		Intern intern;
		Bureaucrat boss("Boss", 1);
		AForm *shrub = intern.makeForm("shrubbery creation", "garden");
		AForm *robot = intern.makeForm("robotomy request", "Bender");
		AForm *pardon = intern.makeForm("presidential pardon", "Arthur Dent");

		if (shrub && robot && pardon)
		{
			boss.signForm(*shrub);
			boss.executeForm(*shrub);
			boss.signForm(*robot);
			boss.executeForm(*robot);
			boss.signForm(*pardon);
			boss.executeForm(*pardon);
		}
		delete shrub;
		delete robot;
		delete pardon;
	}

	return (0);
}
