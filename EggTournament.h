#pragma once
#include"Egg.h"
#include<iostream>
#include<queue>
#include<vector>
#include<optional>

using std::queue;
using std::vector;
using std::optional;

class EggTournament
{
private:
	optional<Egg> currentFighter;
	queue<Egg> opponents;
   
public:
	void addEgg(const Egg& egg);
	void addEggs(const vector<Egg>& eggs);

	bool hasNextBattle()const;
	void playNextBattle();

	const optional<Egg>& getCurrentFighter()const;
};

