#pragma once
#include<iostream>
class Complex {
private:
	double real;
	double im;
public:

	Complex(double real=0, double im=0);
	double getReal() const;
	double getIm() const;

	Complex& operator+=(const Complex& other);
	Complex& operator -=(const Complex& other);
	Complex& operator *=(const Complex& other);
	Complex& operator /=(const Complex& other);

	Complex operator+() const;
	Complex operator-()const;

	friend std::ostream& operator<<(std::ostream& os, const Complex& c);
	friend std::istream& operator>> (std::istream& is, Complex& c);
};

Complex operator +(const Complex& lhs, const Complex& rhs);
Complex operator -(const Complex& lhs, const Complex& rhs);
Complex operator *(const Complex& lhs, const Complex& rhs);
Complex operator /(const Complex& lhs, const Complex& rhs);


bool operator ==(const Complex& lhs, const Complex& rhs);
bool operator !=(const Complex& lhs, const Complex& rhs);