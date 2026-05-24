#pragma once
#include "Requirement.h"

class MinimumCreditsRequirement :public Requirement
{
private:
	size_t minCredits;
public:
	MinimumCreditsRequirement(size_t minCredits);
	bool isSatisfied(const Student& s) const override;
	std::string errorMessage(const Student& s)const override;

};