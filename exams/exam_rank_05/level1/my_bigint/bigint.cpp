#include "bigint.hpp"

// getter
std::string bigint::get_num() const
{
	return (this->num);
}

bigint::bigint()
{
	this->num = "0";
}

bigint::bigint(unsigned int n)
{
	std::stringstream ss;
	ss << n;
	std::string str;
	ss >> str;
	this->num = str;
}

bigint::bigint(const bigint& other)
{
	*this = other;
}

bigint& bigint::operator=(const bigint& other)
{
	if (this == &other)
		return(*this);
	this->num = other.num;
	return(*this);
}

bigint::~bigint()
{
	// std::cout << "Destructor called" << std::endl;
}

/////////////////// adition /////////////////////////

std::string reverse(std::string str)
{
	std::string ret = "";
	for (int i = str.length() -1; i >= 0; i--)
	{
		ret += str[i];
	}
	return (ret);
}

std::string string_addition(std::string s1, std::string s2)
{
	int digit1, digit2, total, carry;
	std::string ret;
	int i = s1.length() -1;
	int j = s2.length() -1;
	carry = 0;
	while(i >= 0 || j >= 0 || carry > 0)
	{
		if (i >= 0)
			digit1 = s1[i] - '0';
		else
			digit1 = 0;
		if (j >= 0)
			digit2 = s2[j] - '0';
		else 
			digit2 = 0;
		total = digit1 + digit2 + carry;
		carry = total/10;
		ret += (total%10 + '0');
		i--;
		j--;
	}
	ret = reverse(ret);
	return ret;
}

bigint bigint::operator+(const bigint& other) const
{
	bigint tmp;
	tmp.num = string_addition(this->num, other.num);
	return(tmp);
}

bigint& bigint::operator+=(const bigint& other)
{
	(*this) = (*this) + other;
	return (*this);
}

bigint& bigint::operator++()
{
	std::string one = "1";
	this->num = string_addition(this->num, one);
	return (*this);
}
bigint bigint::operator++(int)
{
	bigint copy(*this);
	std::string one = "1";
	this->num = string_addition(this->num, one);
	return (copy);
}

/////// digitshift ////////////////
std::string string_n_copy(std::string s, int n)
{
	std::string ret = "";
	for (int i = 0; i < n; i++)
		ret += s[i];
	return (ret); 
}

bigint bigint::operator<<(unsigned int n) const
{
	std::string new_num = this->num;
	for (unsigned int i = 0; i < n; i++)
		new_num += '0';
	bigint ret;
	ret.num = new_num;
	return (ret);
}

bigint bigint::operator>>(unsigned int n) const
{
	std::string new_num = string_n_copy(this->num, this->num.length() - n);
	bigint ret;
	ret.num = new_num;
	return (ret);
}

bigint& bigint::operator<<=(unsigned int n)
{
	(*this) = (*this) << n;
	return (*this);
}

bigint& bigint::operator>>=(unsigned int n)
{
	(*this) = (*this) >> n;
	return (*this);
}


unsigned int str_to_num(std::string s)
{
	std::stringstream ss(s);
	unsigned int ret;
	ss >> ret;
	return (ret);
}


bigint bigint::operator<<(const bigint& other) const
{
	unsigned int n = str_to_num(other.num);
	return (*this << n);
}

bigint bigint::operator>>(const bigint& other) const
{
	unsigned int n = str_to_num(other.num);
	return (*this >> n);
}

bigint& bigint::operator<<=(const bigint& other)
{
	unsigned int n = str_to_num(other.num);
	(*this) = (*this) << n;
	return (*this);
}

bigint& bigint::operator>>=(const bigint& other)
{
	unsigned int n = str_to_num(other.num);
	(*this) = (*this) >> n;
	return (*this);
}
/////// comparison ////////////////

int compare_str(std::string s1, std::string s2)
{
	if (s1.length() > s2.length())
		return(1);
	else if (s1.length() < s2.length())
		return (-1);
	else
	{
		int i = 0;
		while(s1[i] == s2[i] && s1[i] != 0)
			i++;
		return (s1[i] - s2[i]);
	}
}

bool bigint::operator>(const bigint other) const
{
	if (compare_str(this->num, other.num) > 0)
		return (true);
	return (false);
}

bool bigint::operator>=(const bigint other) const
{
	if (compare_str(this->num, other.num) >= 0)
		return (true);
	return (false);
}
bool bigint::operator<(const bigint other) const
{
	if (compare_str(this->num, other.num) < 0)
		return (true);
	return (false);
}
bool bigint::operator<=(const bigint other) const
{
	if (compare_str(this->num, other.num) <= 0)
		return (true);
	return (false);
}
bool bigint::operator==(const bigint other) const
{
	if (compare_str(this->num, other.num) == 0)
		return (true);
	return (false);
}
bool bigint::operator!=(const bigint other) const
{
	if (compare_str(this->num, other.num) != 0)
		return (true);
	return (false);
}

////////////////////////////////////
std::ostream& operator<<(std::ostream& out, const bigint& object)
{
	out << object.get_num() << std::endl;
	return out;
}
