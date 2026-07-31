#include "Base.hpp"

static void testInstance(Base *obj, const std::string &label)
{
	std::cout << label << " via pointer:   ";
	identify(obj);
	std::cout << label << " via reference: ";
	identify(*obj);
}

int main(void)
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	std::cout << "=== Explicit instances ===" << std::endl;
	A a;
	B b;
	C c;
	Base base;
	testInstance(&a, "A");
	testInstance(&b, "B");
	testInstance(&c, "C");
	testInstance(&base, "Base");
	std::cout << std::endl;

	std::cout << "=== Random generation (10 objects) ===" << std::endl;
	for (int i = 0; i < 10; i++)
	{
		Base *obj = generate();
		if (obj == NULL)
		{
			std::cout << "generate() returned NULL" << std::endl;
			return (1);
		}
		std::cout << "Object " << i + 1 << ": ";
		identify(obj);
		identify(*obj);
		delete obj;
	}

	return (0);
}
