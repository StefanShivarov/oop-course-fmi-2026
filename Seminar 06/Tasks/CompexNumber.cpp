#include "CompexNumber.h"

namespace Utility {
	constexpr double EPSILON = 1e-9;
}

void Complex::setRealNum(double real)
{
	this->real = real;
}

void Complex::setImaginaryNum(double imaginary)
{
	this->imaginary = imaginary;
}

double Complex::getRealNum() const
{
	return real;
}

double Complex::getImaginaryNum() const
{
	return imaginary;
}

Complex::Complex() : real(0.0), imaginary(0.0)
{
}

Complex::Complex(double real, double imaginary) : real(real), imaginary(imaginary)
{
}

Complex Complex::getConjugated() const
{
	return Complex(real,-imaginary);
}

Complex& Complex::operator+=(const Complex& other)
{
	real += other.real;
	imaginary += other.imaginary;
	return *this;
}

Complex& Complex::operator-=(const Complex& other)
{
	real -= other.real;
	imaginary -= other.imaginary;
	return *this;
}

Complex& Complex::operator*=(const Complex& other)
{
	double currentReal = real;
	real = real * other.real - imaginary * other.imaginary;
	imaginary = currentReal * other.imaginary + imaginary * other.real;
	return *this;
}

Complex& Complex::operator/=(const Complex& other)
{
	Complex conjugated = other.getConjugated();
	Complex otherCopy(other);

	*this *= conjugated;
	otherCopy *= conjugated;

	if (otherCopy.real != 0) {
		real /= otherCopy.real;
		imaginary /= otherCopy.real;
	}
	return *this;
}

std::istream& operator>>(std::istream& is, Complex& num)
{
	is >> num.real >> num.imaginary;
	return is;
}

std::ostream& operator<<(std::ostream& os, const Complex& num)
{
	os << num.real << ' ' << num.imaginary << 'i';
	return os;
}

Complex operator+(const Complex& num)
{
	return num;
}

Complex operator-(const Complex& num)
{
	return Complex(-num.getRealNum(), -num.getImaginaryNum());
}

Complex operator+(const Complex& lhs, const Complex& rhs)
{
	Complex result = lhs;
	result += rhs;
	return result;
}

Complex operator-(const Complex& lhs, const Complex& rhs)
{
	Complex result = lhs;
	result -= rhs;
	return result;
}

Complex operator*(const Complex& lhs, const Complex& rhs)
{
	Complex result = lhs;
	result *= rhs;
	return result;
}

Complex operator/(const Complex& lhs, const Complex& rhs)
{
	Complex result = lhs;
	result /= rhs;
	return result;
}

bool operator==(const Complex& lhs, const Complex& rhs)
{
	return (lhs.getRealNum() - rhs.getRealNum()) < Utility::EPSILON &&
		(lhs.getImaginaryNum() - rhs.getImaginaryNum()) < Utility::EPSILON;
}

bool operator!=(const Complex& lhs, const Complex& rhs)
{
	return !(lhs == rhs);
}
