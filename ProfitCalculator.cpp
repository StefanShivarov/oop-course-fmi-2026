#include "ProfitCalculator.h"

ProfitCalculator::ProfitCalculator(bool useFixedCost, double fixedCost, bool useCostPerUser,
    double costPerUser, bool usePercentFee, double percentFee, bool useCharity,
    double charity) :useFixedCost(useFixedCost), useCostPerUser(useCostPerUser),
    usePercentFee(usePercentFee), useCharity(useCharity)
{
    setFixedCost(fixedCost);
    setCostPerUser(costPerUser);
    setPercentFee(percentFee);
    setCharity(charity);
}

double ProfitCalculator::operator()(double revenue, size_t users)const
{
    double result = revenue;
    if (useFixedCost)
    {
        result -= fixedCost;
    }

    if (useCostPerUser)
    {
        result -= costPerUser * users;
    }

    if (usePercentFee)
    {
        result -= percentFee * revenue;
    }

    if (useCharity)
    {
        result -= charity;
    }

    return result;
}

ProfitCalculator::Builder ProfitCalculator::builder() 
{
    return Builder();
}

ProfitCalculator::Builder::Builder() = default;

ProfitCalculator::Builder& ProfitCalculator::Builder::withFixedCost(double fixedCost)
{
    if (fixedCost < 0)
    {
        return *this;
    }
    this->fixedCost = fixedCost;
    useFixedCost = true;
    return *this;
}

ProfitCalculator::Builder& ProfitCalculator::Builder::withCostPerUser(double costPerUser)
{
    if (costPerUser < 0)
    {
        return *this;
    }
    this->costPerUser = costPerUser;
    useCostPerUser = true;
    return *this;
}

ProfitCalculator::Builder& ProfitCalculator::Builder::withPercentFee(double percentFee)
{
    if (percentFee < 0)
    {
        return *this;
    }
    this->percentFee = percentFee;
    usePercentFee = true;
    return *this;
}

ProfitCalculator::Builder& ProfitCalculator::Builder::withCharity(double charity)
{
    if (charity < 0)
    {
        return *this;
    }
    this->charity = charity;
    useCharity = true;
    return *this;
}

ProfitCalculator ProfitCalculator::Builder::build() const
{
    return ProfitCalculator(useFixedCost, fixedCost, useCostPerUser, costPerUser,
        usePercentFee, percentFee, useCharity, charity);
}

void ProfitCalculator::setFixedCost(double fixedCost)
{
    if (fixedCost < 0)
    {
        return;
    }
    this->fixedCost = fixedCost;
}

void ProfitCalculator::setCostPerUser(double costPerUser)
{
    if (costPerUser < 0)
    {
        return;
    }
    this->costPerUser = costPerUser;
}

void ProfitCalculator::setPercentFee(double percentFee)
{
    if (percentFee < 0)
    {
        return;
    }
    this->percentFee = percentFee;
}

void ProfitCalculator::setCharity(double charity)
{
    if (charity < 0)
    {
        return;
    }
    this->charity = charity;
}