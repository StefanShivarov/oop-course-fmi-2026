#include "MinimumCoursesFromCategoryRequirement.h"

MinimumCoursesFromCategoryRequirement::MinimumCoursesFromCategoryRequirement(Category category, size_t minCourses):category(category), minCourses(minCourses)
{
}

bool MinimumCoursesFromCategoryRequirement::isSatisfied(const Student& s) const
{
    size_t count = 0;
    for (const auto& sub : s.getSubjects())
    {
        if (sub.getCategory() == category)
            count++;
    }
    return count >= minCourses;
}

std::string MinimumCoursesFromCategoryRequirement::errorMessage(const Student& s) const
{
    size_t count = 0;
    for (const auto& sub: s.getSubjects())
    {
        if (sub.getCategory() == category)
            count++;
    }

    std::string categoryName;
    switch (category)
    {
    case Category::PROGRAMMING: categoryName = "Programming"; break;
    case Category::MATHS: categoryName = "Maths"; break;
    case Category::APPLIEDMATHS: categoryName = "Applied Maths"; break;
    case Category::OTHER: categoryName = "Other"; break;
    }

    return "Student has completed " + std::to_string(count) + " " + categoryName + " courses, but at least "
        + std::to_string(minCourses) + " are required.";
}
