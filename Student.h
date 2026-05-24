#pragma once
#include "Subject.h"
#include <string>
#include <vector>
#include <memory>

class Student
{
private:
	std::string fn;
	std::string name;
	std::vector<Subject> subjects;
	double grade;

public:
	Student(const std::string& fn, const std::string& name, double grade);
	const std::string& getFn() const;
	const std::string& getName()const;
	size_t getCredits()const;
	double getAvg() const;
	const std::vector<Subject>& getSubjects() const;
	bool hasPassed(const std::string& subjectName) const;
	void addSubject(const Subject& subject);

};