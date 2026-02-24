#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>
#include <string>


class vect2{
	private:
		int x;
		int y;
	public:
		//cannonical
		vect2();
		vect2(int x, int y);
		vect2(const vect2& other);
		vect2& operator=(const vect2& other);
		~vect2();

		// getter
		int get_x() const;
		int get_y() const;

		// []
		int operator[](int index) const;
		int& operator[](int index);

		//  ++ --
		vect2 operator++(int);
		vect2& operator++();
		vect2 operator--(int);
		vect2& operator--();

		// operators
		vect2 operator+(const vect2& other) const;
		vect2 operator-(const vect2& other) const;
		vect2 operator*(int n) const;

		vect2& operator+=(const vect2& other);
		vect2& operator-=(const vect2& other);
		vect2& operator*=(int n);

		vect2 operator-()const;

		// comparison

		bool operator==(const vect2& other);
		bool operator!=(const vect2& other);

};

vect2 operator*(int n, const vect2& other);


std::ostream& operator<<(std::ostream& out, const vect2& obj);

#endif