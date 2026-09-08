#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <map>
# include <cstdlib>
# include <cctype>

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
		std::map<std::string, double> _database;

		void loadDatabase(const std::string &filename);

		bool isValidDate(const std::string &date) const;
		bool isValidValue(const std::string &value) const;

		double parseValue(const std::string &value) const;

		std::string trim(const std::string &str) const;

		std::string findClosestDate(const std::string &date) const;
};

#endif