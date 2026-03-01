#include <iostream>

struct Rational {
    int x;
    int y;
};

void printRational(Rational r) {
    std::cout << r.x << " / " << r.y;
}

int gcd(int x, int y)
{
    if (y == 0) {
        return x == 0 ? 1 : x;
    }
    return gcd(y, x % y);
}

int lcm(int x, int y)
{
    return std::abs((x / (gcd(x, y))) * y);
}

void simplify(Rational &r)
{
    int d = gcd(r.x, r.y);
    r.x = r.x / d;
    r.y = r.y / d;
}

Rational simplified(const Rational& r) {
    int d = gcd(r.x, r.y);
    return { r.x / d, r.y / d };
}

Rational sum(Rational r, Rational m)
{
    int g = gcd(r.y, m.y);
    Rational q = {r.x * (m.y / g) + m.x * (r.y / g), r.y * (m.y / g)};
    return simplified(q);
}

Rational subtract(const Rational& r,const Rational &m)
{
    return sum(r, {-m.x, m.y});
}

Rational multiply(Rational r, Rational m)
{
    int q, w;
    simplify(r);
    simplify(m);
    int g = gcd(r.x, m.y);
    int g1 = gcd(m.x, r.y);
    q = (r.x / g) * (m.x / g1);
    w = (m.y / g) * (r.y / g1);
    return {q, w};
}

Rational divide(Rational r, Rational m)
{
    return multiply({r.x, r.y}, {m.y, m.x});
}

bool isValid(Rational r)
{
    return r.y != 0;
}

bool isWholeNumber(Rational r)
{
    return r.x % r.y == 0;
}

int main()
{
    int x, y;
    std::cin >> x;
    std::cin >> y;
    int x1, y1;
    std::cin >> x1;
    std::cin >> y1;
    Rational q = {x, y};
    Rational q1 = {x1, y1};
    if(isValid(q) && isValid(q1)){

        std::cout << "\n Sum: ";
        printRational(sum(q, q1));
    std::cout << "\n Subtraction: ";
    printRational(subtract(q, q1));
    std::cout << "\n Multiplication: ";
    printRational(multiply(q, q1));
    std::cout << "\n Division: ";
    printRational(divide(q, q1));

    }else {
        std::cout<<"Invalid.";
    }
}