#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
}

BitcoinExchange::BitcoinExchange(const std::string &databaseFile)
{
	loadDatabase(databaseFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) : _database(src._database)
{
}

BitcoinExchange::~BitcoinExchange(void)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
	if (this != &rhs)
	{
		_database = rhs._database;
	}
	return (*this);
}

void BitcoinExchange::loadDatabase(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open database file." << std::endl;
		return;
	}

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::string::size_type commaPos = line.find(',');
		if (commaPos != std::string::npos)
		{
			std::string date = line.substr(0, commaPos);
			std::string valueStr = line.substr(commaPos + 1);
			float value = static_cast<float>(std::atof(valueStr.c_str()));
			_database[date] = value;
		}
	}
	file.close();
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
	if (date.length() != 10)
		return (false);
	if (date[4] != '-' || date[7] != '-')
		return (false);

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31)
		return (false);
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return (false);
	if (month == 2)
	{
		bool leapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (day > (leapYear ? 29 : 28))
			return (false);
	}
	return (true);
}

bool BitcoinExchange::isValidValue(float value) const
{
	return (value >= 0 && value <= 1000);
}

std::string BitcoinExchange::findClosestDate(const std::string &date) const
{
	std::map<std::string, float>::const_iterator it = _database.lower_bound(date);
	if (it == _database.begin() && it->first != date)
		return ("");
	if (it == _database.end() || it->first != date)
		--it;
	return (it->first);
}

void BitcoinExchange::processInputFile(const std::string &inputFile) const
{
	std::ifstream file(inputFile.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::string::size_type pipePos = line.find('|');
		if (pipePos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string date = line.substr(0, pipePos);
		std::string valueStr = line.substr(pipePos + 1);

		if (date.length() > 0 && date[date.length() - 1] == ' ')
			date.erase(date.length() - 1);
		if (valueStr.length() > 0 && valueStr[0] == ' ')
			valueStr.erase(0, 1);

		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}

		float value = static_cast<float>(std::atof(valueStr.c_str()));
		if (valueStr.empty() || (valueStr[0] != '-' && valueStr[0] != '+' && !std::isdigit(valueStr[0])))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		if (value < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}

		if (!isValidValue(value))
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}

		std::string closestDate = findClosestDate(date);
		if (closestDate.empty())
		{
			std::cerr << "Error: no valid date found." << std::endl;
			continue;
		}

		std::map<std::string, float>::const_iterator it = _database.find(closestDate);
		float result = value * it->second;

		std::cout << date << " => " << value << " = " << result << std::endl;
	}
	file.close();
}