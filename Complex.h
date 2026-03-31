#pragma once
#include <iostream>
class Complex
{
	private:
		double real;
		double imaginary;
	public:
		double getReal() const;
		void setReal(double number);
		double getImaginary() const;
		void setImaginary(double number);
		Complex();
		Complex(double real, double imaginary) :real(real), imaginary(imaginary) {

		}
		Complex& operator+=(const Complex& complex);
		Complex& operator-=(const Complex& complex);
		Complex& operator*=(const Complex& complex);
		Complex& operator/=(const Complex& complex);
		Complex& operator++();
		Complex operator++(int);
		Complex& operator--();
		Complex operator--(int);
		friend std::istream& operator>>(std::istream& is, Complex& number);
};
bool isEqual(double a, double b, double epsilon);
double absolute(double a);

Complex operator+(const Complex& lhs, const Complex& rhs);
Complex operator-(const Complex& lhs, const Complex& rhs);
Complex operator*(const Complex& lhs, const Complex& rhs);
Complex operator/(const Complex& lhs, const Complex& rhs);
std::ostream& operator<<(std::ostream& os, const Complex& number);
bool operator==(const Complex& lhs, const Complex& rhs);
bool operator!=(const Complex& lhs, const Complex& rhs);