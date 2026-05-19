#pragma once
#include "ProfitConfig.h"

class ProfitConfigBuilder
{
private:
    ProfitConfig config;

public:
    ProfitConfigBuilder& withFixedCost(double value);
    ProfitConfigBuilder& withPerPersonCost(double value);
    ProfitConfigBuilder& withVenueFeePercent(double value);
    ProfitConfigBuilder& withCharityAmount(double value);

    ProfitConfig build() const;
};

