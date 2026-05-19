#include "AnimalFarm.h"

void AnimalFarm::copyFrom(const AnimalFarm& other)
{
    std::vector<std::unique_ptr<Animal>> copiedAnimals;
    copiedAnimals.reserve(other.animals.size());

    for (const auto& animal : other.animals)
    {
        if (!animal)
        {
            throw std::logic_error("AnimalFarm contains an empty animal pointer.");
        }

        copiedAnimals.push_back(animal->clone());
    }

    animals = std::move(copiedAnimals);
    // we do this so that we can replace the vector with the new copied one
    // if we use regular copy op=, it won't compile because
    // the vector consists of unique_ptrs, which can't be copied
}

AnimalFarm::AnimalFarm(const AnimalFarm& other) {
    copyFrom(other);
}

AnimalFarm& AnimalFarm::operator=(const AnimalFarm& other) {
    if (this != &other) {
        copyFrom(other);
    }
    return *this;
}

void AnimalFarm::addAnimal(const Animal& animal) {
    animals.push_back(animal.clone());
}

void AnimalFarm::addAnimal(const std::unique_ptr<Animal>& animal) {
    if (!animal) {
        throw std::invalid_argument("Can't add null animal!");
    }
    animals.push_back(animal->clone());
}

void AnimalFarm::wakeUpAnimals() const {
    for (const auto& animal : animals) {
        animal->makeSound();
    }
}
