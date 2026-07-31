#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <string>

class ScalarConverter
{
public:
	static void convert(const std::string &literal);

private:
	ScalarConverter(void);
	ScalarConverter(const ScalarConverter &src);
	~ScalarConverter(void);
	ScalarConverter &operator=(const ScalarConverter &rhs);
};

#endif
