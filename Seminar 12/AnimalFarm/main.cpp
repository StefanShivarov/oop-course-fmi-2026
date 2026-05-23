#include "AnimalFarm.h"
#include "Animal.h"
#include "Pig.h"
#include "Cow.h"
#include "Sheep.h"

int main() {
    AnimalFarm animalFarm;
    Pig peppaPig("Peppa the Pig");
    Cow cow("Milka");
    Sheep sheep("Dolly");
    std::unique_ptr<Animal> pig = std::make_unique<Pig>("Piglet");


    animalFarm.addAnimal(peppaPig); // addAnimal(const Animal&)
    animalFarm.addAnimal(pig); // addAnimal(const unique_ptr<Animal>& )
    animalFarm.addAnimal(cow);
    animalFarm.addAnimal(sheep);

    try {
        animalFarm.addAnimal(nullptr);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    animalFarm.wakeUpAnimals();

    AnimalFarm animalFarm2 = animalFarm; // this performs deep copying of unique_ptrs!
                                        // the copies of the unique_ptrs are separate unique_ptrs pointing to
                                        // separate but equivalent objects
    animalFarm2.wakeUpAnimals();
}
