#include "vect2.hpp"

vect2::vect2()
{
	this->x = 0;
	this->y = 0;
}

vect2::vect2(int x, int y)
{
	this->x = x;
	this->y = y;
}

vect2::vect2(const vect2& other)
{
	this->x = other.x;
	this->y = other.y;
}

vect2& vect2::operator=(const vect2& other)
{
	if (this == &other)
		return(*this);
	this->x = other.x;
	this->y = other.y;
	return (*this);
}

vect2::~vect2()
{
	// Destructor
}


//////////// getters /////////////

int vect2::get_x() const
{
	return (this->x);
}

int vect2::get_y() const
{
	return (this->y);
}

//// [] //////

int vect2::operator[](int index) const
{
	if(index == 0)
		return (this->x);
	return (this->y);
}

int& vect2::operator[](int index)
{
	if(index == 0)
		return (this->x);
	return (this->y);
}

/// ++, -- ////////
vect2& vect2::operator++()
{
	this->x += 1;
	this->y += 1;
	return (*this);
}
vect2 vect2::operator++(int)
{
	vect2 tmp(*this);
	++(*this);
	return (tmp);
}

vect2& vect2::operator--()
{
	this->x -= 1;
	this->y -= 1;
	return (*this);
}

vect2 vect2::operator--(int)
{
	vect2 tmp(*this);
	--(*this);
	return (tmp);
}


///////////////// operators //////////////

vect2 vect2::operator+(const vect2& other) const
{
	vect2 tmp;
	tmp.x = this->x + other.x;
	tmp.y = this->y + other.y;
	return (tmp);
}
vect2 vect2::operator-(const vect2& other) const
{
	vect2 tmp;
	tmp.x = this->x - other.x;
	tmp.y = this->y - other.y;
	return (tmp);
}
vect2 vect2::operator*(int n) const
{
	vect2 tmp;
	tmp.x = this->x * n;
	tmp.y = this->y * n;
	return (tmp);
}

vect2& vect2::operator+=(const vect2& other)
{
	(*this) = (*this) + other;
	return(*this);
}


vect2& vect2::operator-=(const vect2& other)
{
	(*this) = (*this) - other;
	return(*this);
}
vect2& vect2::operator*=(int n)
{
	(*this) = (*this) * n;
	return (*this);
}


vect2 vect2::operator-() const
{
	vect2 tmp;
	tmp = (*this) * (-1);
	return (tmp);
}

/////////comparison /////

bool vect2::operator==(const vect2& other)
{
	if (this->x == other.x && this->y == other.y)
		return (true);
	return (false);
}

bool vect2::operator!=(const vect2& other)
{
	if (this->x != other.x || this->y != other.y)
		return (true);
	return (false);
}

////////////////

std::ostream& operator<<(std::ostream& out, const vect2& obj)
{
	int x = obj.get_x();
	int y = obj.get_y();
	out << "{" << x << ", " << y  << "}" << std::endl;
	return (out);
}

vect2 operator*(int n, const vect2& other)
{
	return (other * n);
}
