#pragma once
#include "Sheep.h"

class SleepHelper {
private:
    Sheep* sheep = nullptr; // sheep in plural :D
    int sheepCount;
    int jumpedCount = 0;

    static constexpr int DEFAULT_SHEEP_COUNT = 50;

public:
    SleepHelper();
    explicit SleepHelper(int sheepCount);
    ~SleepHelper();

    bool markSheepAsJumped(int sheepId);

    bool isAsleep() const;
};