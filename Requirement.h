#pragma once
#include "Student.h"
class Requirement
{
public:
	virtual bool isSatisfied( const Student& s) const = 0;
	virtual std::string errorMessage(const Student& s) const = 0;
};