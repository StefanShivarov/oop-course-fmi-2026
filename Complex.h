#pragma once
#include<fstream>

class Complex
{
private:
	double a = 0;
	double b = 0;

public:
	Complex();
	Complex(double a, double b);

	double getA()const;
	double getB()const;

	Complex& operator+=(const Complex& other);
	Complex& operator-=(const Complex& other);
	Complex& operator*=(const Complex& other);
	Complex& operator/=(const Complex& other);

	Complex operator+() const;
	Complex operator-() const;

	friend std::istream& operator>>(std::istream& is, Complex& complex);
	friend std::ostream& operator<<(std::ostream& os, const Complex& complex);
};

Complex operator+(const Complex& lhs, const Complex& rhs);
Complex operator-(const Complex& lhs, const Complex& rhs);
Complex operator*(const Complex& lhs, const Complex& rhs);
Complex operator/(const Complex& lhs, const Complex& rhs);

bool operator==(const Complex& lhs, const Complex& rhs);
bool operator!=(const Complex& lhs, const Complex& rhs);