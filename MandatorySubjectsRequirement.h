#pragma once
#include "Requirement.h"
#include <vector>
class MandatorySubjectsRequirement : public Requirement
{
private: 
	std::vector<Subject> subjects;
public:
	MandatorySubjectsRequirement(const std::vector<Subject>& subjects);

	bool isSatisfied(const Student& s) const override;
	std::string errorMessage(const Student& s) const override;
};