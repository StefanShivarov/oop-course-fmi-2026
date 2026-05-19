#include "MaxManaBoostItem.h"

MaxManaBoostItem::MaxManaBoostItem(std::string name, double effectValue) : Item(name, effectValue) {}

// std::unique_ptr<Item> MaxManaBoostItem::clone() const {
//     return std::make_unique<MaxManaBoostItem>(*this);
// }

void MaxManaBoostItem::applyToWarrior(Warrior& warrior) const {
    // no effect
}

void MaxManaBoostItem::applyToTank(Tank& tank) const {
    // no effect
}

void MaxManaBoostItem::applyToMage(Mage& mage) const {
    double amount = mage.getMaxHealth() * effectValue;
    increaseMaxMana(mage, amount);
}
