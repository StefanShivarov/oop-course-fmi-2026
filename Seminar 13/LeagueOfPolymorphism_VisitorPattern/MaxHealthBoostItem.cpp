#include "MaxHealthBoostItem.h"

MaxHealthBoostItem::MaxHealthBoostItem(std::string name, double effectValue) : Item(name, effectValue) {}

// std::unique_ptr<Item> MaxHealthBoostItem::clone() const {
//     return std::make_unique<MaxHealthBoostItem>(*this);
// }

void MaxHealthBoostItem::applyToTank(Tank& tank) const {
    double amount = tank.getMaxHealth() * effectValue * 1.5;
    increaseMaxHealth(tank, amount);
}

void MaxHealthBoostItem::applyToWarrior(Warrior& warrior) const {
    double amount = warrior.getMaxHealth() * effectValue * 1.0;
    increaseMaxHealth(warrior, amount);
}

void MaxHealthBoostItem::applyToMage(Mage& mage) const {
    double amount = mage.getMaxHealth() * effectValue * 0.8;
    increaseMaxHealth(mage, amount);
}
