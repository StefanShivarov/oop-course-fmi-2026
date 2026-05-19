#pragma once
#include "Item.h"

class MaxHealthBoostItem : public Item
{
public:
    MaxHealthBoostItem(std::string name, double effectValue);

    void applyToTank(Tank& tank) const override;
    void applyToMage(Mage& mage) const override;
    void applyToWarrior(Warrior& warrior) const override;

    // std::unique_ptr<Item> clone() const override;
};