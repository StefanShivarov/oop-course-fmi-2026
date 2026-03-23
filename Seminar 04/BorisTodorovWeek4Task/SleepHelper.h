#pragma once
#include "Sheep.h"
class SleepHelper
{
private:
	Sheep* sheep = nullptr;
	int sheepCount;
	int jumpedCount = 0;
public:
	SleepHelper();
	SleepHelper(int count);
	~SleepHelper();
	bool markSheepAsJumped(int sheepId);
	bool isPersonAsleep() const;
};
