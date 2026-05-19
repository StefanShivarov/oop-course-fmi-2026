#pragma once
#include <iostream>
class Complex
{
private:
	double real;
	double imaginary;

public:
	Complex();
	explicit Complex(double real, double im);

	Complex& operator+=(const Complex& other);
	Complex& operator-=(const Complex& other);
	Complex& operator*=(const Complex& other);
	Complex& operator/=(const Complex& other);
	Complex operator+() const;
	Complex operator-() const;
	const double getReal() const;
	const double getIm() const;

	friend std::ostream& operator<<(std::ostream& os, const Complex& complex);
	friend std::istream& operator>>(std::istream& is, Complex& complex);
};

	Complex operator+(const Complex& lhs, const Complex& rhs);
	Complex operator-(const Complex& lhs, const Complex& rhs);
	Complex operator*(const Complex& lhs, const Complex& rhs);
	Complex operator/(const Complex& lhs, const Complex& rhs);
	bool operator==(const Complex& lhs, const Complex& rhs);
	bool operator!=(const Complex& lhs, const Complex& rhs);
