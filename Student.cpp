#include "Student.h"

bool Student::hasPassedCourse(const std::string& courseName) const
{
    for (const Course& course : passedCourses)
    {
        if (course.getName() == courseName)
        {
            return true;
        }
    }
    return false;
}

Student::Student(const std::string& fNumber, const std::string& n, double avrGrade)
	:facultyNumber(fNumber), name(n), averageGrade(avrGrade)
{
}

void Student::addCourse(const Course& course)
{
    passedCourses.push_back(course);
}

std::string Student::getFacultyNumber() const
{
    return facultyNumber;
}

std::string Student::getName() const
{
    return name;
}

const std::vector<Course>& Student::getPassedCourses() const
{
    return passedCourses;
}

int Student::getTotalCredits() const
{
    int totalC = 0;
    for (const Course& course:passedCourses)
    {
        totalC += course.getCredits();
    }
    return totalC;
}

double Student::getAverageGrade() const
{
    return averageGrade;
}
