#include "Singleton.h"
#include <iostream>

Singleton::Singleton()
{
    std::cout << "Singleton()\n";
}

Singleton::~Singleton()
{
    std::cout << "~Singleton()\n";
}

Singleton& Singleton::getInstance()
{
    static Singleton instance;
    return instance;
}
