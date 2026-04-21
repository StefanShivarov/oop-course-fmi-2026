#pragma once
#include "Registry.h"

double calculateProfit(const Registry& registry, double fixedCost = 0, double costPerPerson = 0,
    double venueFeePercent = 0,  double charityAmount = 0);