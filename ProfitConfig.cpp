#include "ProfitConfig.h"

ProfitConfig::ProfitConfig()
{
    hasFixedCost = false;
    hasPerPersonCost = false;
    hasVenueFee = false;
    hasCharity = false;
}



void ProfitConfig::setFixedCost(double value)
{
    fixedCost = value;
    hasFixedCost = true;
}

void ProfitConfig::setPerPersonCost(double value)
{
    perPersonCost = value;
    hasPerPersonCost = true;
}

void ProfitConfig::setVenueFeePercent(double value)
{
    venueFeePercent = value;
    hasVenueFee = true;
}

void ProfitConfig::setCharityAmount(double value)
{
    charityAmount = value;
    hasCharity = true;
}

bool ProfitConfig::hasFixed() const
{
    return hasFixedCost;
}

bool ProfitConfig::hasPerPerson() const
{
    return hasPerPersonCost;
}

bool ProfitConfig::hasVenue() const
{
    return hasVenueFee;
}

bool ProfitConfig::hasCharityValue() const
{
    return hasCharity;
}

double ProfitConfig::getFixedCost() const
{
    return fixedCost;
}

double ProfitConfig::getPerPersonCost() const
{
    return perPersonCost;
}

double ProfitConfig::getVenueFeePercent() const
{
    return venueFeePercent;
}

double ProfitConfig::getCharityAmount() const
{
    return charityAmount;
}
