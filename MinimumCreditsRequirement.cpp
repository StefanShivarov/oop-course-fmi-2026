#include "MinimumCreditsRequirement.h"

MinimumCreditsRequirement::MinimumCreditsRequirement(int minCredits) : minimumCredits(minCredits)
{
}

int MinimumCreditsRequirement::getMinimumCredits() const
{
    return minimumCredits;
}

bool MinimumCreditsRequirement::isSatisfied(const Student& student) const
{
	return student.getTotalCredits() >= minimumCredits;
}

std::string MinimumCreditsRequirement::getErrorMessage(const Student& student) const
{
    return "Student has " +
        std::to_string(student.getTotalCredits()) +
        " credits, but at least " +
        std::to_string(minimumCredits) +
        " are required.";
}
