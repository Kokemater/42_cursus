#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <string>
# include <fstream>
# include <sstream>
# include <map>
# include <cstdlib>

class BitcoinExchange
{
public:
	BitcoinExchange(void);
	BitcoinExchange(const std::string &databaseFile);
	BitcoinExchange(const BitcoinExchange &src);
	~BitcoinExchange(void);

	BitcoinExchange &operator=(const BitcoinExchange &rhs);

	void processInputFile(const std::string &inputFile) const;

private:
	std::map<std::string, float> _database;

	void loadDatabase(const std::string &filename);
	bool isValidDate(const std::string &date) const;
	bool isValidValue(float value) const;
	std::string findClosestDate(const std::string &date) const;
};

#endif