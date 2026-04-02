#include "Complex.h"

Complex::Complex(const int real, const int imag) : real(real), imag(imag) {}
Complex Complex::operator+(const Complex &rhs) const {
    return Complex(real + rhs.real, imag + rhs.imag);
}
Complex Complex::operator-(const Complex &rhs) const {
    return Complex(real - rhs.real, imag - rhs.imag);
}
Complex Complex::operator*(const Complex &rhs) const {
    return Complex(real * rhs.real, imag * rhs.imag);
}
Complex Complex::operator/(const Complex &rhs) const {
    return Complex(real / rhs.real, imag / rhs.imag);
}

Complex Complex::operator+() const {
    return *this;
}
Complex Complex::operator-() const {
    return Complex(-real, -imag);
}

Complex& Complex::operator+=(const Complex &rhs) {
    real += rhs.real;
    imag += rhs.imag;
    return *this;
}
Complex& Complex::operator-=(const Complex &rhs) {
    real -= rhs.real;
    imag -= rhs.imag;
    return *this;
}
Complex& Complex::operator*=(const Complex &rhs) {
    real *= rhs.real;
    imag *= rhs.imag;
    return *this;
}
Complex& Complex::operator/=(const Complex &rhs) {
    real /= rhs.real;
    imag /= rhs.imag;
    return *this;
}

bool Complex::operator==(const Complex &rhs) const {
    return real == rhs.real && imag == rhs.imag;
}
bool Complex::operator!=(const Complex &rhs) const {
    return real != rhs.real || imag != rhs.imag;
}

std::ostream & operator<<(std::ostream &os, const Complex &c) {
    os << c.real << " + " << c.imag << "i";
    return os;
}
std::istream & operator>>(std::istream &is, Complex &c) {
    is >> c.real >> c.imag;
    return is;
}