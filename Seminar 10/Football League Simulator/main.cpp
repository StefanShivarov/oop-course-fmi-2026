#include <iostream>
#include <memory>
#include "League.h"
#include "Team.h"

int main() {
    League league("Premier League");

    auto liverpool = std::make_shared<Team>("Liverpool");
    auto arsenal = std::make_shared<Team>("Arsenal");
    auto chelsea = std::make_shared<Team>("Chelsea");
    auto united = std::make_shared<Team>("Manchester United");

    league.addParticipant(liverpool);
    league.addParticipant(arsenal);
    league.addParticipant(chelsea);
    league.addParticipant(united);

    league.addMatch("Liverpool", "Arsenal", 2, 1);            // Match #1
    league.addMatch("Chelsea", "Manchester United", 0, 2);    // Match #2
    league.addMatch("Liverpool", "Chelsea", 1, 1);            // Match #3
    league.addMatch("Arsenal", "Manchester United", 1, 2);    // Match #4
    league.addMatch("Manchester United", "Liverpool", 4, 3);  // Match #5
    league.addMatch("Arsenal", "Chelsea", 2, 0);              // Match #6
    league.addMatch("Arsenal", "Liverpool", 1, 0);

    std::cout << league << '\n';

    if (const LeagueParticipant* unitedParticipant = league["Chelsea"]) {
        std::cout << "Chelsea stats:\n";
        std::cout << *unitedParticipant << '\n';

        std::cout << "\nPlayed matches for Chelsea: "
                  << league.getPlayedMatchesCountForTeam("Chelsea")
                  << '\n';

        std::cout << "\nMatches for Chelsea:\n";
        auto unitedMatches = league.getMatchesForTeam("Chelsea");
        for (const auto& match : unitedMatches) {
            std::cout << *match << '\n';
        }
    }

    if (const LeagueParticipant* leader = league.getLeader()) {
        std::cout << "\nLeader: " << leader->getName() << '\n';
    }
}
