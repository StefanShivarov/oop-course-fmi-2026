#include <iostream>
#include <exception>
#include <string>

class MyCustomException : public std::exception {
private:
    std::string message;
    int code;

public:
    MyCustomException(const std::string& message, int code)
        : message("[MyException]: " + message), code(code) {}

    int getCode() const {
        return code;
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

struct Test {
    ~Test() {
        std::cout << "~Test()" << std::endl;
    }
};

void g() {
    Test t;
    throw MyCustomException("Exception from g", 8);
}

void f() {
    Test t;
    try {
        g();
    }
    catch (int) {
        std::cout << "Caught in f()";
        throw;
    }
}

int main() {
    try {
        f();
    }
    catch (const MyCustomException& ex) {
        std::cout << ex.what() << " " << ex.getCode();
    }
    catch (const std::exception& ex) {
        std::cout << ex.what();
    }
}
