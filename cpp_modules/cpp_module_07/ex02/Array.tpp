#ifndef ARRAY_TPP
# define ARRAY_TPP

template <typename T>
Array<T>::Array(void) : _elements(NULL), _size(0)
{
}

template <typename T>
Array<T>::Array(unsigned int n) : _elements(new T[n]()), _size(static_cast<int>(n))
{
}

template <typename T>
Array<T>::Array(const Array &src) : _elements(NULL), _size(0)
{
	*this = src;
}

template <typename T>
Array<T>::~Array(void)
{
	delete[] _elements;
}

template <typename T>
Array<T> &Array<T>::operator=(const Array<T> &rhs)
{
	if (this != &rhs)
	{
		delete[] _elements;
		_size = rhs._size;
		if (_size > 0)
		{
			_elements = new T[_size];
			for (int i = 0; i < _size; i++)
				_elements[i] = rhs._elements[i];
		}
		else
			_elements = NULL;
	}
	return (*this);
}

template <typename T>
T &Array<T>::operator[](int index)
{
	if (index < 0 || index >= _size)
		throw std::out_of_range("Index out of bounds");
	return (_elements[index]);
}

template <typename T>
const T &Array<T>::operator[](int index) const
{
	if (index < 0 || index >= _size)
		throw std::out_of_range("Index out of bounds");
	return (_elements[index]);
}

template <typename T>
int Array<T>::size(void) const
{
	return (_size);
}

#endif