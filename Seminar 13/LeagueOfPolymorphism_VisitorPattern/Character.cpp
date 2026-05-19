#include "Character.h"

Character::Character(const std::string& name, double maxHealth, double attackDamage, double abilityPower)
    : name(name), health(maxHealth), maxHealth(maxHealth), attackDamage(attackDamage), abilityPower(abilityPower) {}

const std::string& Character::getName() const {
    return name;
}

double Character::getMaxHealth() const {
    return maxHealth;
}

double Character::getHealth() const {
    return health;
}

double Character::getAttackDamage() const {
    return attackDamage;
}

double Character::getAbilityPower() const {
    return abilityPower;
}
