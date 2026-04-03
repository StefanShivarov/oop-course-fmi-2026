#include "complex.h"
#include <math.h>
#include <iostream>
#include <fstream>
double eps = 0.00001;
complex::complex()
{
}
complex::complex(double a, double b) : real(a), imaginary(b)
{
}
complex::complex(const complex &z) : real(z.real), imaginary(z.imaginary)
{
}

double complex::getRadius() const
{
    return sqrt(this->getRadiusSq());
}
double complex::getRadiusSq() const
{
    return real * real + imaginary * imaginary;
}
double complex::getArgument() const
{
    return std::atan2(imaginary, real);
}
void complex::print() const
{
    std::cout << real << "+ i * " << imaginary;
}
void complex::printPolar() const
{
    std::cout << this->getRadius() << " * e^(i * " << this->getArgument() << ")";
}
complex complex::getComplexConjugate() const
{
    return {real, -imaginary};
}
complex complex::getMultiplicativeInverse() const
{
    if (std::abs(real) < eps && std::abs(imaginary) < eps)
        return {0, 0};
    return (this->getComplexConjugate()) * complex((1 / (this->getRadiusSq())), 0);
}
double complex::getRe() const
{
    return real;
}
double complex::getIm() const
{
    return imaginary;
}
complex &complex::operator+=(const complex &z)
{
    real = real + z.real;
    imaginary = imaginary + z.imaginary;
    return *this;
}
complex &complex::operator-=(const complex &z)
{
    *this += (-z);
    return *this;
}
complex &complex::operator*=(const complex &z)
{
    double temp = real;
    real = real * z.real - imaginary * z.imaginary;
    imaginary = temp * z.imaginary + imaginary * z.real;
    return *this;
}
complex &complex::operator/=(const complex &z)
{
    *this *= (z.getMultiplicativeInverse());
    return *this;
}
complex complex::operator+(const complex &z) const
{
    complex result(*this);
    result += z;
    return result;
}
complex complex::operator-(const complex &z) const
{
    complex result = *this;
    result += (-z);
    return result;
}
complex complex::operator*(const complex &z) const
{
    complex result = z;
    result *= (*this);
    return result;
}
complex complex::operator/(const complex &z) const
{
    complex result = *this;
    result *= (z.getMultiplicativeInverse());
    return result;
}
complex complex::operator+() const
{
    return *this;
}
complex complex::operator-() const
{
    return {-real, -imaginary};
}
bool complex::operator==(const complex &z) const
{
    return std::abs(real - z.real) < eps && std::abs(imaginary - z.imaginary) < eps;
}
bool complex::operator!=(const complex &z) const
{
    return !(*this == z);
}

std::ostream &operator<<(std::ostream &os, const complex &z)
{
    os << z.real << "+ i * " << z.imaginary;
    return os;
}
std::istream &operator>>(std::istream &is, complex &z)
{
    is >> z.real >> z.imaginary;
    return is;
}