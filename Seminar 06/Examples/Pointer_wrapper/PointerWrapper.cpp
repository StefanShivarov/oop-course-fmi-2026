#pragma once
#include <iostream>

class Example {
private:
    int x;
    int y;

public:
    Example(int x, int y) : x(x), y(y) {}

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }
};

class PointerWrapper {
private:
    Example* ptr;

public:
    PointerWrapper(Example* ptr) : ptr(ptr) {}

    PointerWrapper(const PointerWrapper&) = delete;
    PointerWrapper& operator=(const PointerWrapper&) = delete;

    ~PointerWrapper() {
        delete ptr;
    }

    Example* operator->() {
        return ptr;
    }

    const Example* operator->() const {
        return ptr;
    }
};

int main() {
    PointerWrapper wrapper(new Example(10, 20));
    std::cout << wrapper->getX() << '\n'; // the operator-> makes PointerWrapper act as a pointer itself
    std::cout << wrapper->getY() << '\n';

    std::cout << wrapper.operator->()->getX() << '\n';
    std::cout << wrapper.operator->()->getY();
}
