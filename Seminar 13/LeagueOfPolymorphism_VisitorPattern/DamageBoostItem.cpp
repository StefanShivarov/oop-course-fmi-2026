#include "DamageBoostItem.h"

DamageBoostItem::DamageBoostItem(const std::string& name, double effectValue) : Item(name, effectValue) {}

// std::unique_ptr<Item> DamageBoostItem::clone() const {
//     return std::make_unique<DamageBoostItem>(*this);
// }

void DamageBoostItem::applyToTank(Tank& tank) const {
    double amount = tank.getAttackDamage() * effectValue * 0.8;
    increaseAttackDamage(tank, amount);
}

void DamageBoostItem::applyToWarrior(Warrior& warrior) const {
    double amount = warrior.getAttackDamage() * effectValue * 1.5;
    increaseAttackDamage(warrior, amount);
}

void DamageBoostItem::applyToMage(Mage& mage) const {
    double amount = mage.getAttackDamage() * effectValue * 0.5;
    increaseAttackDamage(mage, amount);
}
