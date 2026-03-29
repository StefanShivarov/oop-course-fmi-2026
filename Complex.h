#pragma once
#include <iostream>

constexpr double EPSILON = 0.0000001;

class Complex
{
private:
	double real;
	double im;
	
public:
	Complex();
	Complex(double, double);

	double getReal()const;
	double getIm()const;

	void setReal(double);
	void setIm(double);

	Complex& operator+=(const Complex&);
	Complex& operator-=(const Complex&);
	Complex& operator*=(const Complex&);
	Complex& operator/=(const Complex&);

	Complex operator+() const;
	Complex operator-() const;

	
};

Complex operator+(const Complex&, const Complex&);
Complex operator-(const Complex&, const Complex&);
Complex operator*(const Complex&, const Complex&);
Complex operator/(const Complex&, const Complex&);

bool operator==(const Complex&, const Complex&);
bool operator!=(const Complex&, const Complex&);

std::ostream& operator<<(std::ostream&, const Complex&);
std::istream& operator>>(std::istream&, Complex&);

