#include "Vector.hpp"

int main() {
    Vector<int> v;
    v.pushBack(10);
    v.pushBack(20);
    v.pushBack(30);

    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << '\n';

    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << '\n';

    const Vector<int>& cv = v;
    for (Vector<int>::ConstIterator it = cv.begin(); it != cv.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << '\n';

    // you can also use for-each range loop
    for (int element : cv) {
        std::cout << element << " ";
    }

}
