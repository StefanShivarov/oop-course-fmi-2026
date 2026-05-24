#pragma once
#include "Requirement.h"
#include "AdmissionResult.h"
#include <memory>

class AdmissionService
{
private:
	std::vector<std::shared_ptr<Requirement>> requirements;
public:
	void addRequirement(std::shared_ptr<Requirement> requirement);
	AdmissionResult checkResult(const Student& s) const;

};