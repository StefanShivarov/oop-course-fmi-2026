#pragma once
#include <iostream>

class Complex {
private:
	double real = 0;
	double imaginary = 0;

public:
	Complex();
	Complex(double real, double imaginary);

	double getReal() const;
	double getImaginary() const;
	
	Complex operator+() const;
	Complex operator-() const;

	Complex& operator+=(const Complex& z);
	Complex& operator-=(const Complex& z);
	Complex& operator*=(const Complex& z);
	Complex& operator/=(const Complex& z);

	bool operator==(const Complex& z) const;
	bool operator!=(const Complex& z) const;

	friend std::ostream& operator<<(std::ostream& os, const Complex& z);
	friend std::istream& operator>>(std::istream& is, Complex& z);
};

Complex operator+(Complex z1, const Complex& z2);
Complex operator-(Complex z1, const Complex& z2);
Complex operator*(Complex z1, const Complex& z2);
Complex operator/(Complex z1, const Complex& z2);