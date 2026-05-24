#pragma once
#include "Requirement.h"

class MinimumCoursesFromCategoryRequirement : public Requirement
{
private:
    Category category;
    size_t minCourses;
public:
    MinimumCoursesFromCategoryRequirement(Category category, size_t minCourses);
    bool isSatisfied(const Student& s) const override;
    std::string errorMessage(const Student& s) const override;
};