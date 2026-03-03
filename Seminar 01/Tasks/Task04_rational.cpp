#include <iostream>

using std::cin;
using std::cout;
using std::abs;

namespace utils {
    int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
}

struct RationalNumber {
    int numerator;
    int denominator;
};

void rationalizeRationalNumber(RationalNumber& rationalNumber) {
    int gcdValue = utils::gcd(rationalNumber.denominator, rationalNumber.numerator);
    rationalNumber.numerator /= gcdValue;
    rationalNumber.denominator /= gcdValue;
}

RationalNumber addRationalNumbers(const RationalNumber& a, const RationalNumber& b) {
    int resultDenominator = a.denominator * b.denominator;
    int resultNumerator = a.numerator * b.denominator + a.denominator * b.numerator;
    RationalNumber result { resultNumerator, resultDenominator };
    rationalizeRationalNumber(result);
    return result;
}

RationalNumber subtractRationalNumbers(const RationalNumber& a, const RationalNumber& b) {
    int resultDenominator = a.denominator * b.denominator;
    int resultNumerator = a.numerator * b.denominator - a.denominator * b.numerator;
    RationalNumber result { resultNumerator, resultDenominator };
    rationalizeRationalNumber(result);
    return result;
}

RationalNumber multiplyRationalNumbers(const RationalNumber& a, const RationalNumber& b) {
    RationalNumber result = { a.numerator * b.numerator, a.denominator * b.denominator };
    rationalizeRationalNumber(result);
    return result;
}

RationalNumber divideRationalNumbers(const RationalNumber& a, const RationalNumber& b) {
    RationalNumber reciprocalOfB { b.denominator, b.numerator };
    return multiplyRationalNumbers(a, reciprocalOfB);
}

bool isValidRationalNumber(const RationalNumber& rationalNumber) {
    return rationalNumber.denominator != 0;
}

bool isWholeNumber(const RationalNumber& rationalNumber) {
    return rationalNumber.numerator % rationalNumber.denominator == 0;
}

void printRationalNumber(const RationalNumber& rationalNumber) {
    bool negativeDenominator = rationalNumber.denominator < 0;
    bool negativeNumerator = rationalNumber.numerator < 0;
    bool isNegative = !(negativeDenominator && negativeNumerator) && (negativeDenominator || negativeNumerator);
    cout << (isNegative ? "-(" : "") << abs(rationalNumber.numerator) << "/" << abs(rationalNumber.denominator) << (isNegative ? ")" : "") << '\n';
}

int main() {
    RationalNumber a{ 1, 2 };
    RationalNumber b = { 3, 4 };

    printRationalNumber(addRationalNumbers(a, b)); // 5/4
    printRationalNumber(subtractRationalNumbers(a, b)); // -(1/4)
    printRationalNumber(multiplyRationalNumbers(a, b)); // 3/8 
    printRationalNumber(divideRationalNumbers(a, b)); // 2/3

    printRationalNumber({-1, -2}); // 1/2
}
