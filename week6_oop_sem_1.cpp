#include <iostream>
#include "Complex.h"

int main() {
    Complex a(3, 4);
    Complex b(1, -2);

    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";

    Complex sum = a + b;
    Complex diff = a - b;
    Complex prod = a * b;
    Complex quot = a / b;

    std::cout << "a + b = " << sum << "\n";
    std::cout << "a - b = " << diff << "\n";
    std::cout << "a * b = " << prod << "\n";
    std::cout << "a / b = " << quot << "\n";

   
    std::cout << "-a = " << -a << "\n";

    
    a += b;
    std::cout << "a += b -> " << a << "\n";

    a -= b;
    std::cout << "a -= b -> " << a << "\n";

   
    std::cout << "a == b? " << (a == b ? "yes" : "no") << "\n";
    std::cout << "a != b? " << (a != b ? "yes" : "no") << "\n";

    Complex c;
    std::cout << "Enter a complex number (real imag): ";
    std::cin >> c;
    std::cout << "You entered: " << c << "\n";

    return 0;
}
