#pragma once
#include "Animal.h"

class Cow : public Animal {
public:
    Cow(const std::string& name);
    void makeSound() const override;
    std::unique_ptr<Animal> clone() const override;
};
