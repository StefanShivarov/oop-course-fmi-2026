#pragma once
#include "Item.h"

class DamageBoostItem : public Item {
public:
    DamageBoostItem(const std::string& name, double effectValue);

    void applyToTank(Tank& tank) const override;
    void applyToWarrior(Warrior& warrior) const override;
    void applyToMage(Mage& mage) const override;

    // std::unique_ptr<Item> clone() const override;
};
