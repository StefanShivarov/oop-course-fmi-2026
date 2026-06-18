#include <iostream>
using namespace std;

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}
struct Rational {
    int numerator;
    int denominator;
    void collect(Rational otherRational) {
        int commonDenominator = gcd(denominator, otherRational.denominator);
        numerator *= commonDenominator / denominator;
        otherRational.numerator *= commonDenominator / otherRational.denominator;
        numerator += otherRational.numerator;
        denominator = commonDenominator;
        commonDenominator = gcd(denominator, numerator);
        if (commonDenominator != 1) {
            numerator /= commonDenominator;
            denominator /= commonDenominator;
        }
    }
    void subtract(Rational otherRational) {
        int commonDenominator = gcd(denominator, otherRational.denominator);
        numerator *= commonDenominator / denominator;
        otherRational.numerator *= commonDenominator / otherRational.denominator;
        numerator -= otherRational.numerator;
        denominator = commonDenominator;
        commonDenominator = gcd(denominator, numerator);
        if (commonDenominator != 1) {
            numerator /= commonDenominator;
            denominator /= commonDenominator;
        }
    }
    void multiply(Rational otherRational) {
        numerator *= otherRational.numerator;
        denominator *= otherRational.denominator;
        int commonDenominator = gcd(denominator, numerator);
        if (commonDenominator != 1) {
            numerator /= commonDenominator;
            denominator /= commonDenominator;
        }
    }
    void divide(Rational otherRational) {
        int temp = otherRational.numerator;
        otherRational.numerator = otherRational.denominator;
        otherRational.denominator = temp;
        multiply(otherRational);
    }
    bool isValidRational() const {
        return denominator != 0 && gcd(numerator, denominator) == 1;
    }
    bool isWholeNum() {
        int commonDenominator = gcd(denominator, numerator);
        if (commonDenominator != 1) {
            numerator /= commonDenominator;
            denominator /= commonDenominator;
        }
        return denominator == 1;
    }
};
int main() {

}