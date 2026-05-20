#pragma once
#include <string>
enum class CourseType {
	Programming,
	Mathematics,
	AppliedMathematics,
	Other
};
class Course
{
private:
	std::string name;
	int credits;
	CourseType type;
	bool status;
public:
	Course(const std::string& n, int c, CourseType t, bool s);

	std::string getName() const;
	int getCredits() const;
	CourseType getType() const;
	bool getStatus() const;
};

