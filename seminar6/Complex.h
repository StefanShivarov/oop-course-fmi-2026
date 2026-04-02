#ifndef SEMINAR6_COMPLEX_H
#define SEMINAR6_COMPLEX_H

#include <iostream>

class Complex {
    int real, imag;

public:
    explicit Complex(int real = 0, int imag = 0);

    Complex operator+(const Complex& rhs) const;
    Complex operator-(const Complex& rhs) const;
    Complex operator*(const Complex& rhs) const;
    Complex operator/(const Complex& rhs) const;

    Complex operator+() const;
    Complex operator-() const;

    Complex& operator+=(const Complex& rhs);
    Complex& operator-=(const Complex& rhs);
    Complex& operator*=(const Complex& rhs);
    Complex& operator/=(const Complex& rhs);

    bool operator==(const Complex& rhs) const;
    bool operator!=(const Complex& rhs) const;

    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
    friend std::istream& operator>>(std::istream& is, Complex& c);
};



#endif //SEMINAR6_COMPLEX_H
