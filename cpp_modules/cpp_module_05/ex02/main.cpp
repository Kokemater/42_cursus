#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <cstdlib>
#include <ctime>

int	main(void)
{
	std::srand(std::time(NULL));

	std::cout << "--- Test 1: Shrubbery Creation ---" << std::endl;
	try
	{
		Bureaucrat bob("Bob", 1);
		ShrubberyCreationForm shrub("home");
		std::cout << shrub << std::endl;
		bob.signForm(shrub);
		bob.executeForm(shrub);
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 2: Robotomy Request (multiple attempts) ---" << std::endl;
	try
	{
		Bureaucrat alice("Alice", 1);
		RobotomyRequestForm robot("Bender");
		alice.signForm(robot);
		for (int i = 0; i < 4; i++)
			alice.executeForm(robot);
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 3: Presidential Pardon ---" << std::endl;
	try
	{
		Bureaucrat president("Zaphod", 1);
		PresidentialPardonForm pardon("Ford Prefect");
		std::cout << pardon << std::endl;
		president.signForm(pardon);
		president.executeForm(pardon);
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 4: Execute unsigned form ---" << std::endl;
	try
	{
		Bureaucrat dave("Dave", 1);
		ShrubberyCreationForm shrub("garden");
		dave.executeForm(shrub);
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 5: Sign with low grade ---" << std::endl;
	try
	{
		Bureaucrat eve("Eve", 100);
		PresidentialPardonForm pardon("Arthur Dent");
		eve.signForm(pardon);
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 6: Execute with low grade ---" << std::endl;
	try
	{
		Bureaucrat eve("Eve", 140);
		ShrubberyCreationForm shrub("office");
		Bureaucrat boss("Boss", 1);
		boss.signForm(shrub);
		eve.executeForm(shrub);
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 7: Invalid form grades ---" << std::endl;
	try
	{
		ShrubberyCreationForm shrub("test");
		(void)shrub;
		std::cout << "ShrubberyCreationForm: valid grades (145/137)" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}
	try
	{
		RobotomyRequestForm robot("test");
		(void)robot;
		std::cout << "RobotomyRequestForm: valid grades (72/45)" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}
	try
	{
		PresidentialPardonForm pardon("test");
		(void)pardon;
		std::cout << "PresidentialPardonForm: valid grades (25/5)" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return (0);
}
