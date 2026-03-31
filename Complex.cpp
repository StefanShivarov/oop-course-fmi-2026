#include "Complex.h"
bool isEqual(double a, double b, double epsilon)
{
	return absolute(a - b) < epsilon;
}

double absolute(double a)
{
	if (a > 0.0) return a;
	return -a;
}

double Complex::getReal() const
{
	return real;
}

void Complex::setReal(double number)
{
	real = number;
}

double Complex::getImaginary() const
{
	return imaginary;
}

void Complex::setImaginary(double number)
{
	imaginary = number;
}

Complex::Complex()
{
	real = 0;
	imaginary = 0;
}

Complex& Complex::operator+=(const Complex& complex)
{
	real += complex.real;
	imaginary += complex.imaginary;
	return *this;
}

Complex& Complex::operator-=(const Complex& complex)
{
	real -= complex.real;
	imaginary -= complex.imaginary;
	return *this;
}

Complex& Complex::operator*=(const Complex& complex)
{
	real = real * complex.real - imaginary * complex.imaginary;
	imaginary = real * complex.imaginary + imaginary * complex.real;
	return *this;
}

Complex& Complex::operator/=(const Complex& complex)
{
	double denom = complex.real * complex.real + complex.imaginary * complex.imaginary;
	if (denom == 0.0)
	{
		return *this;
	}

	real = (real * complex.real + imaginary * complex.imaginary) / denom;
	imaginary = (imaginary * complex.real - real * complex.imaginary) / denom;
	return *this;
}
Complex& Complex::operator++()
{
	++real;
	++imaginary;
	return *this;
}
Complex Complex::operator++(int)
{
	Complex result(*this);
	++*this;
	return result;
}
Complex& Complex::operator--()
{
	--real;
	--imaginary;
	return *this;
}
Complex Complex::operator--(int)
{
	Complex result(*this);
	--*this;
	return result;
}

std::istream& operator>>(std::istream& is, Complex& number)
{
	return is >> number.real >> number.imaginary;
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

std::ostream& operator<<(std::ostream& os, const Complex& number)
{
	return os << number.getReal() << " + " << number.getImaginary() << "i";
}

bool operator==(const Complex& lhs, const Complex& rhs)
{
	const double epsilon = 1e-10;
	return isEqual(lhs.getReal(), rhs.getReal(), epsilon) &&
		isEqual(lhs.getImaginary(), rhs.getImaginary(), epsilon);
}

bool operator!=(const Complex& lhs, const Complex& rhs)
{
	return !(lhs == rhs);
}