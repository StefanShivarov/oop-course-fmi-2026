#include <iostream>
#include "Event.h"

int main() {
    User u1("user1@mail.com", 20, 100);
    User u2("user2@mail.com", 30, 10);

    Event ev("Concert", "Live music", CONCERT, 20, 5,5);

    ev.addUser(&u1);

    ev.addUserAtPosition(&u1, 2);

    std::cout << "Taken: " << ev.getOcupiedplaces() << std::endl;
    std::cout << "Free: " << ev.getFreespaces() << std::endl;

    ProfitCalculator calc;
    calc.setFixedCost(3200);
    calc.setCostPerUser(4.5);
    calc.setPercentage(0.05);

    std::cout << "Profit: " << ev.getProfit(calc) << std::endl;
}