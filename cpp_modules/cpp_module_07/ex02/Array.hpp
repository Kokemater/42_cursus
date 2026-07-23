#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <iostream>
# include <string>
# include <stdexcept>
# include <cstdlib>

template <typename T>
class Array
{
public:
	Array(void);
	Array(unsigned int n);
	Array(const Array &src);
	~Array(void);

	Array &operator=(const Array &rhs);
	T &operator[](int index);
	const T &operator[](int index) const;

	int size(void) const;

private:
	T *_elements;
	int _size;
};

#include "Array.tpp"

#endif