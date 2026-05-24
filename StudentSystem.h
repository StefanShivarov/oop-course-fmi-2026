#pragma once
#include "Student.h"
#include "AdmissionService.h"
#include <vector>

class StudentSystem
{
private:
	std::vector<Student> students;
std::shared_ptr<AdmissionService> admission; 
public:
	StudentSystem(std::shared_ptr<AdmissionService> admission);
	void addStudent(const Student& s);
	void removeStudent(const std::string& fn);
	Student& operator[](const std::string& fn);
	AdmissionResult checkStudent(const std::string& fn) const;
};
