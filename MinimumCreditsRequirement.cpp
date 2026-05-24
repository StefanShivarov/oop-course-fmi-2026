#include "MinimumCreditsRequirement.h"

MinimumCreditsRequirement::MinimumCreditsRequirement(size_t minCredits) :minCredits(minCredits)

{
}

bool MinimumCreditsRequirement::isSatisfied(const Student& s) const
{
	return s.getCredits() >= minCredits;
}

std::string MinimumCreditsRequirement::errorMessage(const Student& s) const
{
	return "Student has " + std::to_string(s.getCredits()) + " credits, but at least " + std::to_string(minCredits) + " are required.";
}
