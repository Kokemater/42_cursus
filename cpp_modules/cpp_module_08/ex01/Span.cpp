#include "Span.hpp"

Span::Span(void) : _maxSize(0)
{
}

Span::Span(unsigned int n) : _maxSize(n)
{
}

Span::Span(const Span &src) : _numbers(src._numbers), _maxSize(src._maxSize)
{
}

Span::~Span(void)
{
}

Span &Span::operator=(const Span &rhs)
{
	if (this != &rhs)
	{
		_numbers = rhs._numbers;
		_maxSize = rhs._maxSize;
	}
	return (*this);
}

void Span::addNumber(int number)
{
	if (_numbers.size() >= _maxSize)
		throw std::out_of_range("Span is full");
	_numbers.push_back(number);
}

void Span::addNumber(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	for (std::vector<int>::iterator it = begin; it != end; ++it)
	{
		if (_numbers.size() >= _maxSize)
			throw std::out_of_range("Span is full");
		_numbers.push_back(*it);
	}
}

int Span::shortestSpan(void) const
{
	if (_numbers.size() < 2)
		throw std::out_of_range("Not enough elements to find span");

	std::vector<int> sorted = _numbers;
	std::sort(sorted.begin(), sorted.end());

	int shortest = sorted[1] - sorted[0];
	for (size_t i = 2; i < sorted.size(); i++)
	{
		int span = sorted[i] - sorted[i - 1];
		if (span < shortest)
			shortest = span;
	}
	return (shortest);
}

int Span::longestSpan(void) const
{
	if (_numbers.size() < 2)
		throw std::out_of_range("Not enough elements to find span");

	int min = *std::min_element(_numbers.begin(), _numbers.end());
	int max = *std::max_element(_numbers.begin(), _numbers.end());

	return (max - min);
}