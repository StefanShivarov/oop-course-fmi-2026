#pragma once
#include <string>
#include <memory>
#include <vector>
#include "LeagueParticipant.h"
#include "Match.h"

class League {
private:
    std::string name;
    std::vector<std::unique_ptr<LeagueParticipant>> participants;
    std::vector<std::shared_ptr<Match>> matches;

    // Raw pointers are used here only as non-owning internal lookup results.
    // Ownership remains inside the unique_ptr containers.
    LeagueParticipant* findParticipantByName(const std::string& teamName);
    const LeagueParticipant* findParticipantByName(const std::string& teamName) const;

    std::shared_ptr<Match> findMatchById(unsigned matchId);
    std::shared_ptr<const Match> findMatchById(unsigned matchId) const;

public:
    explicit League(const std::string& name);

    const std::string& getName() const;

    bool addParticipant(const std::shared_ptr<Team>& team);
    bool removeParticipant(const std::string& teamName);
    bool containsParticipant(const std::string& teamName) const;

    // A raw pointer is returned here as a non-owning view to an existing participant.
    // Since we have them as unique_ptrs in the vectors, it is better to return them as non-owning raw ptrs.
    LeagueParticipant* operator[](const std::string& teamName);
    const LeagueParticipant* operator[](const std::string& teamName) const;

    bool addMatch(const std::string& homeTeamName, const std::string& awayTeamName);
    bool addMatch(const std::string& homeTeamName, const std::string& awayTeamName, unsigned homeGoals, unsigned awayGoals);
    bool setMatchResult(unsigned matchId, unsigned homeGoals, unsigned awayGoals);

    std::vector<std::shared_ptr<Match>> getMatchesForTeam(const std::string& teamName) const;
    size_t getPlayedMatchesCountForTeam(const std::string& teamName) const;

    // The table contains non-owning pointers to participants already owned by the league.
    std::vector<const LeagueParticipant*> getTable() const;
    const LeagueParticipant* getLeader() const;

    size_t getParticipantsCount() const;
    size_t getTotalMatchesCount() const;

    friend std::ostream& operator<<(std::ostream& os, const League& league);
};