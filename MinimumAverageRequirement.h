#pragma once
#include "Requirement.h"

class MinimumAverageRequirement:public Requirement
{
private:
    double minAverage;

public:
    MinimumAverageRequirement(double minAverage);

    bool isSatisfied(const Student& s) const override;

    std::string errorMessage(const Student& s) const override;
};