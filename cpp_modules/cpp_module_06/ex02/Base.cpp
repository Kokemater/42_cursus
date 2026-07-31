#include "Base.hpp"

#include <exception>

Base::~Base(void)
{
}

Base *generate(void)
{
	int random = std::rand() % 3;

	if (random == 0)
		return (new A());
	if (random == 1)
		return (new B());
	return (new C());
}

void identify(Base *p)
{
	if (dynamic_cast<A *>(p) != NULL)
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B *>(p) != NULL)
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C *>(p) != NULL)
		std::cout << "C" << std::endl;
	else
		std::cout << "Unknown" << std::endl;
}

void identify(Base &p)
{
	try
	{
		A &a = dynamic_cast<A &>(p);
		(void)a;
		std::cout << "A" << std::endl;
		return;
	}
	catch (std::exception &) {}

	try
	{
		B &b = dynamic_cast<B &>(p);
		(void)b;
		std::cout << "B" << std::endl;
		return;
	}
	catch (std::exception &) {}

	try
	{
		C &c = dynamic_cast<C &>(p);
		(void)c;
		std::cout << "C" << std::endl;
		return;
	}
	catch (std::exception &) {}

	std::cout << "Unknown" << std::endl;
}
