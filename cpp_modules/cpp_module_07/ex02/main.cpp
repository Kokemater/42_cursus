#include "Array.hpp"

int main(void)
{
	std::cout << "=== Test 1: Default constructor (empty array) ===" << std::endl;
	Array<int> empty;
	std::cout << "Size: " << empty.size() << std::endl;

	std::cout << "\n=== Test 2: Constructor with size ===" << std::endl;
	Array<int> ints(5);
	std::cout << "Size: " << ints.size() << std::endl;
	std::cout << "Elements: ";
	for (int i = 0; i < ints.size(); i++)
		std::cout << ints[i] << " ";
	std::cout << std::endl;

	std::cout << "\n=== Test 3: Modify elements ===" << std::endl;
	for (int i = 0; i < ints.size(); i++)
		ints[i] = (i + 1) * 10;
	std::cout << "Modified: ";
	for (int i = 0; i < ints.size(); i++)
		std::cout << ints[i] << " ";
	std::cout << std::endl;

	std::cout << "\n=== Test 4: Copy constructor ===" << std::endl;
	Array<int> copy(ints);
	std::cout << "Original: ";
	for (int i = 0; i < ints.size(); i++)
		std::cout << ints[i] << " ";
	std::cout << std::endl;
	std::cout << "Copy: ";
	for (int i = 0; i < copy.size(); i++)
		std::cout << copy[i] << " ";
	std::cout << std::endl;

	std::cout << "\n=== Test 5: Assignment operator ===" << std::endl;
	Array<int> assigned;
	assigned = ints;
	std::cout << "Original: ";
	for (int i = 0; i < ints.size(); i++)
		std::cout << ints[i] << " ";
	std::cout << std::endl;
	std::cout << "Assigned: ";
	for (int i = 0; i < assigned.size(); i++)
		std::cout << assigned[i] << " ";
	std::cout << std::endl;

	std::cout << "\n=== Test 6: Modify copy doesn't affect original ===" << std::endl;
	copy[0] = 999;
	std::cout << "Original[0]: " << ints[0] << std::endl;
	std::cout << "Copy[0]: " << copy[0] << std::endl;

	std::cout << "\n=== Test 7: Index out of bounds ===" << std::endl;
	try
	{
		std::cout << ints[10] << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	try
	{
		std::cout << ints[-1] << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 8: String array ===" << std::endl;
	Array<std::string> strings(3);
	strings[0] = "Hello";
	strings[1] = "World";
	strings[2] = "Templates";
	std::cout << "Strings: ";
	for (int i = 0; i < strings.size(); i++)
		std::cout << strings[i] << " ";
	std::cout << std::endl;

	std::cout << "\n=== Test 9: Const array ===" << std::endl;
	const Array<int> constArr(ints);
	std::cout << "Const array: ";
	for (int i = 0; i < constArr.size(); i++)
		std::cout << constArr[i] << " ";
	std::cout << std::endl;

	return (0);
}