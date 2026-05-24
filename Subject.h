#pragma once
#include <string>
#include <vector>
#include <memory>

enum class Category { PROGRAMMING, MATHS, APPLIEDMATHS, OTHER };
class Subject
{
	std::string name;
	size_t credits;
	Category category;
	bool required;
public: 
	Subject(const std::string& name, size_t credits, Category category, bool required);
	const std::string& getName() const;
	size_t getCredits() const;
	Category getCategory() const;
	bool getRequired() const;
};