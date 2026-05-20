#include "AdmissionResult.h"

AdmissionResult::AdmissionResult()
    :admitted(true)
{
}

void AdmissionResult::addmessage(const std::string& msg)
{
    admitted = false;
    messages.push_back(msg);
}

bool AdmissionResult::isAdmitted() const
{
    return admitted;
}

const std::vector<std::string>& AdmissionResult::getMessages() const
{
	return messages;
}
