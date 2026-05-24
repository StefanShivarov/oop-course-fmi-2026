#pragma once
#include <stdexcept>
#include <string>

class StudentAlreadyExists : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Student already exists.";
	}
};

class StudentNotFound : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Student not found.";
	}
};
class ValidGrade : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Grade not valid (must be between 2 and 6)";
	}

};