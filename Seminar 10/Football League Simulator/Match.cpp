#include "Match.h"
#include "Team.h"

unsigned Match::nextId = 1;

Match::Match(const std::shared_ptr<Team>& homeTeam, const std::shared_ptr<Team>& awayTeam)
    : id(nextId++), homeTeam(homeTeam), awayTeam(awayTeam) {
}

unsigned Match::getId() const {
    return id;
}

std::shared_ptr<Team> Match::getHomeTeam() const {
    return homeTeam.lock();
}

std::shared_ptr<Team> Match::getAwayTeam() const {
    return awayTeam.lock();
}

unsigned Match::getHomeGoals() const {
    return homeGoals;
}

unsigned Match::getAwayGoals() const {
    return awayGoals;
}

bool Match::isPlayed() const {
    return played;
}

void Match::setResult(unsigned homeGoals, unsigned awayGoals) {
    this->homeGoals = homeGoals;
    this->awayGoals = awayGoals;
    played = true;
}

std::ostream& operator<<(std::ostream& os, const Match& match) {
    std::shared_ptr<Team> home = match.getHomeTeam();
    std::shared_ptr<Team> away = match.getAwayTeam();

    os << "Match #" << match.id << " | ";

    if (home) {
        os << home->getName();
    } else {
        os << "<expired>";
    }

    os << " vs ";

    if (away) {
        os << away->getName();
    } else {
        os << "<expired>";
    }

    if (match.played) {
        os << " | Result: " << match.homeGoals << ":" << match.awayGoals;
    } else {
        os << " | Result: not played";
    }

    return os;
}