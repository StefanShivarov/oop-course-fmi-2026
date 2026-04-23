#include "ProfitCalculator.h"

void ProfitCalculator::setFixedCost(double val)
{
    fixedCost = val;
    hasFixedCost = true;
}

void ProfitCalculator::setCostPerUser(double val)
{
    costPerUser = val;
    hasCostPerUser = true;
}

void ProfitCalculator::setPercentage(double val)
{
    percentage = val;
    hasPercentage = true;
}

double ProfitCalculator::calculate(double revenue, int users) const
{
    double result = revenue;

    if (hasFixedCost) result -= fixedCost;
    if (hasPercentage) result -= (percentage * revenue);
    if (hasCostPerUser) result -= (costPerUser * users);

    return result;
}