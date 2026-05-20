#pragma once
#include "Student.h"
class AdmissionRequiremen
{
public:
	virtual bool isSatisfied(const Student& student) const = 0;
	virtual std::string getErrorMessage(const Student& student) const = 0;
	virtual ~AdmissionRequiremen() = default;
};

