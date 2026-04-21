#define _CRT_SECURE_NO_WARNINGS
#include "ProfitCalculator.h"

double calculateProfit(const Registry& registry, double fixedCost, double costPerPerson,
    double venueFeePercent, double charityAmount)
{
    double revenue = registry.calculate();
    return revenue - fixedCost  - (venueFeePercent * revenue)  - (costPerPerson * (double)registry.getTaken())- charityAmount;
}