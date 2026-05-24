#include "AdmissionService.h"

void AdmissionService::addRequirement(std::shared_ptr<Requirement> requirement)
{
	requirements.push_back(requirement);
}

AdmissionResult AdmissionService::checkResult(const Student& s) const
{
	AdmissionResult result;
	for (const auto& r : requirements)
	{
		if (!r->isSatisfied(s))
		{
			result.addError(r->errorMessage(s));
		}
	}
	return result;
}
