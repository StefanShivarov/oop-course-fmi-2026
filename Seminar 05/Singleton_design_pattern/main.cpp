#include "Singleton.h"
#include <iostream>
using namespace std;
int main() {
    Singleton& s1 = Singleton::getInstance();
    Singleton& s2 = Singleton::getInstance();
    Singleton& s3 = Singleton::getInstance();

    std::cout << &s1 << " " << &s2 << " " << &s3 << std::endl;
}
