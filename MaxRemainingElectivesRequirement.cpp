#include "MaxRemainingElectivesRequirement.h"

MaxRemainingElectivesRequirement::MaxRemainingElectivesRequirement(  const std::vector<Subject>& allElectives, size_t maxRemaining): allElectives(allElectives), maxRemaining(maxRemaining)
{
}

size_t MaxRemainingElectivesRequirement::countRemaining(const Student& s) const
{
    size_t remaining = 0;
    for (const auto& elective : allElectives)
    {
        if (!s.hasPassed(elective.getName()))
            remaining++;
    }
    return remaining;
}

bool MaxRemainingElectivesRequirement::isSatisfied(const Student& s) const
{
    return countRemaining(s) <= maxRemaining;
}

std::string MaxRemainingElectivesRequirement::errorMessage(const Student& s) const
{
    size_t remaining = countRemaining(s);
    return "Student still has " + std::to_string(remaining) + " remaining elective courses left to pass.";
}
