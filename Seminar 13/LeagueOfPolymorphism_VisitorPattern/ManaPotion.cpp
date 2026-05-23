#include "ManaPotion.h"

ManaPotion::ManaPotion(const std::string& name, double effectValue) : Item(name, effectValue) {}

void ManaPotion::applyToTank(Tank& tank) const {
    // no effect
}

void ManaPotion::applyToWarrior(Warrior& warrior) const {
    // no effect
}

void ManaPotion::applyToMage(Mage& mage) const {
    double amount = mage.getMaxHealth() * effectValue;
    restoreMana(mage, amount);
}

// std::unique_ptr<Item> ManaPotion::clone() const {
//     return std::make_unique<ManaPotion>(*this);
// }
