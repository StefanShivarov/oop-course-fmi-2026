#pragma once
#include <memory>
#include <ostream>
#include "Team.h"

class Match {
private:
    static unsigned nextId;
    unsigned id;
    std::weak_ptr<Team> homeTeam;
    std::weak_ptr<Team> awayTeam;
    unsigned homeGoals = 0;
    unsigned awayGoals = 0;
    bool played = false;

public:
    Match(const std::shared_ptr<Team>& homeTeam, const std::shared_ptr<Team>& awayTeam);

    std::shared_ptr<Team> getHomeTeam() const;
    std::shared_ptr<Team> getAwayTeam() const;

    unsigned getId() const;
    unsigned getHomeGoals() const;
    unsigned getAwayGoals() const;
    bool isPlayed() const;
    void setResult(unsigned homeGoals, unsigned awayGoals);

    friend std::ostream& operator<<(std::ostream& os, const Match& match);
};
