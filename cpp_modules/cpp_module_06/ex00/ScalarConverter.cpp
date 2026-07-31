#include "ScalarConverter.hpp"

#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <sstream>

static bool isNumber(const std::string &num, bool requireDot)
{
	size_t i = 0;
	bool dot = false;
	bool hasDigit = false;

	if (num.empty())
		return (false);
	if (num[0] == '+' || num[0] == '-')
	{
		if (num.length() == 1)
			return (false);
		i = 1;
	}
	for (; i < num.length(); i++)
	{
		if (num[i] == '.')
		{
			if (dot)
				return (false);
			dot = true;
		}
		else if (std::isdigit(static_cast<unsigned char>(num[i])))
			hasDigit = true;
		else
			return (false);
	}
	if (!hasDigit)
		return (false);
	if (requireDot && !dot)
		return (false);
	return (true);
}

static bool isChar(const std::string &literal)
{
	if (literal.length() == 1
		&& std::isprint(static_cast<unsigned char>(literal[0]))
		&& !std::isdigit(static_cast<unsigned char>(literal[0])))
		return (true);
	if (literal.length() == 3
		&& literal[0] == '\''
		&& literal[2] == '\''
		&& std::isprint(static_cast<unsigned char>(literal[1])))
		return (true);
	return (false);
}

static bool isInt(const std::string &literal)
{
	size_t i = 0;

	if (literal.empty())
		return (false);
	if (literal[0] == '+' || literal[0] == '-')
	{
		if (literal.length() == 1)
			return (false);
		i = 1;
	}
	for (; i < literal.length(); i++)
	{
		if (!std::isdigit(static_cast<unsigned char>(literal[i])))
			return (false);
	}
	return (true);
}

static bool isFloat(const std::string &literal)
{
	if (literal == "-inff" || literal == "+inff" || literal == "nanf")
		return (true);
	if (literal.length() < 2 || literal[literal.length() - 1] != 'f')
		return (false);
	return (isNumber(literal.substr(0, literal.length() - 1), true));
}

static bool isDouble(const std::string &literal)
{
	if (literal == "-inf" || literal == "+inf" || literal == "nan")
		return (true);
	return (isNumber(literal, true));
}

static void printChar(double value)
{
	if (std::isnan(value) || std::isinf(value)
		|| value < 0
		|| value > std::numeric_limits<unsigned char>::max())
	{
		std::cout << "impossible";
		return;
	}
	unsigned char c = static_cast<unsigned char>(value);
	if (std::isprint(c))
		std::cout << "'" << c << "'";
	else
		std::cout << "Non displayable";
}

static void printInt(double value)
{
	if (std::isnan(value) || std::isinf(value)
		|| value < std::numeric_limits<int>::min()
		|| value > std::numeric_limits<int>::max())
	{
		std::cout << "impossible";
		return;
	}
	std::cout << static_cast<int>(value);
}

static void printFloat(double value)
{
	if (std::isnan(value))
	{
		std::cout << "nanf";
		return;
	}
	if (std::isinf(value))
	{
		std::cout << (value > 0 ? "+inff" : "-inff");
		return;
	}
	if (value < -static_cast<double>(std::numeric_limits<float>::max())
		|| value > static_cast<double>(std::numeric_limits<float>::max()))
	{
		std::cout << "impossible";
		return;
	}
	std::ostringstream ss;
	ss.precision(7);
	ss << static_cast<float>(value);
	std::string s = ss.str();
	if (s.find('.') == std::string::npos
		&& s.find('e') == std::string::npos
		&& s.find('E') == std::string::npos)
		s += ".0";
	std::cout << s << "f";
}

static void printDouble(double value)
{
	if (std::isnan(value))
	{
		std::cout << "nan";
		return;
	}
	if (std::isinf(value))
	{
		std::cout << (value > 0 ? "+inf" : "-inf");
		return;
	}
	std::ostringstream ss;
	ss.precision(15);
	ss << value;
	std::string s = ss.str();
	if (s.find('.') == std::string::npos)
		s += ".0";
	std::cout << s;
}

static void convertFromChar(const std::string &literal)
{
	char c = literal[0];

	if (literal.length() == 3)
		c = literal[1];

	std::cout << "char: ";
	printChar(static_cast<double>(c));
	std::cout << std::endl;
	std::cout << "int: ";
	printInt(static_cast<double>(c));
	std::cout << std::endl;
	std::cout << "float: ";
	printFloat(static_cast<double>(c));
	std::cout << std::endl;
	std::cout << "double: ";
	printDouble(static_cast<double>(c));
	std::cout << std::endl;
}

static void convertFromInt(const std::string &literal)
{
	double value = std::strtod(literal.c_str(), NULL);

	if (std::isinf(value))
	{
		std::cout << "char: impossible" << std::endl
				  << "int: impossible" << std::endl
				  << "float: impossible" << std::endl
				  << "double: impossible" << std::endl;
		return;
	}

	std::cout << "char: ";
	printChar(value);
	std::cout << std::endl;
	std::cout << "int: ";
	printInt(value);
	std::cout << std::endl;
	std::cout << "float: ";
	printFloat(value);
	std::cout << std::endl;
	std::cout << "double: ";
	printDouble(value);
	std::cout << std::endl;
}

static void convertFromFloat(const std::string &literal)
{
	double value;

	if (literal == "-inff")
		value = -std::numeric_limits<double>::infinity();
	else if (literal == "+inff")
		value = std::numeric_limits<double>::infinity();
	else if (literal == "nanf")
		value = std::numeric_limits<double>::quiet_NaN();
	else
		value = std::strtod(literal.c_str(), NULL);

	std::cout << "char: ";
	printChar(value);
	std::cout << std::endl;
	std::cout << "int: ";
	printInt(value);
	std::cout << std::endl;
	std::cout << "float: ";
	printFloat(value);
	std::cout << std::endl;
	std::cout << "double: ";
	printDouble(value);
	std::cout << std::endl;
}

static void convertFromDouble(const std::string &literal)
{
	double value;

	if (literal == "-inf")
		value = -std::numeric_limits<double>::infinity();
	else if (literal == "+inf")
		value = std::numeric_limits<double>::infinity();
	else if (literal == "nan")
		value = std::numeric_limits<double>::quiet_NaN();
	else
		value = std::strtod(literal.c_str(), NULL);

	std::cout << "char: ";
	printChar(value);
	std::cout << std::endl;
	std::cout << "int: ";
	printInt(value);
	std::cout << std::endl;
	std::cout << "float: ";
	printFloat(value);
	std::cout << std::endl;
	std::cout << "double: ";
	printDouble(value);
	std::cout << std::endl;
}

void ScalarConverter::convert(const std::string &literal)
{
	if (isChar(literal))
		convertFromChar(literal);
	else if (isFloat(literal))
		convertFromFloat(literal);
	else if (isDouble(literal))
		convertFromDouble(literal);
	else if (isInt(literal))
		convertFromInt(literal);
	else
		std::cout << "char: impossible" << std::endl
				  << "int: impossible" << std::endl
				  << "float: impossible" << std::endl
				  << "double: impossible" << std::endl;
}
