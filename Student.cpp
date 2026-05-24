#include "Student.h"

Student::Student(const std::string& fn, const std::string& name, double grade):fn(fn), name(name), grade(grade)
{
}

const std::string& Student::getFn() const
{
	return fn;

}
const std::string& Student::getName() const
{
	return name;
}
size_t Student::getCredits() const
{
	size_t total=0;
	for (const auto& s : subjects)
	{
		total += s.getCredits();
	}
	return total;
}

double Student::getAvg() const
{
	return grade;
}

const std::vector<Subject>& Student::getSubjects() const
{
	return subjects;
}

bool Student::hasPassed(const std::string& subjectName) const
{
	for (const auto& s:subjects)
	{
		if (subjectName == s.getName()) return true;
	}
	return false;
}
void Student::addSubject(const Subject& subject)
{
	subjects.push_back(subject);
}