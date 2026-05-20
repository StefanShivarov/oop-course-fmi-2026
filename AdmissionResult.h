#pragma once
#include <string>
#include <vector>
#include <string>
class AdmissionResult
{
private:
	bool admitted;
	std::vector<std::string> messages;
public:
	AdmissionResult();
	void addmessage(const std::string& msg);
	bool isAdmitted() const;
	const std::vector<std::string>& getMessages() const;

};

