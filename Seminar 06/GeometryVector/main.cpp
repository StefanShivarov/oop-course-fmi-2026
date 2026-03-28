#include <iostream>
#include "GeometryVector.h"

int main() {
    GeometryVector v1(3);
    GeometryVector v2(3);

    std::cin >> v1 >> v2;

    std::cout << "v1 = " << v1 << '\n';
    std::cout << "v2 = " << v2 << '\n';

    std::cout << "v1[0] = " << v1[0] << '\n';

    std::cout << "+v1 = " << +v1 << '\n';
    std::cout << "-v1 = " << -v1 << '\n';

    std::cout << "v1 + v2 = " << v1 + v2 << '\n';
    std::cout << "v1 - v2 = " << v1 - v2 << '\n';

    std::cout << "v1 * 2 = " << v1 * 2.0 << '\n';
    std::cout << "3 * v2 = " << 3.0 * v2 << '\n';
    std::cout << "v1 / 2 = " << v1 / 2.0 << '\n';

    std::cout << "Scalar product: " << (v1 % v2) << '\n';
    std::cout << "Orthogonal: " << (v1 |= v2) << '\n';

    std::cout << "v1 == v2: " << (v1 == v2) << '\n';
    std::cout << "v1 != v2: " << (v1 != v2) << '\n';
    std::cout << "v1 < v2: " << (v1 < v2) << '\n';
    std::cout << "v1 > v2: " << (v1 > v2) << '\n';
    std::cout << "v1 <= v2: " << (v1 <= v2) << '\n';
    std::cout << "v1 >= v2: " << (v1 >= v2) << '\n';

    if (v1) {
        std::cout << "v1 is not the zero vector\n";
    } else {
        std::cout << "v1 is the zero vector\n";
    }

    GeometryVector v3 = v1;
    std::cout << "v3 = " << v3 << '\n';

    v3 += v2;
    std::cout << "After v3 += v2: " << v3 << '\n';

    v3 -= v1;
    std::cout << "After v3 -= v1: " << v3 << '\n';

    v3 *= 2;
    std::cout << "After v3 *= 2: " << v3 << '\n';

    v3 /= 2;
    std::cout << "After v3 /= 2: " << v3 << '\n';

    return 0;
}
