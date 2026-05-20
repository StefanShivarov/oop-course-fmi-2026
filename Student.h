#pragma once
#include <string>
#include <vector>
#include "Course.h"
class Student
{
private:
	std::string facultyNumber;
	std::string name;
	std::vector<Course> passedCourses;
	double averageGrade;
public:
	Student(const std::string& fNumber, const std::string& n, double avrGrade);
	void addCourse(const Course& course);
	std::string getFacultyNumber() const;
	std::string getName() const;
	const std::vector<Course>& getPassedCourses() const;
	int getTotalCredits() const;
	double getAverageGrade() const;
	bool hasPassedCourse(const std::string& courseName) const;
};

