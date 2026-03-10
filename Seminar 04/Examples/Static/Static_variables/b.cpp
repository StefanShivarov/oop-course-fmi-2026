#include "demo.h"

// #include "demo.h" pastes the content of demo.h here
// therefore the b.cpp file will have its own static int x = 0
// which is only for this translation unit

// IMPORTANT: this is not the same counter as the one for a.cpp

void g() {
    counter++;
    std::cout << "g() counter: " << counter << '\n';
}
