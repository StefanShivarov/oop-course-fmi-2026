#include "ProfitConfigBuilder.h"


ProfitConfigBuilder& ProfitConfigBuilder::withFixedCost(double value)
{
    config.setFixedCost(value);
    return *this;
}



ProfitConfigBuilder& ProfitConfigBuilder::withPerPersonCost(double value)
{
    config.setPerPersonCost(value);
    return *this;
}

ProfitConfigBuilder& ProfitConfigBuilder::withVenueFeePercent(double value)
{ config.setVenueFeePercent(value);
    return *this;
}

ProfitConfigBuilder& ProfitConfigBuilder::withCharityAmount(double value)
{
    config.setCharityAmount(value);
    return *this;
}


ProfitConfig ProfitConfigBuilder::build() const
{return config;
}
