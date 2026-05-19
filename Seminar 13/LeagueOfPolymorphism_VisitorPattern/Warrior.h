#pragma once
#include "Character.h"

class Warrior : public Character {
public:
    Warrior(const std::string& name, double maxHealth, double attackDamage, double abilityPower);
    void useItem(const Item& item) override;
    // std::unique_ptr<Character> clone() const override;
};
