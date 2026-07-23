#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <iostream>
# include <string>
# include <cstdlib>
# include <limits>
# include <cmath>

class ScalarConverter
{
public:
	static void convert(const std::string &literal);

private:

	ScalarConverter(void);
	ScalarConverter(const ScalarConverter &src);
	~ScalarConverter(void);
	ScalarConverter &operator=(const ScalarConverter &rhs);

	static bool isChar(const std::string &literal);
	static bool isInt(const std::string &literal);
	static bool isFloat(const std::string &literal);
	static bool isDouble(const std::string &literal);

	static void convertFromChar(const std::string &literal);
	static void convertFromInt(const std::string &literal);
	static void convertFromFloat(const std::string &literal);
	static void convertFromDouble(const std::string &literal);
};

#endif