#include "Bureaucrat.hpp"

int	main(void)
{
	std::cout << "--- Test 1: Valid construction ---" << std::endl;
	try
	{
		Bureaucrat a("Jbutragu", 1);
		Bureaucrat b("Peter Parker", 150);
		Bureaucrat c("Spiderman", 75);
		std::cout << a << std::endl;
		std::cout << b << std::endl;
		std::cout << c << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 2: Grade too high ---" << std::endl;
	try
	{
		Bureaucrat d("Dave", 0);
		std::cout << d << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 3: Grade too low ---" << std::endl;
	try
	{
		Bureaucrat e("Eve", 151);
		std::cout << e << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 4: Increment ---" << std::endl;
	try
	{
		Bureaucrat f("Frank", 3);
		std::cout << f << std::endl;
		f.increment();
		std::cout << f << std::endl;
		f.increment();
		std::cout << f << std::endl;
		f.increment();
		std::cout << f << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 5: Decrement ---" << std::endl;
	try
	{
		Bureaucrat g("Grace", 148);
		std::cout << g << std::endl;
		g.decrement();
		std::cout << g << std::endl;
		g.decrement();
		std::cout << g << std::endl;
		g.decrement();
		std::cout << g << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 6: Increment too high ---" << std::endl;
	try
	{
		Bureaucrat h("Henry", 1);
		std::cout << h << std::endl;
		h.increment();
		std::cout << h << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 7: Decrement too low ---" << std::endl;
	try
	{
		Bureaucrat i("Ivy", 150);
		std::cout << i << std::endl;
		i.decrement();
		std::cout << i << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 8: Copy constructor and assignment ---" << std::endl;
	try
	{
		Bureaucrat j("Jack", 50);
		Bureaucrat k(j);
		Bureaucrat l("Leo", 100);
		l = j;
		std::cout << j << std::endl;
		std::cout << k << std::endl;
		std::cout << l << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return (0);
}
