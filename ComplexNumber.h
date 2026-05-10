#pragma once
#include <fstream>

class ComplexNumber {
private:
	double realPart;
	double imaginaryPart;

public:
	ComplexNumber();
	ComplexNumber(double realPart, double imaginaryPart);

	double getRealPart() const;
	double getImaginaryPart() const;
	double getModulus() const;

	ComplexNumber getComplexConjugate() const;

	ComplexNumber operator+() const;
	ComplexNumber operator-() const;

	ComplexNumber& operator+=(const ComplexNumber& other);
	ComplexNumber& operator+=(double number);
	ComplexNumber& operator-=(const ComplexNumber& other);
	ComplexNumber& operator-=(double number);
	ComplexNumber& operator*=(const ComplexNumber& other);
	ComplexNumber& operator*=(double number);
	ComplexNumber& operator/=(const ComplexNumber& other);
	ComplexNumber& operator/=(double number);

	friend std::istream& operator>>(std::istream& is, ComplexNumber& num);
};

std::ostream& operator<<(std::ostream& os, const ComplexNumber& num);

ComplexNumber operator+(ComplexNumber lhs, const ComplexNumber& rhs);
ComplexNumber operator+(const ComplexNumber& lhs, double number);
ComplexNumber operator+(double number, const ComplexNumber& rhs);

ComplexNumber operator-(ComplexNumber lhs, const ComplexNumber& rhs);
ComplexNumber operator-(const ComplexNumber& lhs, double number);
ComplexNumber operator-(double number, const ComplexNumber& rhs);

ComplexNumber operator*(ComplexNumber lhs, const ComplexNumber& rhs);
ComplexNumber operator*(const ComplexNumber& lhs, double number);
ComplexNumber operator*(double number, const ComplexNumber& rhs);

ComplexNumber operator/(ComplexNumber lhs, const ComplexNumber& rhs);
ComplexNumber operator/(const ComplexNumber& lhs, double number);
ComplexNumber operator/(double number, const ComplexNumber& rhs);

bool operator==(const ComplexNumber& lhs, const ComplexNumber& rhs);
bool operator==(const ComplexNumber& lhs, double number);
bool operator==(double number, const ComplexNumber& rhs);

bool operator!=(const ComplexNumber& lhs, const ComplexNumber& rhs);
bool operator!=(const ComplexNumber& lhs, double number);
bool operator!=(double number, const ComplexNumber& rhs);