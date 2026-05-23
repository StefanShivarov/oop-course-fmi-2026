#include "League.h"

#include <algorithm>
#include <ostream>

namespace {
    int getGoalDifference(const LeagueParticipant::Stats& stats) {
        return (int) stats.goalsScored - (int) stats.goalsConceded;
    }
}

League::League(const std::string& name): name(name) {
}

const std::string& League::getName() const {
    return name;
}

LeagueParticipant* League::findParticipantByName(const std::string& teamName) {
    auto it = std::find_if(participants.begin(), participants.end(),
        [&](const std::unique_ptr<LeagueParticipant>& participant) {
            return participant->getName() == teamName;
        });

    return it == participants.end() ? nullptr : it->get();
}

const LeagueParticipant* League::findParticipantByName(const std::string& teamName) const {
    auto it = std::find_if(participants.begin(), participants.end(),
        [&](const std::unique_ptr<LeagueParticipant>& participant) {
            return participant->getName() == teamName;
        });

    return it == participants.end() ? nullptr : it->get();
}

std::shared_ptr<Match> League::findMatchById(unsigned matchId) {
    auto it = std::find_if(matches.begin(), matches.end(),
        [&](const std::shared_ptr<Match>& match) {
            return match && match->getId() == matchId;
        });

    return it == matches.end() ? nullptr : *it;
}

std::shared_ptr<const Match> League::findMatchById(unsigned matchId) const {
    auto it = std::find_if(matches.begin(), matches.end(),
        [&](const std::shared_ptr<Match>& match) {
            return match && match->getId() == matchId;
        });

    return it == matches.end() ? nullptr : *it;
}

bool League::addParticipant(const std::shared_ptr<Team>& team) {
    if (!team || containsParticipant(team->getName())) {
        return false;
    }

    participants.push_back(std::make_unique<LeagueParticipant>(team));
    return true;
}

bool League::removeParticipant(const std::string& teamName) {
    LeagueParticipant* participant = findParticipantByName(teamName);
    if (!participant) {
        return false;
    }

    std::erase_if(matches, [&](const std::shared_ptr<Match>& match) {
        if (!match) {
            return true;
        }

        auto homeTeam = match->getHomeTeam();
        auto awayTeam = match->getAwayTeam();

        return (homeTeam && homeTeam->getName() == teamName) || (awayTeam && awayTeam->getName() == teamName);
    });

    std::erase_if(participants, [&](const std::unique_ptr<LeagueParticipant>& current) {
        return current->getName() == teamName;
    });

    return true;
}

bool League::containsParticipant(const std::string& teamName) const {
    return findParticipantByName(teamName) != nullptr;
}

LeagueParticipant* League::operator[](const std::string& teamName) {
    return findParticipantByName(teamName);
}

const LeagueParticipant* League::operator[](const std::string& teamName) const {
    return findParticipantByName(teamName);
}

bool League::addMatch(const std::string& homeTeamName, const std::string& awayTeamName) {
    if (homeTeamName == awayTeamName) {
        return false;
    }

    LeagueParticipant* homeParticipant = findParticipantByName(homeTeamName);
    LeagueParticipant* awayParticipant = findParticipantByName(awayTeamName);

    if (!homeParticipant || !awayParticipant) {
        return false;
    }

    std::shared_ptr<Match> match = std::make_shared<Match>(homeParticipant->getTeam(), awayParticipant->getTeam());

    if (!homeParticipant->addMatch(match)) {
        return false;
    }

    if (!awayParticipant->addMatch(match)) {
        return false;
    }

    matches.push_back(match);
    return true;
}

bool League::addMatch(const std::string& homeTeamName, const std::string& awayTeamName,
                      unsigned homeGoals, unsigned awayGoals) {
    if (!addMatch(homeTeamName, awayTeamName)) {
        return false;
    }

    return setMatchResult(matches.back()->getId(), homeGoals, awayGoals);
}

bool League::setMatchResult(unsigned matchId, unsigned homeGoals, unsigned awayGoals) {
    std::shared_ptr<Match> match = findMatchById(matchId);
    if (!match || match->isPlayed()) {
        return false;
    }

    std::shared_ptr<Team> homeTeam = match->getHomeTeam();
    std::shared_ptr<Team> awayTeam = match->getAwayTeam();

    if (!homeTeam || !awayTeam) {
        return false;
    }

    LeagueParticipant* homeParticipant = findParticipantByName(homeTeam->getName());
    LeagueParticipant* awayParticipant = findParticipantByName(awayTeam->getName());

    if (!homeParticipant || !awayParticipant) {
        return false;
    }

    match->setResult(homeGoals, awayGoals);

    auto& homeStats = homeParticipant->getStats();
    auto& awayStats = awayParticipant->getStats();

    homeStats.gamesPlayed++;
    awayStats.gamesPlayed++;

    homeStats.goalsScored += homeGoals;
    homeStats.goalsConceded += awayGoals;

    awayStats.goalsScored += awayGoals;
    awayStats.goalsConceded += homeGoals;

    if (homeGoals > awayGoals) {
        homeStats.wins++;
        awayStats.losses++;
        homeStats.points += 3;
    } else if (homeGoals < awayGoals) {
        awayStats.wins++;
        homeStats.losses++;
        awayStats.points += 3;
    } else {
        homeStats.draws++;
        awayStats.draws++;
        homeStats.points += 1;
        awayStats.points += 1;
    }

    return true;
}

std::vector<std::shared_ptr<Match>> League::getMatchesForTeam(const std::string& teamName) const {
    std::vector<std::shared_ptr<Match>> result;
    const LeagueParticipant* participant = findParticipantByName(teamName);
    if (!participant) {
        return result;
    }

    const auto& teamMatches = participant->getMatches();
    result.reserve(teamMatches.size());

    for (const std::weak_ptr<Match>& weakMatch : teamMatches) {
        std::shared_ptr<Match> match = weakMatch.lock();
        if (match) {
            result.push_back(match);
        }
    }

    return result;
}

std::size_t League::getPlayedMatchesCountForTeam(const std::string& teamName) const {
    auto teamMatches = getMatchesForTeam(teamName);

    return std::count_if(teamMatches.begin(), teamMatches.end(), [](const std::shared_ptr<Match>& match) {
        return match && match->isPlayed();
    });
}

std::vector<const LeagueParticipant*> League::getTable() const {
    std::vector<const LeagueParticipant*> table;
    table.reserve(participants.size());

    for (const auto& participant : participants) {
        table.push_back(participant.get());
    }

    std::sort(table.begin(), table.end(),
        [](const LeagueParticipant* lhs, const LeagueParticipant* rhs) {
            const auto& a = lhs->getStats();
            const auto& b = rhs->getStats();

            if (a.points != b.points) {
                return a.points > b.points;
            }

            int gdA = getGoalDifference(a);
            int gdB = getGoalDifference(b);

            if (gdA != gdB) {
                return gdA > gdB;
            }

            if (a.goalsScored != b.goalsScored) {
                return a.goalsScored > b.goalsScored;
            }

            return lhs->getName() < rhs->getName();
        });

    return table;
}

const LeagueParticipant* League::getLeader() const {
    auto table = getTable();
    return table.empty() ? nullptr : table.front();
}

std::size_t League::getParticipantsCount() const {
    return participants.size();
}

std::size_t League::getTotalMatchesCount() const {
    return matches.size();
}

std::ostream& operator<<(std::ostream& os, const League& league) {
    os << "League: " << league.name << '\n';
    os << "Participants: " << league.getParticipantsCount() << '\n';
    os << "Matches: " << league.getTotalMatchesCount() << '\n';

    os << "\nTable:\n";
    auto table = league.getTable();

    if (table.empty()) {
        os << "<empty>\n";
    } else {
        std::size_t position = 1;
        for (const LeagueParticipant* participant : table) {
            os << position << ". " << *participant << '\n';
            position++;
        }
    }

    os << "\nMatches:\n";
    if (league.matches.empty()) {
        os << "<empty>\n";
    } else {
        for (const auto& match : league.matches) {
            os << *match << '\n';
        }
    }

    return os;
}
