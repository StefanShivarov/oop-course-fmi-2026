#include <iostream>
#include <print> 
#include "Complex.h"

int main() {
    Complex c1(3, 4);
    Complex c2(1, 2);

    std::print("c1 = ");
    std::cout << c1 << '\n';
    std::print("c2 = ");
    std::cout << c2 << '\n';

    Complex sum = c1 + c2;
    std::print("c1 + c2 = ");
    std::cout << sum << '\n';

    Complex diff = c1 - c2;
    std::print("c1 - c2 = ");
    std::cout << diff << '\n';

    Complex prod = c1 * c2;
    std::print("c1 * c2 = ");
    std::cout << prod << '\n';

    Complex div = c1 / c2;
    std::print("c1 / c2 = ");
    std::cout << div << '\n';

    Complex c3 = c1;
    c3 += c2;
    std::print("c1 += c2 -> ");
    std::cout << c3 << '\n';

    c3 = c1;
    c3 -= c2;
    std::print("c1 -= c2 -> ");
    std::cout << c3 << '\n';

    c3 = c1;
    c3 *= c2;
    std::print("c1 *= c2 -> ");
    std::cout << c3 << '\n';

    c3 = c1;
    c3 /= c2;
    std::print("c1 /= c2 -> ");
    std::cout << c3 << '\n';

    std::println("c1 == c2: {}", (c1 == c2));
    std::println("c1 != c2: {}", (c1 != c2));

    Complex input;
    std::println("Enter complex number: ");
    std::cin >> input;
    std::print("You entered: ");
    std::cout << input << '\n';

    return 0;
}