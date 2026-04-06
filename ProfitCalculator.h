#pragma once

class ProfitCalculator
{
public:
    class Builder;

private:
    bool useFixedCost;
    bool useCostPerUser;
    bool usePercentFee;
    bool useCharity;

    double fixedCost;
    double costPerUser;
    double percentFee;
    double charity;

    ProfitCalculator(bool useFixedCost,double fixedCost, bool useCostPerUser,
        double costPerUser,bool usePercentFee,double percentFee, 
        bool useCharity, double charity);

public:
    double operator()(double revenue, size_t users)const;
    static Builder builder();

    void setFixedCost(double fixedCost);
    void setCostPerUser(double costPerUser);
    void setPercentFee(double percentFee);
    void setCharity(double charity);
};

class ProfitCalculator::Builder
{
private:
    bool useFixedCost = false;
    bool useCostPerUser = false;
    bool usePercentFee = false;
    bool useCharity = false;

    double fixedCost = 0;
    double costPerUser = 0;
    double percentFee = 0;
    double charity = 0;

public:
    Builder();
    Builder(const Builder& other) = delete;
    Builder& operator=(const Builder& other) = delete;

    Builder& withFixedCost(double fixedCost);
    Builder& withCostPerUser(double costPerUser);
    Builder& withPercentFee(double percentFee);
    Builder& withCharity(double charity);

    ProfitCalculator build() const;
};