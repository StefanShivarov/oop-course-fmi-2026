#include <iostream>

using std::cout;
using std::endl;

struct A {
    A() {
        cout << "A()" << endl;
    }

    ~A() {
        cout << "~A()" << endl;
    }
};

struct B {
    B() {
        cout << "B()" << endl;
    }

    ~B() {
        cout << "~B()" << endl;
    }
};

struct C {
    A a;
    B b;

    C() : b(), a() {
        // the order of the member initializer list does not matter!
        // if we don't write anything in the member initializer list,
        // it will automatically call the default constructors of A and B!
        cout << "C()" << endl;
    }

    ~C() {
        cout << "~C()" << endl;
    }
};

struct X {
    A* a = nullptr;
    B* b = nullptr;

    X() : b(new B()) /* you can also allocate memory through the member initializer list */ {
        // since we call the constructor of A in the body, the constructor of B() will be called before A()
        this->a = new A(); // A()
        cout << "X()" << endl;
    }

    ~X() {
        delete a; // ~A()
        delete b; // ~B()
        cout << "~X()" << endl;
    }
};

int main() {
    C obj; // A() B() C()

    C arr[3]; // A() B() C() A() B() C() A() B() C()

    X obj2; // B() A() X()
}
// ~A() ~B() ~X()
// ~C() ~B() ~A() ~C() ~B() ~A() ~C() ~B() ~A()
// ~C() ~B() ~A()
