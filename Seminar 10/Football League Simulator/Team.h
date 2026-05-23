#pragma once
#include <string>

class Team {
private:
    std::string name;
    // ...
public:
    explicit Team(const std::string& name);
    const std::string& getName() const;
};
