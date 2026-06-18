#include <iostream>
#include "Complex.h"

using namespace std;

int main() {
    Complex complex1(2, 3), complex2(4, 5);
    std::cout << complex1 << std::endl;
    std::cout << complex2 << std::endl;
    complex1 += complex2;
    std::cout << complex1 << std::endl;
}