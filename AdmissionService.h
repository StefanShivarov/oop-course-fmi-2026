#pragma once
#include <memory>
#include <vector>
#include "AdmissionRequiremen.h"
#include "AdmissionResult.h"

class AdmissionService
{
private:
    std::vector<std::shared_ptr<AdmissionRequiremen>> requirements;
public:
    void addRequirement(
        std::shared_ptr<AdmissionRequiremen>
        requirement
    );

    AdmissionResult checkAdmission(
        const Student& student) const;
};

