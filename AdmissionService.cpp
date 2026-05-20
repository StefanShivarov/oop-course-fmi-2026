#include "AdmissionService.h"

void AdmissionService::addRequirement(std::shared_ptr<AdmissionRequiremen> requirement)
{
    requirements.push_back(requirement);
}

AdmissionResult AdmissionService::checkAdmission(const Student& student) const
{
    AdmissionResult result;
    for (const auto& requirement : requirements)
    {
        if (!requirement->isSatisfied(student))
        {
            result.addmessage(
                requirement->getErrorMessage(student)
            );
        }
    }

    return result;
}
