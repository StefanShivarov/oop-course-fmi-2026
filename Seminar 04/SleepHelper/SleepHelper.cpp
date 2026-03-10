#include "SleepHelper.h"

SleepHelper::SleepHelper() : SleepHelper(DEFAULT_SHEEP_COUNT) {}

SleepHelper::SleepHelper(int sheepCount) : sheepCount(sheepCount) {
    sheep = new Sheep[sheepCount];
}

SleepHelper::~SleepHelper() {
    delete[] sheep;
    sheep = nullptr;
    sheepCount = 0;
    jumpedCount = 0;
}

bool SleepHelper::markSheepAsJumped(int sheepId) {
    if (sheepId > sheepCount) {
        return false;
    }
    if (sheep[sheepId - 1].jump()) {
        jumpedCount++;
        return true;
    }
    return false;
}

bool SleepHelper::isAsleep() const {
    return jumpedCount == sheepCount;
}
