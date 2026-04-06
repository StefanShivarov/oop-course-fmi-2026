#pragma once
class ProfitConfig
{
private:
    bool hasFixedCost;
    double fixedCost;
    bool hasPerPersonCost;
    double perPersonCost;
    bool hasVenueFee;
    double venueFeePercent;
    bool hasCharity;
    double charityAmount;

public:
    ProfitConfig();

    void setFixedCost(double value);
    void setPerPersonCost(double value);
    void setVenueFeePercent(double value);
    void setCharityAmount(double value);


    bool hasFixed() const;
    bool hasPerPerson() const;
    bool hasVenue() const;
    bool hasCharityValue() const;


    double getFixedCost() const;
    double getPerPersonCost() const;
    double getVenueFeePercent() const;
    double getCharityAmount() const;
};

