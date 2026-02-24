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
vect2::~vect2()
{

}

vect2 vect2::operator=(const vect2& other)
{
	if (this == &other)
		return (*this);
	this->x = other.x;
	this->y = other.y;
	return (*this);
}

int vect2::operator[](int index) const
{
	if (index == 0)
		return (this->x);
	return (this->y);
}

int& vect2::operator[](int index)
{
	if (index == 0)
		return (this->x);
	return (this->y);
}
vect2& vect2::operator++()
{
	this->x += 1;
	this->y += 1;
	return (*this);
}

vect2 vect2::operator++(int)
{
	vect2 tmp = *this;
	this->x += 1;
	this->y += 1;
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
	vect2 tmp = *this;
	this->x -= 1;
	this->y -= 1;
	return (tmp);
}

vect2 vect2::operator+(const vect2& other) const
{
	int x = this->x + other.x;
	int y = this->y + other.y;
	vect2 ans(x, y);
	return (ans);
}
vect2& vect2::operator+=(const vect2& other)
{
	*this = *this + other;
	return (*this);
}


vect2 vect2::operator-(const vect2& other) const 
{
	int x = this->x - other.x;
	int y = this->y - other.y;
	vect2 ans(x, y);
	return (ans);
}
vect2& vect2::operator-=(const vect2& other)
{
	*this = *this - other;
	return (*this);
}

vect2 vect2::operator*(int n) const 
{
	int x = this->x *n;
	int y = this->y *n;
	vect2 ans(x, y);
	return (ans);
}
vect2& vect2::operator*=(int n)
{
	*this = *this * n;
	return (*this);
}

vect2 operator*(int n, const vect2& object)
{
	int x = object[0] *n;
	int y = object[1] *n;
	vect2 ans(x, y);
	return (ans);
}

vect2 vect2::operator-()
{
	vect2 ans = *this * -1;
	return (ans);
}

bool vect2::operator==(const vect2& other) const
{
	if (this->x == other.x && this->y == other.y)
		return true;
	else
		return false;
}
bool vect2::operator!=(const vect2& other) const
{
	if (*this == other)
		return false;
	return true;

}







std::ostream& operator<<(std::ostream& out, const vect2& object)
{
	out << "{" << object[0] << ", " << object[1] << "}" << std::endl;
	return (out);
}



