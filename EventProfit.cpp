#include "EventProfit.h"

EventProfit::EventProfit(
    const Event& event,
    bool useOrganisationalExp, 
    double organisationalExp,
    bool useUsersExp,
    double usersExp,
    bool useTax,
    double tax,
    bool useCharity, 
    double charity
) : event(event),
    useOrganisationalExp(useOrganisationalExp),
    useUsersExp(useUsersExp),
    useTax(useTax),
    useCharity(useCharity),
    organisationalExp(organisationalExp),
    usersExp(usersExp),
    tax(tax),
    charity(charity) {
}

double EventProfit::getTotalIncome() const
{
    return event.getTicketPrice() * event.occupiedSeats();
}

double EventProfit::getProfit() const
{
    double income = getTotalIncome();
    size_t users = event.occupiedSeats();
    double profit = income;

    if (useOrganisationalExp) {
        profit -= organisationalExp;
    }
        

    if (useTax) {
        profit -= tax * income;
    }
        

    if (useUsersExp) {
        profit -= usersExp * users;
    }
        

    if (useCharity) {
        profit -= charity;
    }
        

    return profit;
}

double EventProfit::operator()() const
{
    return getProfit();
}

EventProfit::Builder EventProfit::builder(const Event& event)
{
    return Builder(event);
}

EventProfit::Builder::Builder(const Event& event) : event(event) {}

EventProfit::Builder& EventProfit::Builder::withOrganisationalExp(double exp)
{
    organisationalExp = exp;
    useOrganisationalExp = true;
    return *this;
}

EventProfit::Builder& EventProfit::Builder::withUsersExp(double exp)
{
    usersExp = exp;
    useUsersExp = true;
    return *this;
}

EventProfit::Builder& EventProfit::Builder::withTax(double percent)
{
    tax = percent / 100.0;
    useTax = true;
    return *this;
}

EventProfit::Builder& EventProfit::Builder::withCharity(double amount)
{
    charity = amount;
    useCharity = true;
    return *this;
}

EventProfit EventProfit::Builder::build() const
{
    return EventProfit(
        event,
        useOrganisationalExp, organisationalExp,
        useUsersExp, usersExp,
        useTax, tax,
        useCharity, charity
    );
}

