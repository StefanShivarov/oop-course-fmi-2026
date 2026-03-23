#include <iostream>
using std::cin;
using std::cout;

struct Rational {
    int numerator;
    int denominator;  
};

void readRational(Rational& rational) {
    cout << "Enter the numerator and denominator of the rational number: \n";
    cin >> rational.numerator >> rational.denominator;
}

void printRational(const Rational& r) {
    cout << r.numerator << "/" << r.denominator;
}

bool isValidRationalNumber(const Rational& rational) {
    return rational.denominator == 0 ? false : true;
}

bool isWholeNumber(const Rational& rational) {
   if (rational.denominator == 1) return true;
   else if (rational.numerator % rational.denominator == 0) return true;
   else return false;
}

void simplifyRationalNumber(Rational& rational) {
    if (!isValidRationalNumber(rational)) {
        cout << "Invalid rational number!\n";
        return;
    }
     if (isWholeNumber(rational)) {
        rational.numerator /= rational.denominator;
        rational.denominator = 1;
        return;
    }
     if (rational.denominator < 0) {
        rational.numerator *= -1;
        rational.denominator *= -1;
    }
    int a = rational.numerator;
    int b = rational.denominator;
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    int gcd = a;
    rational.numerator /= gcd;
    rational.denominator /= gcd;
}

Rational sumOfRationalNumbers(const Rational& num1, const Rational& num2) {
    Rational result;
    if (isValidRationalNumber(num1) && isValidRationalNumber(num2)) {
        if (isWholeNumber(num1) && isWholeNumber(num2)) {
            result.numerator = num1.numerator / num1.denominator + num2.numerator / num2.denominator;
            result.denominator = 1;
        }
        else if (isWholeNumber(num1) && !isWholeNumber(num2)) {
            result.numerator = num1.numerator / num1.denominator * num2.denominator + num2.numerator;
            result.denominator = num2.denominator;
        }
        else if (!isWholeNumber(num1) && isWholeNumber(num2)) {
            result.numerator = num1.numerator + num2.numerator / num2.denominator * num1.denominator;
            result.denominator = num1.denominator;
        }
        else if (!isWholeNumber(num1) && !isWholeNumber(num2)) {
            result.numerator = num1.numerator * num2.denominator + num2.numerator * num1.denominator;
            result.denominator = num1.denominator * num2.denominator;
        }
    }
    else {
        cout << "Invalid rational number(s)!\n";
        result.numerator = 0;
        result.denominator = 1;
        return result;
    }
    if (isWholeNumber(num1) && isWholeNumber(num2)) {
        result.numerator = num1.numerator / num1.denominator + num2.numerator / num2.denominator;
        result.denominator = 1;
    }
     else if (isWholeNumber(num1) && !isWholeNumber(num2)) {
        result.numerator = num1.numerator / num1.denominator * num2.denominator + num2.numerator;
        result.denominator = num2.denominator;
    }
    else if (!isWholeNumber(num1) && isWholeNumber(num2)) {
        result.numerator = num1.numerator + num2.numerator / num2.denominator * num1.denominator;
        result.denominator = num1.denominator;
    }
     else if (!isWholeNumber(num1) && !isWholeNumber(num2)) {
        result.numerator = num1.numerator * num2.denominator + num2.numerator * num1.denominator;
        result.denominator = num1.denominator * num2.denominator;
    }
     else if (num1.denominator == num2.denominator) {
        result.numerator = num1.numerator + num2.numerator;
        result.denominator = num1.denominator;
    }
    else {
        result.numerator = num1.numerator * num2.denominator + num2.numerator * num1.denominator;
        result.denominator = num1.denominator * num2.denominator;
    }
    if (num1.denominator == num2.denominator) {
        result.numerator = num1.numerator + num2.numerator;
        result.denominator = num1.denominator;
    }
    else {
        result.numerator = num1.numerator * num2.denominator + num2.numerator * num1.denominator;
        result.denominator = num1.denominator * num2.denominator;
    }
    return result;
}

Rational differenceOfRationalNumbers(const Rational& num1, const Rational& num2) {
    Rational result;
    if (!isValidRationalNumber(num1) || !isValidRationalNumber(num2)) {
        cout << "Invalid rational number(s)!\n";
        result.numerator = 0;
        result.denominator = 1;
        return result;
    }
     if (isWholeNumber(num1) && isWholeNumber(num2)) {
        result.numerator = num1.numerator / num1.denominator - num2.numerator / num2.denominator;
        result.denominator = 1;
    }
     else if (isWholeNumber(num1) && !isWholeNumber(num2)) {
        result.numerator = num1.numerator / num1.denominator * num2.denominator - num2.numerator;
        result.denominator = num2.denominator;
    }
    else if (!isWholeNumber(num1) && isWholeNumber(num2)) {
        result.numerator = num1.numerator - num2.numerator / num2.denominator * num1.denominator;
        result.denominator = num1.denominator;
    }
     else if (!isWholeNumber(num1) && !isWholeNumber(num2)) {
        result.numerator = num1.numerator * num2.denominator - num2.numerator * num1.denominator;
        result.denominator = num1.denominator * num2.denominator;
    }
     else if (num1.denominator == num2.denominator) {
        result.numerator = num1.numerator - num2.numerator;
        result.denominator = num1.denominator;
    }
    else {
        result.numerator = num1.numerator * num2.denominator - num2.numerator * num1.denominator;
        result.denominator = num1.denominator * num2.denominator;
    }
    return result;
}

Rational multiplicationOfRationalNumbers(const Rational& num1, const Rational& num2) {
    Rational result;
    if (!isValidRationalNumber(num1) || !isValidRationalNumber(num2)) {
        cout << "Invalid rational number(s)!\n";
        result.numerator = 0;
        result.denominator = 0;
        return result;
    }
    result.numerator = num1.numerator * num2.numerator;
    result.denominator = num1.denominator * num2.denominator;
    return result;
}

Rational divisionOfRationalNumbers(const Rational& num1, const Rational& num2) {
    Rational result;
    if (!isValidRationalNumber(num1) || !isValidRationalNumber(num2)) {
        cout << "Invalid rational number(s)!\n";
        result.numerator = 0;
        result.denominator = 0;
        return result;
    }
    result.numerator = num1.numerator * num2.denominator;
    result.denominator = num1.denominator * num2.numerator;
    return result;
}

int main() {
    Rational num1, num2;
    readRational(num1);
    readRational(num2);

    Rational sum = sumOfRationalNumbers(num1, num2);
    Rational difference = differenceOfRationalNumbers(num1, num2);
    Rational multiplication = multiplicationOfRationalNumbers(num1, num2);
    Rational division = divisionOfRationalNumbers(num1, num2);

    simplifyRationalNumber(sum);
    simplifyRationalNumber(difference);
    simplifyRationalNumber(multiplication);
    simplifyRationalNumber(division);

    cout << "\n";
    cout << "Sum: ";
    printRational(sum);
    cout << "\n";
    cout << "Difference: ";
    printRational(difference);
    cout << "\n";
    cout << "Multiplication: ";
    printRational(multiplication);
    cout << "\n";
    cout << "Division: ";
    printRational(division);
    cout << "\n";

    return 0;
}
