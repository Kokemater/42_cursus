#include "Bureaucrat.hpp"
#include "Form.hpp"

int	main(void)
{
	std::cout << "--- Test 1: Valid Form construction ---" << std::endl;
	try
	{
		Form a("Medium", 50, 100);
		Form b("Top secret", 1, 1);
		Form c("Public", 150, 150);
		std::cout << a << std::endl;
		std::cout << b << std::endl;
		std::cout << c << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 2: Form grade too high ---" << std::endl;
	try
	{
		Form d("Bad Form", 0, 100);
		std::cout << d << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 3: Form exec grade too high ---" << std::endl;
	try
	{
		Form e("Bad Form 2", 100, 0);
		std::cout << e << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 4: Form grade too low ---" << std::endl;
	try
	{
		Form f("Bad Form 3", 151, 100);
		std::cout << f << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 5: Sign form successfully ---" << std::endl;
	try
	{
		Bureaucrat bob("Bob", 50);
		Form tax("Tax Form", 50, 100);
		std::cout << bob << std::endl;
		std::cout << tax << std::endl;
		bob.signForm(tax);
		std::cout << tax << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 6: Sign form grade too low ---" << std::endl;
	try
	{
		Bureaucrat charlie("Charlie", 100);
		Form secret("Top Secret", 50, 100);
		std::cout << charlie << std::endl;
		std::cout << secret << std::endl;
		charlie.signForm(secret);
		std::cout << secret << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 7: Direct beSigned ---" << std::endl;
	try
	{
		Bureaucrat dave("Dave", 1);
		Form permit("Building Permit", 10, 50);
		std::cout << permit << std::endl;
		permit.beSigned(dave);
		std::cout << permit << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 8: Direct beSigned too low ---" << std::endl;
	try
	{
		Bureaucrat eve("Eve", 100);
		Form license("Driver License", 50, 50);
		std::cout << license << std::endl;
		license.beSigned(eve);
		std::cout << license << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 9: Bureaucrat tests ---" << std::endl;
	try
	{
		Bureaucrat frank("Frank", 3);
		std::cout << frank << std::endl;
		frank.increment();
		std::cout << frank << std::endl;
		frank.decrement();
		std::cout << frank << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return (0);
}
