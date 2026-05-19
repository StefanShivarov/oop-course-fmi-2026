#pragma once
#include <iostream>
#include <memory>

class Animal {
public:
    explicit Animal(const std::string& name);

    const std::string& getName() const;

    // this class does not know what specific type of animal it is and at this point it can't
    // define what sound it makes
    // at the same time we want all specific animals to be able to make some sound,
    // so this function is a perfect example of a pure virtual function,
    // therefore we can make the Animal an abstract class
    virtual void makeSound() const = 0;

    // This cloning function's purpose is so that we can create deep copies
    // of pointers to polymorphic objects, without needing to know
    // the specific type of object, in this case specific type of animal...
    // Each animal knows what it is, and overrides the clone() function to
    // call its constructor accordingly, we don't need to know the type of the animal inside the farm class
    virtual std::unique_ptr<Animal> clone() const = 0;

    virtual ~Animal() = default;

protected:
    std::string name;
};
