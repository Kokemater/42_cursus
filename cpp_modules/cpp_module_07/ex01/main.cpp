#include "iter.hpp"

template <typename T>
void printElement(T &elem)
{
	std::cout << elem << " ";
}

void multiplyByTwo(int &elem)
{
	elem *= 2;
}

void toUpperCase(char &c)
{
	if (c >= 'a' && c <= 'z')
		c = c - 32;
}

int main(void)
{
	std::cout << "=== Test 1: Integer array ===" << std::endl;
	int intArr[] = {1, 2, 3, 4, 5};
	int intLen = 5;

	std::cout << "Original: ";
	iter(intArr, intLen, printElement);
	std::cout << std::endl;

	iter(intArr, intLen, multiplyByTwo);
	std::cout << "After multiplyByTwo: ";
	iter(intArr, intLen, printElement);
	std::cout << std::endl;

	std::cout << "\n=== Test 2: String array ===" << std::endl;
	std::string strArr[] = {"hello", "world", "templates"};
	int strLen = 3;

	std::cout << "Original: ";
	iter(strArr, strLen, printElement);
	std::cout << std::endl;

	std::cout << "\n=== Test 3: Char array ===" << std::endl;
	char charArr[] = "hello";
	int charLen = 5;

	std::cout << "Original: ";
	iter(charArr, charLen, printElement);
	std::cout << std::endl;

	iter(charArr, charLen, toUpperCase);
	std::cout << "After toUpperCase: ";
	iter(charArr, charLen, printElement);
	std::cout << std::endl;

	std::cout << "\n=== Test 4: Double array ===" << std::endl;
	double dblArr[] = {1.1, 2.2, 3.3};
	int dblLen = 3;

	std::cout << "Original: ";
	iter(dblArr, dblLen, printElement);
	std::cout << std::endl;

	std::cout << "\n=== Test 5: Const array ===" << std::endl;
	const int constArr[] = {10, 20, 30};
	int constLen = 3;

	std::cout << "Const array: ";
	iter(constArr, constLen, printElement);
	std::cout << std::endl;

	return (0);
}