#pragma once
#include <memory>
#include <vector>
#include "Match.h"
#include "Team.h"
#include <ostream>

class LeagueParticipant {
public:
    struct Stats {
        unsigned gamesPlayed = 0;
        unsigned wins = 0;
        unsigned draws = 0;
        unsigned losses = 0;
        unsigned goalsScored = 0;
        unsigned goalsConceded = 0;
        unsigned points = 0;
    };
private:
    std::shared_ptr<Team> team;
    Stats stats;
    std::vector<std::weak_ptr<Match>> matches;

public:
    explicit LeagueParticipant(const std::shared_ptr<Team>& team);

    const std::shared_ptr<Team>& getTeam() const;
    const std::string& getName() const;

    const Stats& getStats() const;
    Stats& getStats();

    const std::vector<std::weak_ptr<Match>>& getMatches() const;
    bool addMatch(const std::shared_ptr<Match>& match);

    friend std::ostream& operator<<(std::ostream& os, const LeagueParticipant& participant);
};
