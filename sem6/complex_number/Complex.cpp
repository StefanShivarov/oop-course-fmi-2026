#include "Complex.h"

Complex::Complex() : real(0), imaginary(0)
{
}

Complex::Complex(double real, double imaginary) : real(real), imaginary(imaginary)
{
}

double Complex::getReal() const
{
	return real;
}

double Complex::getImaginary() const
{
	return imaginary;
}

Complex Complex::operator+() const
{
	return *this;
}

Complex Complex::operator-() const
{
	return Complex(-real, -imaginary);
}

Complex& Complex::operator+=(const Complex& z)
{
	real += z.real;
	imaginary += z.imaginary;
	return *this;
}

Complex& Complex::operator-=(const Complex& z)
{
	real -= z.real;
	imaginary -= z.imaginary;
	return *this;
}

Complex& Complex::operator*=(const Complex& z)
{
	double realRes = real * z.real - imaginary * z.imaginary;
	double imRes = real * z.imaginary + imaginary * z.real;

	real = realRes;
	imaginary = imRes;
	return *this;
}

Complex& Complex::operator/=(const Complex& z)
{
	double divisor = z.real * z.real + z.imaginary * z.imaginary;

	double realRes = (real * z.real + imaginary * z.imaginary) / divisor;
	double imRes = (imaginary * z.real - real * z.imaginary) / divisor;

	real = realRes;
	imaginary = imRes;

	return *this;
}

bool Complex::operator==(const Complex& z) const
{
	return (real == z.real) && (imaginary == z.imaginary);
}

bool Complex::operator!=(const Complex& z) const
{
	return !(*this == z);
}

std::ostream& operator<<(std::ostream& os, const Complex& z)
{
	os << z.real;
	if (z.imaginary >= 0) {
		os << "+";
	}
	os << z.imaginary << "i";
	return os;
}

std::istream& operator>>(std::istream& is,Complex& z)
{
	is >> z.real >> z.imaginary;
	return is;
}

Complex operator+(Complex z1, const Complex& z2)
{
	z1 += z2;
	return z1;
}

Complex operator-(Complex z1, const Complex& z2)
{
	z1 -= z2;
	return z1;
}

Complex operator*(Complex z1, const Complex& z2)
{
	z1 *= z2;
	return z1;
}

Complex operator/(Complex z1, const Complex& z2)
{
	z1 /= z2;
	return z1;
}