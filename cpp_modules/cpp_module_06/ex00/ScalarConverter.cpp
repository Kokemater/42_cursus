#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter(void)
{
}

ScalarConverter::ScalarConverter(const ScalarConverter &src)
{
	(void)src;
}

ScalarConverter::~ScalarConverter(void)
{
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &rhs)
{
	(void)rhs;
	return (*this);
}

bool ScalarConverter::isChar(const std::string &literal)
{
	return (literal.length() == 1 && std::isprint(literal[0]) && !std::isdigit(literal[0]));
}

bool ScalarConverter::isInt(const std::string &literal)
{
	size_t i = 0;

	if (literal.length() == 0)
		return (false);
	if (literal[0] == '-' || literal[0] == '+')
	{
		if (literal.length() == 1)
			return (false);
		i = 1;
	}
	for (; i < literal.length(); i++)
	{
		if (!std::isdigit(literal[i]))
			return (false);
	}
	return (true);
}

bool ScalarConverter::isFloat(const std::string &literal)
{
	if (literal == "-inff" || literal == "+inff" || literal == "nanf")
		return (true);
	if (literal.length() < 2 || literal[literal.length() - 1] != 'f')
		return (false);
	std::string num = literal.substr(0, literal.length() - 1);
	size_t i = 0;
	bool dot = false;

	if (num[0] == '-' || num[0] == '+')
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
		else if (!std::isdigit(num[i]))
			return (false);
	}
	return (dot);
}

bool ScalarConverter::isDouble(const std::string &literal)
{
	if (literal == "-inf" || literal == "+inf" || literal == "nan")
		return (true);
	size_t i = 0;
	bool dot = false;

	if (literal[0] == '-' || literal[0] == '+')
	{
		if (literal.length() == 1)
			return (false);
		i = 1;
	}
	for (; i < literal.length(); i++)
	{
		if (literal[i] == '.')
		{
			if (dot)
				return (false);
			dot = true;
		}
		else if (!std::isdigit(literal[i]))
			return (false);
	}
	return (dot);
}

void ScalarConverter::convertFromChar(const std::string &literal)
{
	char c = literal[0];
	std::cout << "char: '" << c << "'" << std::endl;
	std::cout << "int: " << static_cast<int>(c) << std::endl;
	std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
}

void ScalarConverter::convertFromInt(const std::string &literal)
{
	long value = std::atol(literal.c_str());

	if (value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max())
		std::cout << "char: impossible" << std::endl;
	else if (std::isprint(static_cast<char>(value)))
		std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;

	if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max())
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(value) << std::endl;

	std::cout << "float: " << static_cast<float>(value) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(value) << ".0" << std::endl;
}

void ScalarConverter::convertFromFloat(const std::string &literal)
{
	float value;

	if (literal == "-inff")
		value = -std::numeric_limits<float>::infinity();
	else if (literal == "+inff")
		value = std::numeric_limits<float>::infinity();
	else if (literal == "nanf")
		value = std::numeric_limits<float>::quiet_NaN();
	else
		value = static_cast<float>(std::atof(literal.c_str()));

	if (std::isnan(value) || std::isinf(value))
		std::cout << "char: impossible" << std::endl;
	else if (value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max())
		std::cout << "char: impossible" << std::endl;
	else if (std::isprint(static_cast<char>(value)))
		std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;

	if (std::isnan(value) || std::isinf(value) ||
		value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max())
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(value) << std::endl;

	if (value - static_cast<int>(value) == 0 && !std::isinf(value))
		std::cout << "float: " << value << ".0f" << std::endl;
	else
		std::cout << "float: " << value << "f" << std::endl;

	if (value - static_cast<int>(value) == 0 && !std::isinf(value))
		std::cout << "double: " << static_cast<double>(value) << ".0" << std::endl;
	else
		std::cout << "double: " << static_cast<double>(value) << std::endl;
}

void ScalarConverter::convertFromDouble(const std::string &literal)
{
	double value;

	if (literal == "-inf")
		value = -std::numeric_limits<double>::infinity();
	else if (literal == "+inf")
		value = std::numeric_limits<double>::infinity();
	else if (literal == "nan")
		value = std::numeric_limits<double>::quiet_NaN();
	else
		value = std::atof(literal.c_str());

	if (std::isnan(value) || std::isinf(value))
		std::cout << "char: impossible" << std::endl;
	else if (value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max())
		std::cout << "char: impossible" << std::endl;
	else if (std::isprint(static_cast<char>(value)))
		std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;

	if (std::isnan(value) || std::isinf(value) ||
		value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max())
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(value) << std::endl;

	if (value < -std::numeric_limits<float>::max() || value > std::numeric_limits<float>::max())
		std::cout << "float: impossible" << std::endl;
	else if (value - static_cast<int>(value) == 0 && !std::isinf(value))
		std::cout << "float: " << static_cast<float>(value) << ".0f" << std::endl;
	else
		std::cout << "float: " << static_cast<float>(value) << "f" << std::endl;

	if (value - static_cast<int>(value) == 0 && !std::isinf(value))
		std::cout << "double: " << value << ".0" << std::endl;
	else
		std::cout << "double: " << value << std::endl;
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