#include "Tank.h"
#include "Item.h"

Tank::Tank(const std::string& name, double maxHealth, double attackDamage, double abilityPower)
    : Character(name, maxHealth, attackDamage, abilityPower) {}

void Tank::useItem(const Item& item) {
    item.applyToTank(*this);
}

// std::unique_ptr<Character> Tank::clone() const {
//     return std::make_unique<Tank>(*this);
// }
