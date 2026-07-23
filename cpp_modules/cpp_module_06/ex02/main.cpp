#include "Base.hpp"

int main(void)
{
	std::srand(std::time(NULL));

	std::cout << "=== Generating and identifying 10 random objects ===" << std::endl;
	for (int i = 0; i < 10; i++)
	{
		Base *obj = generate();
		std::cout << "Object " << i + 1 << " - Pointer: ";
		identify(obj);
		std::cout << "Object " << i + 1 << " - Reference: ";
		identify(*obj);
		delete obj;
	}

	return (0);
}