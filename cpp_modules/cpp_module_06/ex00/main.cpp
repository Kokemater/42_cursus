#include <iostream>

#include "ScalarConverter.hpp"

static void testLiteral(const std::string &literal)
{
	std::cout << "----------------------------------------" << std::endl;
	std::cout << "Input: " << literal << std::endl;
	ScalarConverter::convert(literal);
	std::cout << std::endl;
}

int main()
{
	testLiteral("0");
	testLiteral("-42");
	testLiteral("42");
	testLiteral("42.0f");
	testLiteral("-4.2f");
	testLiteral("4.2f");
	testLiteral("42f");
	testLiteral("0f");
	testLiteral("0.0");
	testLiteral("-4.2");
	testLiteral("4.2");
	testLiteral("a");
	testLiteral("'*'");
	testLiteral("'c'");
	testLiteral("200");
	testLiteral("300");
	testLiteral("nan");
	testLiteral("-inf");
	testLiteral("+inf");
	testLiteral("nanf");
	testLiteral("-inff");
	testLiteral("+inff");
	testLiteral("2147483647");
	testLiteral("-2147483648");
	testLiteral("2147483648");
	testLiteral(".42");
	testLiteral("42.");
	testLiteral("42.f");
	testLiteral("hello");
	return (0);
}
