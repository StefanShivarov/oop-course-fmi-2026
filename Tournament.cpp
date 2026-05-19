#include "Tournament.h"
void Tournament::addPlayer(Player* player) {
    players.push_back(player);
}

Player* Tournament::getWinner() const {
    if (players.empty()) {
        return nullptr;
    }
    int bestScore = -9999999;
    Player* winner = nullptr;
    for (int i = 0; i < players.size(); i++) {
        int currentScore = 0;
        for (int j = 0; j < players.size(); j++) {
            if (i == j) {
                continue;
            }
            currentScore += players[i]->play(*players[j]);
        }
        if (currentScore > bestScore) {
            bestScore = currentScore;
            winner = players[i];
        }
    }
    return winner;
}
