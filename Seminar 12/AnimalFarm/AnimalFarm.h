#pragma once
#include "Animal.h"

class AnimalFarm {
public:
    AnimalFarm() = default;

    // we need to implement the copying operations ourselves,
    // because the compiler-generated ones won't work for a few reasons:
    // 1. the unique_pointers
    // 2. if we want to make deep copy of the animals inside the farm,
    // instead of using the same objects (shallow-copy),
    // we should create new pointers with the correct constructor
    // which is why we use the clone() function (Prototype design pattern)

    AnimalFarm(const AnimalFarm& other);
    AnimalFarm& operator=(const AnimalFarm& other);

    AnimalFarm(AnimalFarm&& other) noexcept = default;
    AnimalFarm& operator=(AnimalFarm&& other) noexcept = default;

    void addAnimal(const Animal& animal);
    void addAnimal(const std::unique_ptr<Animal>& animal);

    void wakeUpAnimals() const;

private:
    std::vector<std::unique_ptr<Animal>> animals;

    void copyFrom(const AnimalFarm& other);
};
