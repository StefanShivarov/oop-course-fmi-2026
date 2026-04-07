#include <iostream>

void f();
void g();

int main() {
    f(); // f() counter: 1
    f(); // f() counter: 2
    f(); // f() counter: 3

    g(); // g() counter: 1
    g(); // g() counter: 2
    g(); // g() counter: 3
}
