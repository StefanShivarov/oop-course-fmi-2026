#include "SleepHelper.h"
#include <iostream>

int main() {
    SleepHelper sleepHelper(2);
    sleepHelper.markSheepAsJumped(1);
    sleepHelper.markSheepAsJumped(2);

    std::cout << sleepHelper.isAsleep() << std::endl;
}