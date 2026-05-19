#pragma once
#include "Character.h"

class Tank : public Character {
public:
    Tank(const std::string& name, double maxHealth, double attackDamage, double abilityPower);
    void useItem(const Item& item) override;
    // std::unique_ptr<Character> clone() const override;
};
