#include "Subject.h"

Subject::Subject(const std::string& name, size_t credits, Category category, bool required):name(name), credits(credits), category(category), required(required)
{
}






const std::string& Subject::getName() const
{
	return name;
}

size_t Subject::getCredits() const
{
	return credits;
}

Category Subject::getCategory() const
{
	return category;
}

bool Subject::getRequired() const
{
	return required;
}
