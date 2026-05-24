#pragma once
#include <vector>
#include <string>

class AdmissionResult
{
private:
    bool admitted = true;
    std::vector<std::string> messages;

public:
    void addError(const std::string& error);

    bool isAdmitted() const;

    const std::vector<std::string>& getMessages() const;
};