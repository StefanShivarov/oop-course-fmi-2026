#include "Team.h"

const std::string& Team::getName() const {
    return name;
}

Team::Team(const std::string& name): name(name) {
}

