#include <iostream>
#include <string>
#include "Vector.hpp"

template <typename T>
void printVector(const Vector<T>& v) {
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << ' ';
    }
    std::cout << '\n';
}

template <>
void printVector(const Vector<bool>& v) {
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v.get(i) << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::cout << "Vector<int>:\n";
    Vector<int> numbers;
    numbers.pushBack(10);
    numbers.pushBack(20);
    numbers.pushBack(30);

    printVector(numbers);
    std::cout << "size = " << numbers.size() << '\n';
    std::cout << "capacity = " << numbers.capacity() << '\n';

    numbers[1] = 99;
    printVector(numbers);

    std::cout << "\nVector<std::string>:\n";
    Vector<std::string> words;
    words.pushBack("templates");
    words.pushBack("in");

    std::string lang = "C++";
    words.pushBack(lang);

    printVector(words);

    std::cout << "\nVector<bool>:\n";
    Vector<bool> flags;
    flags.pushBack(true);
    flags.pushBack(false);
    flags.pushBack(true);
    flags.pushBack(false);

    printVector(flags);

    flags.set(1, true);
    flags.set(3, true);

    std::cout << "After set:\n";
    printVector(flags);

    std::cout << "size = " << flags.size() << '\n';
    std::cout << "capacity = " << flags.capacity() << '\n';

    return 0;
}