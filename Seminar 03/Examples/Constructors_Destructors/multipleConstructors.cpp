#include <iostream>

using std::cout;
using std::endl;

class A {
private:
    int n = 0;
    char c = '0';
    double d = 0.0;

public:
    A() = default; // this sets the members to their default values or calls their default constructors

    A(int n) {
        // using this to avoid the name conflict between the parameter n and the member n
        // just like in member functions
        this->n = n;
    }

    A(int n, char c) : A(n) {
        this->c = c;
    }

    A(int n, char c, double d) : A(n, c) {
        this->d = d;
    }

    int getN() const {
        return n;
    }

    char getC() const {
        return c;
    }

    double getD() const {
        return d;
    }
};

class B {
private:
    int n;
    char c;
    double d;

public:
    B() : B(0, '0', 0.0) {
    }

    B(int n) : B(n, '0', 0.0) {
    }

    B(int n, char c) : B(n, c, 0.0) {
    }

    B(int n, char c, double d) : n(n), c(c), d(d) {
    }

    int getN() const {
        return n;
    }

    char getC() const {
        return c;
    }

    double getD() const {
        return d;
    }
};

int main() {
    cout << "Bottom-up delegation:" << endl;
    A b1;
    A b2(5);
    A b3(7, 's');
    A b4(8, 'm', 3.14);

    cout << b1.getN() << ' ' << b1.getC() << ' ' << b1.getD() << endl;
    cout << b2.getN() << ' ' << b2.getC() << ' ' << b2.getD() << endl;
    cout << b3.getN() << ' ' << b3.getC() << ' ' << b3.getD() << endl;
    cout << b4.getN() << ' ' << b4.getC() << ' ' << b4.getD() << endl;

    cout << endl;

    cout << "Top-down delegation:" << endl;
    B t1;
    B t2(5);
    B t3(7, 's');
    B t4(8, 'm', 3.14);

    cout << t1.getN() << ' ' << t1.getC() << ' ' << t1.getD() << endl;
    cout << t2.getN() << ' ' << t2.getC() << ' ' << t2.getD() << endl;
    cout << t3.getN() << ' ' << t3.getC() << ' ' << t3.getD() << endl;
    cout << t4.getN() << ' ' << t4.getC() << ' ' << t4.getD() << endl;
}
