#include "demo.h"
// #include "demo.h" pastes the content of demo.h here
// therefore the a.cpp file will have its own static int x = 0
// which is only for this translation unit

void f() {
    counter++;
    std::cout << "f() counter: " << counter << '\n';
}
