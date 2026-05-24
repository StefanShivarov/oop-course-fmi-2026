#pragma once
#include "Player.h"
#include "Paper.h"
#include "Scissors.h"
#include "Rock.h"
#include <vector>
#include <memory>

class RPSTournament {
private:
    std::vector<std::unique_ptr<Player>> players;
public:
    void addPlayer(std::unique_ptr<Player> p);
    std::unique_ptr<Player> run();
    
};