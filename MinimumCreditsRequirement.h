#pragma once
#include "AdmissionRequiremen.h"
class MinimumCreditsRequirement: public AdmissionRequiremen
{
private:
	int minimumCredits;
public:
	MinimumCreditsRequirement(int minCredits);
	int getMinimumCredits() const;
	bool isSatisfied(const Student& student) const override;
	std::string getErrorMessage(const Student& student) const override;
};

