#include "Warrior.h"
#include "Item.h"

Warrior::Warrior(const std::string& name, double maxHealth, double attackDamage, double abilityPower)
    : Character(name, maxHealth, attackDamage, abilityPower) {}

void Warrior::useItem(const Item& item) {
    item.applyToWarrior(*this);
}

// std::unique_ptr<Character> Warrior::clone() const {
//     return std::make_unique<Warrior>(*this);
// }
