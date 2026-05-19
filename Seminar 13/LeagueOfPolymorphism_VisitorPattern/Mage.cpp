#include "Mage.h"
#include "Item.h"

Mage::Mage(const std::string& name, double maxHealth, double attackDamage, double abilityPower, double maxMana)
    : Character(name, maxHealth, attackDamage, abilityPower), mana(maxMana), maxMana(maxMana) {}

void Mage::useItem(const Item& item) {
    item.applyToMage(*this);
}

double Mage::getMana() const {
    return mana;
}

double Mage::getMaxMana() const {
    return maxMana;
}

// std::unique_ptr<Character> Mage::clone() const {
//     return std::make_unique<Mage>(*this);
// }
