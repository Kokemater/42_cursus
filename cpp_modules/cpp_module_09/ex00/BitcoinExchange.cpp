#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
}

BitcoinExchange::BitcoinExchange(const std::string &databaseFile)
{
	loadDatabase(databaseFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
	: _database(src._database)
{
}

BitcoinExchange::~BitcoinExchange(void)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
	if (this != &rhs)
		_database = rhs._database;
	return (*this);
}

/*
** Removes spaces and tabs from the beginning and end
** of a string.
*/
std::string BitcoinExchange::trim(const std::string &str) const
{
	std::string::size_type start = 0;
	std::string::size_type end = str.length();

	while (start < end &&
		(str[start] == ' ' || str[start] == '\t'))
		++start;

	while (end > start &&
		(str[end - 1] == ' ' || str[end - 1] == '\t'))
		--end;

	return (str.substr(start, end - start));
}

/*
** Loads the provided data.csv database.
**
** Expected format:
**
** date,exchange_rate
** 2011-01-03,0.3
** ...
*/
void BitcoinExchange::loadDatabase(const std::string &filename)
{
	std::ifstream file(filename.c_str());

	if (!file.is_open())
	{
		std::cerr << "Error: could not open database file." << std::endl;
		return;
	}

	std::string line;

	// Skip header
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::string::size_type commaPos = line.find(',');

		if (commaPos == std::string::npos)
			continue;

		std::string date = trim(line.substr(0, commaPos));
		std::string valueStr = trim(line.substr(commaPos + 1));

		if (date.empty() || valueStr.empty())
			continue;

		double value = std::atof(valueStr.c_str());

		_database[date] = value;
	}

	file.close();
}

/*
** Checks:
**
** YYYY-MM-DD
**
** and verifies that the date actually exists
** in the Gregorian calendar.
*/
bool BitcoinExchange::isValidDate(const std::string &date) const
{
	if (date.length() != 10)
		return (false);

	if (date[4] != '-' || date[7] != '-')
		return (false);

	// YYYY-MM-DD -> every other character must be a digit.
	for (int i = 0; i < 10; ++i)
	{
		if (i == 4 || i == 7)
			continue;

		if (!std::isdigit(static_cast<unsigned char>(date[i])))
			return (false);
	}

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (year < 1)
		return (false);

	if (month < 1 || month > 12)
		return (false);

	if (day < 1)
		return (false);

	if (month == 2)
	{
		bool leapYear;

		leapYear = (year % 4 == 0 && year % 100 != 0)
			|| (year % 400 == 0);

		if (leapYear && day > 29)
			return (false);

		if (!leapYear && day > 28)
			return (false);
	}
	else if (month == 4 || month == 6
		|| month == 9 || month == 11)
	{
		if (day > 30)
			return (false);
	}
	else
	{
		if (day > 31)
			return (false);
	}

	return (true);
}

/*
** Checks whether the entire value is a valid number.
**
** Examples accepted:
** 0
** 1
** 1.2
** 0.42
**
** Examples rejected:
** abc
** 1abc
** 1.2.3
** 1foo
*/
bool BitcoinExchange::isValidValue(const std::string &value) const
{
	std::stringstream ss(value);
	double number;
	char extra;

	if (!(ss >> number))
		return (false);

	if (ss >> extra)
		return (false);

	return (true);
}

double BitcoinExchange::parseValue(const std::string &value) const
{
	std::stringstream ss(value);
	double number = 0;

	ss >> number;

	return (number);
}

/*
** Returns:
**
** - exact date if it exists
** - closest previous date otherwise
** - empty string if there is no previous date
**
** Example:
**
** DB:
** 2011-01-01
** 2011-01-05
** 2011-01-10
**
** Input:
** 2011-01-07
**
** Result:
** 2011-01-05
*/
std::string BitcoinExchange::findClosestDate(const std::string &date) const
{
	std::map<std::string, double>::const_iterator it;

	it = _database.lower_bound(date);

	if (it == _database.begin() && it->first != date)
		return ("");

	if (it == _database.end())
	{
		--it;
		return (it->first);
	}

	if (it->first == date)
		return (it->first);

	--it;
	return (it->first);
}

/*
** Processes the user's input file.
**
** Expected format:
**
** date | value
**
** Example:
**
** 2011-01-03 | 3
*/
void BitcoinExchange::processInputFile(const std::string &inputFile) const
{
	std::ifstream file(inputFile.c_str());

	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;

	// Read header
	if (!std::getline(file, line))
	{
		file.close();
		return;
	}

	while (std::getline(file, line))
	{
		/*
		** There must be exactly one '|'.
		*/
		std::string::size_type firstPipe = line.find('|');
		std::string::size_type lastPipe = line.rfind('|');

		if (firstPipe == std::string::npos
			|| firstPipe != lastPipe)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string date = trim(line.substr(0, firstPipe));
		std::string valueStr = trim(line.substr(firstPipe + 1));

		/*
		** Validate date.
		*/
		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		/*
		** Validate value syntax.
		*/
		if (!isValidValue(valueStr))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		double value = parseValue(valueStr);

		/*
		** Negative values are forbidden.
		*/
		if (value < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}

		/*
		** Values greater than 1000 are forbidden.
		*/
		if (value > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}

		/*
		** Find exact date or closest previous date.
		*/
		std::string closestDate = findClosestDate(date);

		if (closestDate.empty())
		{
			std::cerr << "Error: no valid date found." << std::endl;
			continue;
		}

		std::map<std::string, double>::const_iterator it;

		it = _database.find(closestDate);

		if (it == _database.end())
		{
			std::cerr << "Error: no valid date found." << std::endl;
			continue;
		}

		double result = value * it->second;

		std::cout << date
			<< " => "
			<< value
			<< " = "
			<< result
			<< std::endl;
	}

	file.close();
}