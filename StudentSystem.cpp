#include "StudentSystem.h"
#include "Exceptions.h"
#include <vector>
#include <algorithm>

StudentSystem::StudentSystem(std::shared_ptr<AdmissionService> admission):admission(admission)
{
}

void StudentSystem::addStudent(const Student& s)
{
	for (const auto& student : students)
	{
		if (student.getFn() == s.getFn())
		{
			throw StudentAlreadyExists();
		}
	}
	students.push_back(s);
}

void StudentSystem::removeStudent(const std::string& fn)
{
	for (auto it = students.begin(); it != students.end(); ++it)
	{
		if (it->getFn() == fn)
		{
			students.erase(it);
			return;
		}
	}
	throw StudentNotFound();
}

Student& StudentSystem::operator[](const std::string& fn)
{
	for ( auto& s : students)
	{
		if (s.getFn() == fn) return s;
	}
	throw StudentNotFound();
}

AdmissionResult StudentSystem::checkStudent(const std::string& fn) const
{
	for (const auto& s : students)
	{
		if (s.getFn() == fn)
		{
			return admission->checkResult(s);
		}
	}
	throw StudentNotFound();
}
