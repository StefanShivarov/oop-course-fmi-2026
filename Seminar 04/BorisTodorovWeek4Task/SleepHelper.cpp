#include <iostream>
#include "SleepHelper.h"
SleepHelper::SleepHelper() :SleepHelper(50) {}
SleepHelper::SleepHelper(int count)
{
	sheepCount = count;
	sheep = new Sheep[sheepCount];
}
SleepHelper::~SleepHelper()
{
	delete[] sheep;
	sheep = nullptr;
}
bool SleepHelper::markSheepAsJumped(int sheepId)
{
	if (sheepId > sheepCount) 
	{
		return false;
	}
	if (sheep[sheepId - 1].jump())
	{
		++jumpedCount;
		return true;
	}
	return false;
}
bool SleepHelper::isPersonAsleep() const
{
	return sheepCount == jumpedCount;
}