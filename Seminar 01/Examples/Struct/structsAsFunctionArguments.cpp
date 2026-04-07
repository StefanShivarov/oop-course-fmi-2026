#include <iostream>

// same goes for classes, unions, enums, etc. - the const-qualification rules are the same for all of them

struct A {};

void f1(A obj);
void f2(const A obj);
void f3(A& ref);
void f4(const A& ref);
void f5(A* ptr);
void f6(const A* ptr);

void f1(A obj) {
    f1(obj); // ok (recursion)
    f2(obj); // ok
    f3(obj); // ok
    f4(obj); // ok
    f5(&obj); // ok
    f6(&obj); // ok
}

void f2(const A obj) {
    f1(obj); // ok
    f2(obj); // ok (recursion)
    f3(obj); // compilation error (we can modify obj from f3)
    f4(obj); // ok
    f5(&obj); // compilation error (we can modify obj from f5)
    f6(&obj); // ok
}

void f3(A& ref) {
    f1(ref); // ok
    f2(ref); // ok
    f3(ref); // ok (recursion)
    f4(ref); // ok
    f5(&ref); // ok
    f6(&ref); // ok
}

void f4(const A& ref) {
    f1(ref); // ok
    f2(ref); // ok
    f3(ref); // compilation error (we can modify ref from f3)
    f4(ref); // ok (recursion)
    f5(&ref); // compilation error (we can modify ref from f5)
    f6(&ref); // ok
}

void f5(A* ptr) {
    f1(*ptr); // ok
    f2(*ptr); // ok
    f3(*ptr); // ok
    f4(*ptr); // ok
    f5(ptr); // ok (recursion)
    f6(ptr); // ok
}

void f6(const A* ptr) {
    f1(*ptr); // ok
    f2(*ptr); // ok
    f3(*ptr); // compilation error (we can modify ptr from f3)
    f4(*ptr); // ok
    f5(ptr); // compilation error (we can modify ptr from f5)
    f6(ptr); // ok (recursion)
}

int main() {
    // ...
}
