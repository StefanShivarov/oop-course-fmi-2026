#include "MinimumAverageRequirement.h"
#include "Exceptions.h"

MinimumAverageRequirement::MinimumAverageRequirement(double minAverage):minAverage(minAverage)
{
	if (minAverage < 2 || minAverage>6) throw ValidGrade();
}

bool MinimumAverageRequirement::isSatisfied(const Student& s) const
{
	return s.getAvg()>=minAverage;
}

std::string MinimumAverageRequirement::errorMessage(const Student& s) const
{
	return "Student has " + std::to_string(s.getAvg()) + " average grade, but the minimum grade is " + std::to_string(minAverage);
}
