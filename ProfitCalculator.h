#pragma once

class ProfitCalculator {
private:
    bool hasFixedCost = false;
    bool hasCostPerUser = false;
    bool hasPercentage = false;

    double fixedCost;
    double costPerUser;
    double percentage;

public:
    void setFixedCost(double val);

    void setCostPerUser(double val);

    void setPercentage(double val);

    double calculate(double revenue, int users) const;
};