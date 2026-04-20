#include <iostream>

class A {
private:
    int x;
    static int y;
public:
    void g() {
        x++;
        y++;
        f();
        k();
        // here we have access to both non-static and static members
    }
    
    static void f() {
        // this->x = 4; // compilation error, since static member functions
                        // don't have access to this, and therefore don't have access
                        // to non-static members
        // g(); // also can't call non-static functions from a static member function
        y *= 2; // we have access to static members
        k(); // and we can also call other static functions only
    }

    static void k() {
        y++;
        f();
        // g(); // can't do that
        // x++; // no access to x
    }
};

int main() {
    // ...
}
