#include "Egg.h"

Egg::Egg(std::string name, double health, double attackDamage, double armor,
         double criticalStrike) : name(std::move(name)), health(health), attackDamage(attackDamage), armor(armor),
                                  criticalStrike(criticalStrike) {
}

std::string Egg::getName() const {
    return name;
}

double Egg::getHealth() const {
    return health;
}

double Egg::getAttackDamage() const {
    return attackDamage;
}

double Egg::getArmor() const {
    return armor;
}

double Egg::getCriticalStrike() const {
    return criticalStrike;
}

void Egg::takeDamage(double damage) {
    if (damage > armor) {
        double remaining = damage - armor;
        armor = 0;
        health -= remaining;
    }
    else {
        armor -= damage;
    }
}

bool Egg::isThirdFight() const {
    return fightCount % 3 == 0;
}

void Egg::updateFightCount() {
    fightCount++;
}
