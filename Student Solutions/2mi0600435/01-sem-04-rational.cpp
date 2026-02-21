#include <iostream>

namespace Fractions {
    struct Rational {
        int numerator;
        int denominator;

        void print() const {
            std::cout << numerator << "/" << denominator << std::endl;
        }

        bool isValid() const {
			return denominator != 0;
		}

        bool isInteger() const {
            return isValid() && (numerator % denominator == 0);
		}
    };

    namespace Utils {
        void readRationals(Rational* rationals, int count) {
            for (int i = 0; i < count; i++)
            {
                std::cin >> rationals[i].numerator >> rationals[i].denominator;
            }
        }

        Rational add(const Rational& r1, const Rational& r2) {
            if (!r1.isValid() || !r2.isValid()) {
                Rational errorResult;
                errorResult.numerator = 0;
                errorResult.denominator = 0;
                return errorResult;
            }

            Rational result;
            result.numerator = r1.numerator * r2.denominator + r2.numerator * r1.denominator;
            result.denominator = r1.denominator * r2.denominator;

            return result;
		}

        Rational subtract(const Rational& r1, const Rational& r2) {
            if (!r1.isValid() || !r2.isValid()) {
                Rational errorResult;
                errorResult.numerator = 0;
                errorResult.denominator = 0;
                return errorResult;
            }

            Rational result;
            result.numerator = r1.numerator * r2.denominator - r2.numerator * r1.denominator;
            result.denominator = r1.denominator * r2.denominator;

            return result;
        }

        Rational multiply(const Rational& r1, const Rational& r2) {
            if (!r1.isValid() || !r2.isValid()) {
                Rational errorResult;
                errorResult.numerator = 0;
                errorResult.denominator = 0;
                return errorResult;
            }

            Rational result;
            result.numerator = r1.numerator * r2.numerator;
            result.denominator = r1.denominator * r2.denominator;

            return result;
		}

        Rational divide(const Rational& r1, const Rational& r2) {
            if (!r1.isValid() || !r2.isValid() || r2.numerator == 0) {
                Rational errorResult;
                errorResult.numerator = 0;
                errorResult.denominator = 0;
                return errorResult;
            }

            Rational result;
            result.numerator = r1.numerator * r2.denominator;
            result.denominator = r1.denominator * r2.numerator;

            return result;
        }
	}
}

int main() {
    using namespace Fractions;

    Rational r1;
    r1.numerator = 1;
    r1.denominator = 2;

    Rational r2;
    r2.numerator = 1;
    r2.denominator = 3;

    Rational sum = Utils::add(r1, r2);
    std::cout << "Sum: ";
    sum.print();

    Rational diff = Utils::subtract(r1, r2);
    std::cout << "Difference: ";
    diff.print();

    Rational prod = Utils::multiply(r1, r2);
    std::cout << "Product: ";
    prod.print();

    Rational quot = Utils::divide(r1, r2);
    std::cout << "Quotient: ";
    quot.print();
    std::cout << std::endl;

    Rational r3;
    r3.numerator = 10;
    r3.denominator = 5;

    r3.print();
    std::cout << "is ";
    if (r3.isInteger()) {
        std::cout << "an integer!" << std::endl;
    }
    else {
        std::cout << "NOT an integer!" << std::endl;
    }
    std::cout << std::endl;
}
