#pragma once
#pragma once
#include "Requirement.h"
#include <vector>

class MaxRemainingElectivesRequirement : public Requirement
{
private:
    std::vector<Subject> allElectives;
    size_t maxRemaining;
    size_t countRemaining(const Student& s) const;
public:
    MaxRemainingElectivesRequirement(const std::vector<Subject>& allElectives, size_t maxRemaining);
    bool isSatisfied(const Student& s) const override;
    std::string errorMessage(const Student& s) const override;
   
};