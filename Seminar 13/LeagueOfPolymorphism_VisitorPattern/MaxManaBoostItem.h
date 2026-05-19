#pragma once
#include "Item.h"

class MaxManaBoostItem : public Item {
public:
    MaxManaBoostItem(std::string name, double effectValue);

    void applyToTank(Tank& tank) const override;
    void applyToMage(Mage& mage) const override;
    void applyToWarrior(Warrior& warrior) const override;

    // std::unique_ptr<Item> clone() const override;
};