#pragma once
#include "Event.h"

class ProfitCalculator {
public:
    double operator()(const Event& event) const;

    class Builder {
    public:
        Builder& withFixedCost(double fixedCost);
        Builder& withCostPerRegistration(double costPerRegistration);
        Builder& withPercentFee(double percentFee);
        Builder& withCharityAmount(double charityAmount);
        Builder& withMarketingCost(double marketingCost);

        ProfitCalculator build() const;

    private:
        double fixedCost = 0.0;
        bool useFixedCost = false;

        double costPerRegistration = 0.0;
        bool useCostPerRegistration = false;

        double percentFee = 0.0;
        bool usePercentFee = false;

        double charityAmount = 0.0;
        bool useCharityAmount = false;

        double marketingCost = 0.0;
        bool useMarketingCost = false;
    };

    static Builder builder();

private:
    ProfitCalculator(double fixedCost, bool useFixedCost,
                    double costPerRegistration, bool useCostPerRegistration,
                    double percentFee, bool usePercentFee,
                    double charityAmount, bool useCharityAmount,
                    double marketingCost, bool useMarketingCost);

    double fixedCost = 0.0;
    bool useFixedCost = false;

    double costPerRegistration = 0.0;
    bool useCostPerRegistration = false;

    double percentFee = 0.0;
    bool usePercentFee = false;

    double charityAmount = 0.0;
    bool useCharityAmount = false;

    double marketingCost = 0.0;
    bool useMarketingCost = false;
};
