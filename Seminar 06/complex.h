#pragma once
#include <fstream>
class complex
{
private:
    double real = 0;
    double imaginary = 0;

public:
    complex();
    complex(double a, double b);
    complex(const complex &z);
    double getRadius() const;
    double getRadiusSq() const;
    double getArgument() const;
    void print() const;
    void printPolar() const;
    complex getComplexConjugate() const;
    complex getMultiplicativeInverse() const;
    double getRe() const;
    double getIm() const;
    complex &operator+=(const complex &z);
    complex &operator-=(const complex &z);
    complex &operator*=(const complex &z);
    complex &operator/=(const complex &z);
    complex operator+(const complex &z) const;
    complex operator-(const complex &z) const;
    complex operator*(const complex &z) const;
    complex operator/(const complex &z) const;
    complex operator+() const;
    complex operator-() const;
    bool operator==(const complex &z) const;
    bool operator!=(const complex &z) const;
    friend std::ostream &operator<<(std::ostream &os, const complex &z);
    friend std::istream &operator>>(std::istream &is, complex &z);
};