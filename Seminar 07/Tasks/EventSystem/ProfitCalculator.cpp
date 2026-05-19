#include "ProfitCalculator.h"

ProfitCalculator::ProfitCalculator(double fixedCost, bool useFixedCost,
                                 double costPerRegistration, bool useCostPerRegistration,
                                 double percentFee, bool usePercentFee,
                                 double charityAmount, bool useCharityAmount,
                                 double marketingCost, bool useMarketingCost)
    : fixedCost(fixedCost), useFixedCost(useFixedCost),
      costPerRegistration(costPerRegistration), useCostPerRegistration(useCostPerRegistration),
      percentFee(percentFee), usePercentFee(usePercentFee),
      charityAmount(charityAmount), useCharityAmount(useCharityAmount),
      marketingCost(marketingCost), useMarketingCost(useMarketingCost) {
}

double ProfitCalculator::operator()(const Event& event) const {
    double revenue = event.getCurrentRevenue();
    double result = revenue;

    if (useFixedCost) {
        result -= fixedCost;
    }

    if (usePercentFee) {
        result -= revenue * percentFee / 100.0;
    }

    if (useCostPerRegistration) {
        result -= costPerRegistration * (double) event.getTakenSeatsCount();
    }

    if (useCharityAmount) {
        result -= charityAmount;
    }

    if (useMarketingCost) {
        result -= marketingCost;
    }

    return result;
}

ProfitCalculator::Builder ProfitCalculator::builder() {
    return Builder();
}

ProfitCalculator ProfitCalculator::Builder::build() const {
    return ProfitCalculator(
        fixedCost, useFixedCost,
        costPerRegistration, useCostPerRegistration,
        percentFee, usePercentFee,
        charityAmount, useCharityAmount,
        marketingCost, useMarketingCost
    );
}

ProfitCalculator::Builder& ProfitCalculator::Builder::withFixedCost(double fixedCost) {
    this->fixedCost = fixedCost;
    useFixedCost = true;
    return *this;
}

ProfitCalculator::Builder& ProfitCalculator::Builder::withCostPerRegistration(double costPerRegistration) {
    this->costPerRegistration = costPerRegistration;
    useCostPerRegistration = true;
    return *this;
}

ProfitCalculator::Builder& ProfitCalculator::Builder::withPercentFee(double percentFee) {
    this->percentFee = percentFee;
    usePercentFee = true;
    return *this;
}

ProfitCalculator::Builder& ProfitCalculator::Builder::withCharityAmount(double charityAmount) {
    this->charityAmount = charityAmount;
    useCharityAmount = true;
    return *this;
}

ProfitCalculator::Builder& ProfitCalculator::Builder::withMarketingCost(double marketingCost) {
    this->marketingCost = marketingCost;
    useMarketingCost = true;
    return *this;
}
