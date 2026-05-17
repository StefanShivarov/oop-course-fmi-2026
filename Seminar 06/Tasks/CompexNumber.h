#pragma once
#include<iostream>

class Complex{
	double real = 0;
	double imaginary = 0;
public:
	void setRealNum(double real);
	void setImaginaryNum(double imaginary);
	
	double getRealNum()const;
	double getImaginaryNum() const;

	Complex();
	Complex(double real, double imaginary);

	Complex getConjugated() const;

	Complex& operator+=(const Complex& other);
	Complex& operator-=(const Complex& other);
	Complex& operator*=(const Complex& other);
	Complex& operator/=(const Complex& other);

	friend std::istream& operator>>(std::istream& is,Complex& num);
	friend std::ostream& operator<<(std::ostream& os, const Complex& num);

};

bool operator==(const Complex& lhs, const Complex& rhs);
bool operator!=(const Complex& lhs, const Complex& rhs);

std::istream& operator>>(std::istream& is,Complex& num);
std::ostream& operator<<(std::ostream& os, const Complex& num);

Complex operator+(const Complex& num);
Complex operator-(const Complex& num);

Complex operator+(const Complex& lhs, const Complex& rhs);
Complex operator-(const Complex& lhs, const Complex& rhs);
Complex operator*(const Complex& lhs, const Complex& rhs);
Complex operator/(const Complex& lhs, const Complex& rhs);