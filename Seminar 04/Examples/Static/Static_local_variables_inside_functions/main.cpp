#include <iostream>

class A {
public:
    A() {
        std::cout << "A()" << '\n';
    }

    ~A() {
        std::cout << "~A()" << '\n';
    }
};

int normalCounter() {
    int x = 0;
    ++x;
    return x;
}

int staticCounter() {
    static int x = 0;
    ++x;
    return x;
}

void staticObject() {
    static A obj; // this object is created only in the first call of this function
    std::cout << "calling static obj function..." << '\n';
}

int main() {
    staticObject(); // A()
                    // calling static obj function....
    staticObject(); // calling static obj function...
    std::cout << normalCounter() << '\n'; // 1
    std::cout << normalCounter() << '\n'; // 1
    std::cout << normalCounter() << '\n'; // 1

    std::cout << staticCounter() << '\n'; // 1
    std::cout << staticCounter() << '\n'; // 2
    std::cout << staticCounter() << '\n'; // 3

    staticObject(); // calling static obj function...

}
// ~A() (the static A obj from the staticObject() function is destroyed when the program finishes)
