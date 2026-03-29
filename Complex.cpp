#include "Complex.h"

Complex::Complex(): real(0.0), im(0.0)
{
}

Complex::Complex(double real, double im): real(real), im(im)
{
}

double Complex::getReal() const
{
	return real;
}

double Complex::getIm() const
{
	return im;
}

void Complex::setReal(double real)
{
	this->real = real;
}

void Complex::setIm(double im)
{
	this->im = im;
}

Complex& Complex::operator+=(const Complex& complex)
{
	real += complex.real;
	im += complex.im;

	return *this;
}

Complex& Complex::operator-=(const Complex& complex)
{
	real -= complex.real;
	im -= complex.im;

	return *this;
}

Complex& Complex::operator*=(const Complex& num)
{
	double newReal = real * num.real - im * num.im;
	double newIm = real * num.im + im * num.real;
	real = newReal;
	im = newIm;
	return *this;
}

Complex& Complex::operator/=(const Complex& num)
{
	double denum = num.real * num.real + num.im * num.im;
	double newReal = (real * num.real + im * num.im) / denum;
	double newIm = (im * num.real - real * num.im) / denum;
	real = newReal;
	im = newIm;
	return *this;
}

Complex Complex::operator+() const
{
	return *this;
}

Complex Complex::operator-() const
{	
	return Complex(-real, -im);
}

Complex operator+(const Complex& num1, const Complex& num2)
{
	Complex result(num1); 
	result += num2;
	return result;
}

Complex operator-(const Complex& num1, const Complex& num2)
{
	Complex result(num1); 
	result -= num2;
	return result;
}

Complex operator*(const Complex& num1, const Complex& num2)
{
	Complex result(num1);
	result *= num2;
	return result;
}

Complex operator/(const Complex& num1, const Complex& num2)
{
	Complex result(num1);
	result /= num2;
	return result;
}

bool operator==(const Complex& num1, const Complex& num2)
{
	return (std::abs(num1.getReal() - num2.getReal()) < EPSILON 
		&& std::abs(num1.getIm() - num2.getIm()) < EPSILON);
}

bool operator!=(const Complex& num1, const Complex& num2)
{
	return !(num1==num2);
}

std::ostream& operator<<(std::ostream& of, const Complex& complex)
{
	of << complex.getReal() << " " << complex.getIm();
	return of;
}

std::istream& operator>>(std::istream& is, Complex& complex)
{
	double r, i;
	is >> r >> i;

	complex.setReal(r);
	complex.setIm(i);

	return is;
}

