#ifndef VECT2_HPP
#define VECT2_HPP


#include <iostream>
#include <sstream>

class vect2{

private:
	int x;
	int y;
public:
	// cannonical
	vect2();
	vect2(int x, int y);
	vect2(const vect2& other);
	vect2 operator=(const vect2& other);
	~vect2();

	int operator[](int index) const;
	int& operator[](int index);

	vect2& operator++();
	vect2 operator++(int);
	vect2& operator--();
	vect2 operator--(int);
	vect2 operator-();


	vect2 operator+(const vect2& other) const;
	vect2& operator+=(const vect2& other);
	vect2 operator-(const vect2& other) const;
	vect2& operator-=(const vect2& other);
	vect2 operator*(int n) const;
	vect2& operator*=(int n);

	bool operator==(const vect2& other)const;
	bool operator!=(const vect2& other)const;

};

std::ostream& operator<<(std::ostream& out, const vect2& object);

vect2 operator*(int n, const vect2& object);

#endif