#include <iostream>
#include <print>
using namespace std;
struct Rational 
{
    int numerator;
    int denominator;
};
bool isValid(const Rational& r)
{
    return r.denominator != 0;
}
bool isWhole(const Rational& r)
{
    return r.numerator % r.denominator == 0;
}
Rational add(const Rational& r1, const Rational& r2)
{
    Rational result;
    result.numerator = (r1.numerator * r2.denominator) + (r2.numerator * r1.denominator);
    result.denominator = r1.denominator * r2.denominator;
    return result;
}
Rational subtract(const Rational& r1, const Rational& r2)
{
    Rational result;
    result.numerator = (r1.numerator * r2.denominator) - (r2.numerator * r1.denominator);
    result.denominator = r1.denominator * r2.denominator;
    return result;
}
Rational multiply(const Rational& r1, const Rational& r2)
{
    Rational result;
    result.numerator = r1.numerator * r2.numerator;
    result.denominator = r1.denominator * r2.denominator;
    return result;
}
Rational divide(const Rational& r1, const Rational& r2)
{
    Rational result;
    result.numerator = r1.numerator * r2.denominator;
    result.denominator = r1.denominator * r2.numerator;
    return result;
}
int main()
{
    
}
