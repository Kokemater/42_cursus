#ifndef SPAN_HPP
# define SPAN_HPP

# include <iostream>
# include <string>
# include <vector>
# include <algorithm>
# include <stdexcept>

class Span
{
public:
	Span(unsigned int n);
	Span(const Span &src);
	~Span(void);

	Span &operator=(const Span &rhs);

	void addNumber(int number);
	void addNumber(std::vector<int>::iterator begin, std::vector<int>::iterator end);

	int shortestSpan(void) const;
	int longestSpan(void) const;

private:
	std::vector<int> _numbers;
	unsigned int _maxSize;

	Span(void);
};

#endif