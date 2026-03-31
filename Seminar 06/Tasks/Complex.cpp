#include "Complex.h"
#include <cmath>
Complex::Complex() : real(0), imaginary(0)
{
}

Complex::Complex(double real, double im) : real(real), imaginary(im)
{
}

Complex& Complex::operator+=(const Complex& other)
{
	this->real += other.real;
	this->imaginary += other.imaginary;
	return *this;
}

Complex& Complex::operator-=(const Complex& other)
{
	this->real -= other.real;
	this->imaginary -= other.imaginary;
	return *this;
}

Complex& Complex::operator*=(const Complex& other)
{
	double oldReal = this->real;
	this->real = (this->real * other.real) - (this->imaginary * other.imaginary);
	this->imaginary = (oldReal * other.imaginary) + (this->imaginary * other.real);
	return *this;
}

Complex& Complex::operator/=(const Complex& other)
{ 
	double denominator = pow(other.real, 2) + pow(other.imaginary, 2);
	if (denominator == 0)
	{
		std::cout << "Error";
		return *this;
	}
	double oldReal = this->real;
	this->real = ((this->real * other.real) + (this->imaginary * other.imaginary)) / denominator;
	this->imaginary = ((this->imaginary * other.real) - (oldReal * other.imaginary)) / denominator;
	return *this;
}

Complex Complex::operator+() const
{
	
	return *this;
}

Complex Complex::operator-() const
{
	return Complex(-real,-imaginary);
}

const double Complex::getReal() const
{
	return this->real;
}

const double Complex::getIm() const
{
	return this->imaginary;
}

std::ostream& operator<<(std::ostream& os, const Complex& complex)
{
	char sign = complex.imaginary < 0 ? '-' : '+';
	if (complex.real == 0 && complex.imaginary == 0)
	{
		os << "Your complex number is: 0 \n";
		return os;
	}
	if (complex.real == 0)
	{
		os << "Your complex number is: " << complex.imaginary << "i \n";
		return os;
	}
	if (complex.imaginary == 0)
	{
		os << "Your complex number is: " << complex.real << std::endl;
		return os;
	}
	os << "Your complex number is: " << complex.real << " " << sign  << " " << abs(complex.imaginary) << "i \n";
	return os;
}

std::istream& operator>>(std::istream& is, Complex& complex)
{
	is >> complex.real >> complex.imaginary;
	return is;
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
	return result;;
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

bool operator==(const Complex& lhs, const Complex& rhs)
{
	const double epsilon = 0.00000000001;
	return (abs(lhs.getReal() - rhs.getReal()) < epsilon) && (abs(lhs.getIm() - rhs.getIm()) < epsilon);
}

bool operator!=(const Complex& lhs, const Complex& rhs)
{
	return !(lhs == rhs);
}
