#include "Item.h"

Item::Item(const std::string& name, double effectValue) : name(name), effectValue(effectValue) {}

const std::string& Item::getName() const {
    return name;
}

double Item::getEffectValue() const {
    return effectValue;
}

void Item::heal(Character& character, double amount) {
    character.health = std::min(character.health + amount, character.maxHealth);
}

void Item::restoreMana(Mage& mage, double amount) {
    mage.mana = std::min(mage.mana + amount, mage.maxMana);
}

void Item::increaseMaxHealth(Character& character, double amount) {
    character.health += amount;
    character.maxHealth += amount;
}

void Item::increaseMaxMana(Mage& mage, double amount) {
    mage.mana += amount;
    mage.maxMana += amount;
}

void Item::increaseAbilityPower(Character& character, double amount) {
    character.abilityPower += amount;
}

void Item::increaseAttackDamage(Character& character, double amount) {
    character.attackDamage += amount;
}
