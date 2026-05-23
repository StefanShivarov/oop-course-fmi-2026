#include "AbilityPowerBoostItem.h"

AbilityPowerBoostItem::AbilityPowerBoostItem(std::string name, double effectValue) : Item(name, effectValue) {}

// std::unique_ptr<Item> AbilityPowerBoostItem::clone() const {
//     return std::make_unique<AbilityPowerBoostItem>(*this);
// }

void AbilityPowerBoostItem::applyToMage(Mage& mage) const {
    double amount = mage.getAbilityPower() * effectValue * 1.5;
    increaseAbilityPower(mage, amount);
}

void AbilityPowerBoostItem::applyToTank(Tank& tank) const {
    double amount = tank.getAbilityPower() * effectValue * 0.3;
    increaseAbilityPower(tank, amount);
}

void AbilityPowerBoostItem::applyToWarrior(Warrior& warrior) const {
    double amount = warrior.getAbilityPower() * effectValue * 0.25;
    increaseAbilityPower(warrior, amount);
}
