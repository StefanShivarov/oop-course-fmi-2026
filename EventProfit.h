#pragma once
#include "Event.h"

class EventProfit {
public:
    class Builder;

private:
    const Event& event;

    bool useOrganisationalExp;
    bool useUsersExp;
    bool useTax;
    bool useCharity;

    double organisationalExp;
    double usersExp;
    double tax;
    double charity;

    EventProfit(const Event&, bool, double, bool, double, bool, double, bool, double);
    

public:
    double getTotalIncome() const;

    double getProfit() const;
    
    double operator()() const;

    static Builder builder(const Event&);
};

class EventProfit::Builder {
private:
    const Event& event;

    bool useOrganisationalExp = false;
    bool useUsersExp = false;
    bool useTax = false;
    bool useCharity = false;

    double organisationalExp = 0.0;
    double usersExp = 0.0;
    double tax = 0.0;
    double charity = 0.0;

public:
    
    Builder(const Event&);

    Builder& withOrganisationalExp(double);

    Builder& withUsersExp(double);

    Builder& withTax(double);

    Builder& withCharity(double);

    EventProfit build() const;
    
};

