#include "Course.h"
#include <string>

Course::Course(const std::string& n, int c, CourseType t, bool s)
	:name(n), credits(c), type(t), status(s)
{
}

std::string Course::getName() const
{
    return name;
}

int Course::getCredits() const
{
    return credits;
}

CourseType Course::getType() const
{
    return type;
}

bool Course::getStatus() const
{
    return status;
}
