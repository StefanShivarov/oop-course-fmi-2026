
#include <iostream>

using std::cin;
using std::cout;

struct Rational {
    int nom;
    int denom;
};

int getGCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;

}

int getNOK(int a, int b) {
    int nok = (a / getGCD(a, b)) * b;
    return nok;
}

Rational add(Rational a, Rational b) {
    int denominator = getNOK(a.denom, b.denom);
    int nominator = (denominator / a.denom) * a.nom + (denominator / b.denom) * b.nom;

    return { nominator, denominator };
}

Rational subtract(Rational a, Rational b) {
    int denominator = getNOK(a.denom, b.denom);
    int nominator = (denominator / a.denom) * a.nom - (denominator / b.denom) * b.nom;

    return { nominator, denominator };
}

Rational multiply(Rational a, Rational b) {
    return { a.nom * b.nom, a.denom * b.denom };
}

Rational divide(Rational a, Rational b) {

    int nom = a.nom * b.denom;
    int denom = a.denom * b.nom;

    return { nom, denom };

}

bool isValidRational(Rational number) {
    return (number.denom != 0);
}

bool isInteger(Rational number) {
    if (number.denom == 0) return false;

    if (number.nom % number.denom == 0)
        return true;
    else
        return false;
}

int main()
{
    Rational a;
    Rational b;

    cin >> a.nom >> a.denom >> b.nom >> b.denom;

    if (!isValidRational(a) || !isValidRational(b)) {
        cout << "Denominator cannot be 0" << '\n';
    }

    Rational sum = add(a, b);
    cout << "sum = " << sum.nom << "/" << sum.denom << '\n';

    Rational diff = subtract(a, b);
    cout << "diff = " << diff.nom << "/" << diff.denom << '\n';

    Rational product = multiply(a, b);
    cout << "product = " << product.nom << "/" << product.denom << '\n';

    if (b.nom != 0) {
        Rational quotient = divide(a, b);
        cout << "quotient = " << quotient.nom << "/" << quotient.denom << '\n';
    }
    else {
        cout << "undefined";
        return 1;
    }
}