#include "AdmissionResult.h"

void AdmissionResult::addError(const std::string& error)
{
	admitted = false;
	messages.push_back(error);
}

bool AdmissionResult::isAdmitted() const
{
	return admitted;
}

const std::vector<std::string>& AdmissionResult::getMessages() const
{
	return messages;
}
