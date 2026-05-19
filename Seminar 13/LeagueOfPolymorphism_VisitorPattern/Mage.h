#pragma once
#include "Character.h"

class Mage : public Character {
public:
    Mage(const std::string& name, double maxHealth, double attackDamage, double abilityPower, double maxMana);

    double getMana() const;
    double getMaxMana() const;

    void useItem(const Item& item) override;
    // std::unique_ptr<Character> clone() const override;

private:
    double mana;
    double maxMana;

    friend class Item;
};
