

#include <iostream>
#include <sstream>
#include <string>

class bigint
{
	private:
		std::string num;
	public:
		// cannonical
		bigint();
		bigint(unsigned int n);
		bigint(const bigint& other);
		bigint& operator=(const bigint& other);
		~bigint();
		// getter
		std::string get_num() const;

		// addition
		bigint operator+(const bigint& other) const;
		bigint& operator+=(const bigint& other);
		bigint& operator++();
		bigint operator++(int);

		// digitshift
		bigint operator<<(unsigned int n) const;
		bigint operator>>(unsigned int n) const;
		bigint& operator<<=(unsigned int n);
		bigint& operator>>=(unsigned int n);

		bigint operator>>(const bigint& other) const;
		bigint operator<<(const bigint& other) const;
		bigint& operator<<=(const bigint& other);
		bigint& operator>>=(const bigint& other);

		//comparison
		bool operator>(const bigint other) const;
		bool operator>=(const bigint other) const;
		bool operator<(const bigint other) const;
		bool operator<=(const bigint other) const;
		bool operator==(const bigint other) const;
		bool operator!=(const bigint other) const;

};

std::ostream& operator<<(std::ostream& output, const bigint& object);