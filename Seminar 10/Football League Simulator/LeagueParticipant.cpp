#include "LeagueParticipant.h"
#include "Team.h"
#include "Match.h"
#include <algorithm>

LeagueParticipant::LeagueParticipant(const std::shared_ptr<Team>& team)
    : team(team) {
}

const std::shared_ptr<Team>& LeagueParticipant::getTeam() const {
    return team;
}

const std::string& LeagueParticipant::getName() const {
    return team->getName();
}

const LeagueParticipant::Stats& LeagueParticipant::getStats() const {
    return stats;
}

LeagueParticipant::Stats& LeagueParticipant::getStats() {
    return stats;
}

const std::vector<std::weak_ptr<Match>>& LeagueParticipant::getMatches() const {
    return matches;
}

bool LeagueParticipant::addMatch(const std::shared_ptr<Match>& match) {
    if (!match) {
        return false;
    }

    auto it = std::ranges::find_if(matches, [&](const std::weak_ptr<Match>& current) {
        auto locked = current.lock();
        return locked && locked->getId() == match->getId();
    });

    if (it != matches.end()) {
        return false;
    }

    matches.push_back(match);
    return true;
}

std::ostream& operator<<(std::ostream& os, const LeagueParticipant& participant) {
    const auto& stats = participant.getStats();

    os << participant.getName()
       << " | GP: " << stats.gamesPlayed
       << " | W: " << stats.wins
       << " | D: " << stats.draws
       << " | L: " << stats.losses
       << " | GF: " << stats.goalsScored
       << " | GA: " << stats.goalsConceded
       << " | GD: " << ((int)(stats.goalsScored) - (int)(stats.goalsConceded))
       << " | Pts: " << stats.points;

    return os;
}