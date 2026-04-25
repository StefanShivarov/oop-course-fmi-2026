#include "ComplexNumber.h"
#include <cmath>


ComplexNumber::ComplexNumber() : realPart(0), imaginaryPart(0) {}

ComplexNumber::ComplexNumber(double realPart, double imaginaryPart) : realPart(realPart), imaginaryPart(imaginaryPart) {}

double ComplexNumber::getRealPart() const {
    return this->realPart;
}

double ComplexNumber::getImaginaryPart() const {
    return this->imaginaryPart;
}

double ComplexNumber::getModulus() const {
    return std::sqrt(realPart * realPart + imaginaryPart * imaginaryPart);
}

ComplexNumber ComplexNumber::getComplexConjugate() const {
    return ComplexNumber(realPart, -imaginaryPart);
}

ComplexNumber ComplexNumber::operator+() const {
    return *this;
}

ComplexNumber ComplexNumber::operator-() const {
    return ComplexNumber(-realPart, -imaginaryPart);
}

ComplexNumber& ComplexNumber::operator+=(const ComplexNumber& other) {
    this->realPart += other.realPart;
    this->imaginaryPart += other.imaginaryPart;
    return *this;
}

ComplexNumber& ComplexNumber::operator+=(double number) {
    this->realPart += number;
    return *this;
}

ComplexNumber& ComplexNumber::operator-=(const ComplexNumber& other) {
    this->realPart -= other.realPart;
    this->imaginaryPart -= other.imaginaryPart;
    return *this;
}

ComplexNumber& ComplexNumber::operator-=(double number) {
    this->realPart -= number;
    return *this;
}

ComplexNumber& ComplexNumber::operator*=(const ComplexNumber& other) {
    double newReal = (this->realPart * other.realPart) - (this->imaginaryPart * other.imaginaryPart);
    double newImag = (this->realPart * other.imaginaryPart) + (this->imaginaryPart * other.realPart);

    this->realPart = newReal;
    this->imaginaryPart = newImag;

    return *this;
}

ComplexNumber& ComplexNumber::operator*=(double number) {
    this->realPart *= number;
    this->imaginaryPart *= number;
    return *this;
}

ComplexNumber& ComplexNumber::operator/=(const ComplexNumber& other) {
    double denominator = (other.realPart * other.realPart) + (other.imaginaryPart * other.imaginaryPart);

    double newReal = (this->realPart * other.realPart + this->imaginaryPart * other.imaginaryPart) / denominator;
    double newImag = (this->imaginaryPart * other.realPart - this->realPart * other.imaginaryPart) / denominator;

    this->realPart = newReal;
    this->imaginaryPart = newImag;

    return *this;
}

ComplexNumber& ComplexNumber::operator/=(double number) {
    this->realPart /= number;
    this->imaginaryPart /= number;
    return *this;
}

std::istream& operator>>(std::istream& is, ComplexNumber& num)
{
    return is >> num.realPart >> num.imaginaryPart;
}

std::ostream& operator<<(std::ostream& os, const ComplexNumber& num) {
    os << num.getRealPart();
    if (num.getImaginaryPart() >= 0) {
        os << " + " << num.getImaginaryPart() << "i";
    }
    else {
        os << " - " << -num.getImaginaryPart() << "i";
    }
    return os;
}

ComplexNumber operator+(ComplexNumber lhs, const ComplexNumber& rhs) {
    lhs += rhs;
    return lhs;
}

ComplexNumber operator+(const ComplexNumber& lhs, double number) {
    ComplexNumber rhs(number, 0);
    return lhs + rhs;
}

ComplexNumber operator+(double number, const ComplexNumber& rhs) {
    ComplexNumber lhs(number, 0);
    return lhs + rhs;
}

ComplexNumber operator-(ComplexNumber lhs, const ComplexNumber& rhs) {
    lhs -= rhs;
    return lhs;
}

ComplexNumber operator-(const ComplexNumber& lhs, double number) {
    ComplexNumber rhs (number, 0);
    return lhs - rhs;
}

ComplexNumber operator-(double number, const ComplexNumber& rhs) {
    ComplexNumber lhs(number, 0);
    return lhs - rhs;
}

ComplexNumber operator*(ComplexNumber lhs, const ComplexNumber& rhs) {
    lhs *= rhs;
    return lhs;
}

ComplexNumber operator*(const ComplexNumber& lhs, double number) {
    ComplexNumber rhs(number, 0);
    return lhs * rhs;
}

ComplexNumber operator*(double number, const ComplexNumber& rhs) {
    ComplexNumber lhs(number, 0);
    return lhs * rhs;
}

ComplexNumber operator/(ComplexNumber lhs, const ComplexNumber& rhs) {
    lhs /= rhs;
    return lhs;
}

ComplexNumber operator/(const ComplexNumber& lhs, double number) {
    ComplexNumber rhs(number, 0);
    return lhs / rhs;
}

ComplexNumber operator/(double number, const ComplexNumber& rhs) {
    ComplexNumber lhs(number, 0);
    return lhs / rhs;
}

bool operator==(const ComplexNumber& lhs, const ComplexNumber& rhs) {
    return lhs.getRealPart() == rhs.getRealPart() && lhs.getImaginaryPart() == rhs.getImaginaryPart();
}

bool operator==(const ComplexNumber& lhs, double number) {
    ComplexNumber rhs(number, 0);
    return lhs.getRealPart() == rhs.getRealPart() && lhs.getImaginaryPart() == rhs.getImaginaryPart();
}

bool operator==(double number, const ComplexNumber& rhs) {
    ComplexNumber lhs(number, 0);
    return lhs.getRealPart() == rhs.getRealPart() && lhs.getImaginaryPart() == rhs.getImaginaryPart();
}

bool operator!=(const ComplexNumber& lhs, const ComplexNumber& rhs) {
    return !(lhs == rhs);
}

bool operator!=(const ComplexNumber& lhs, double number) {
    return !(lhs == number);
}

bool operator!=(double number, const ComplexNumber& rhs) {
    return !(number == rhs);
}
