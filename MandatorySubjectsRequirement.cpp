#include "MandatorySubjectsRequirement.h"
#include <algorithm>
#include <iostream>
#include <vector>
MandatorySubjectsRequirement::MandatorySubjectsRequirement(const std::vector<Subject>& subjects) :subjects(subjects) 
{
}

bool MandatorySubjectsRequirement::isSatisfied(const Student& s) const
{
	for (const auto& sub : subjects)
	{
		if (sub.getRequired() && s.hasPassed(sub.getName()))
		{
			return false;
		}
	}
	return true;
}

std::string MandatorySubjectsRequirement::errorMessage(const Student& s) const
{
	std::string result;
	for (const auto& sub : subjects)
	{
		if (sub.getRequired() && !s.hasPassed(sub.getName()))
		{
			result += "Mandatory course not passed: " + sub.getName() + ".\n";
		}
	}
	return result;
}
