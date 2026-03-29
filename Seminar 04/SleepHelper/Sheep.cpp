#include "Sheep.h"
#include <iostream>

int Sheep::totalSheepCount = 0;

Sheep::Sheep() : id(++totalSheepCount) {}

bool Sheep::jump() {
    if (hasJumped) {
        return false;
    }
    std::cout << "Sheep " << id << " jumped!\n";
    hasJumped = true;
    return true;
}

int Sheep::getId() const {
    return id;
}


