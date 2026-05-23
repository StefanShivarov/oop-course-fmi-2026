#include "HealthPotion.h"

HealthPotion::HealthPotion(const std::string& name, double effectValue) : Item(name, effectValue) {}

// std::unique_ptr<Item> HealthPotion::clone() const {
//     return std::make_unique<HealthPotion>(*this);
// }

void HealthPotion::applyToTank(Tank& tank) const {
    double amount = tank.getMaxHealth() * effectValue * 1.2;
    heal(tank, amount);
}

void HealthPotion::applyToWarrior(Warrior& warrior) const {
    double amount = warrior.getMaxHealth() * effectValue * 1.0;
    heal(warrior, amount);
}

void HealthPotion::applyToMage(Mage& mage) const {
    double amount = mage.getMaxHealth() * effectValue * 0.8;
    heal(mage, amount);
}
