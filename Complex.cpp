#include "Complex.h"
#include<iostream>

constexpr double EPSILON = 00000.1;

Complex::Complex() :a(0), b(0) {}

Complex::Complex(double a,double b):a(a),b(b){}

double Complex::getA() const
{
	return a;
}

double Complex::getB() const
{
	return b;
}

Complex& Complex::operator+=(const Complex& other)
{
	a += other.a;
	b += other.b;
	return *this;
}

Complex& Complex::operator-=(const Complex& other)
{
	a -= other.a;
	b -= other.b;
	return *this;
}

Complex& Complex::operator*=(const Complex& other)
{
	double tmpA = a * other.a - b * other.b;
	double tmpB = a * other.b + b * other.a;
	a = tmpA;
	b = tmpB;

	return *this;
}

Complex& Complex::operator/=(const Complex& other)
{
	double denominator = other.a * other.a + other.b * other.b;
	if (denominator != 0)
	{
		double realPart = (a * other.a + b * other.b) / denominator;
		double imaginaryPart = (b * other.a - a * other.b) / denominator;
		a = realPart;
		b = imaginaryPart;
	}

	return *this;
}

Complex operator+(const Complex& lhs, const Complex& rhs)
{
	Complex result(lhs);
	result += rhs;
	return result;
}

Complex operator-(const Complex& lhs, const Complex& rhs)
{
	Complex result(lhs);
	result -= rhs;
	return result;
}

Complex operator*(const Complex& lhs, const Complex& rhs)
{
	Complex result(lhs);
	result *= rhs;
	return result;
}

Complex operator/(const Complex& lhs, const Complex& rhs)
{
	Complex result(lhs);
	result /= rhs;
	return result;
}

Complex Complex::operator+()const
{
	return *this;
}

Complex Complex::operator-()const
{
	return Complex(-a, -b);
}

bool operator==(const Complex& lhs, const Complex& rhs)
{
	return std::abs(lhs.getA() - rhs.getA()) < EPSILON &&
		   std::abs(lhs.getB() - rhs.getB()) < EPSILON;
}

bool operator!=(const Complex& lhs, const Complex& rhs)
{
	return !(lhs == rhs);
}

std::istream& operator>>(std::istream& is, Complex& complex)
{
	double real;
	double imaginery;
	is >> real >> imaginery;
	complex.a = real;
	complex.b = imaginery;
	return is;
}

std::ostream& operator<<(std::ostream& os, const Complex& complex)
{
	if (complex.b >= 0)
	{
		os << complex.a << " + " << complex.b << "i";
	}
	else
	{
		os << complex.a << " - " << -complex.b << "i";
	}

	return os;
}