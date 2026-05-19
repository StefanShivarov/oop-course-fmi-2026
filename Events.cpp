
#include <iostream>
#include "User.h"
#include "Registration.h"
#include "Event.h"

int main()
{
    User user1("alice@mail.com", 25, 120.0);
    User user2("bobi@mail.com", 30, 80.0);
    User user3("martii@mail.com", 19, 200.0);
    User user4("kris@mail.com", 40, 10.0); 

    Registration reg1(&user1);
    Registration reg2(&user2);
    Registration reg3(&user3);
    Registration reg4(&user4);

    Event event( "Summer Concert","Big music event in the city park",EventType::Concert,20.0,5,15.0    );
    std::cout << "------------ Initial state --------" << std::endl;
    event.printSeats();
    std::cout << std::endl;
    std::cout << "Add user1 on first free seat: ";
    std::cout << (event.addRegistration(reg1) ? "success" : "failed") << std::endl;
    std::cout << "Add user2 on seat 3: ";
    std::cout << (event.addRegistrationAtSeat(reg2, 3) ? "success" : "failed") << std::endl;
    std::cout << "Add user3 on seat 3 (if occupied -> first free): ";
    std::cout << (event.addRegistrationAtSeat(reg3, 3) ? "success" : "failed") << std::endl;
    std::cout << "Add user4 with too small budget: ";
    std::cout << (event.addRegistration(reg4) ? "success" : "failed") << std::endl;
    std::cout << std::endl;
    std::cout << "-------- After registrations ------------" << std::endl;
    event.printSeats();
    std::cout << std::endl;
    std::cout << "Remove registration from seat 3: ";
    std::cout << (event.removeRegistrationBySeat(3) ? "success" : "failed") << std::endl;
    std::cout << std::endl;
    std::cout << "----- After removing seat 3 ------" << std::endl;
    event.printSeats();
    std::cout << std::endl;

    ProfitConfig config;
    config.setFixedCost(3200.0);
    config.setPerPersonCost(4.5);
    config.setVenueFeePercent(0.05);
    std::cout << "Revenue: " << event.calculateRevenue() << std::endl;
    std::cout << "Expected profit: " << event.calculateExpectedProfit(config) << std::endl;
    std::cout << std::endl;

    std::cout << "--------- Remaining budgets -------------------" << std::endl;
    std::cout << user1.getEmail() << " -> " << user1.getBudget() << std::endl;
    std::cout << user2.getEmail() << " -> " << user2.getBudget() << std::endl;
    std::cout << user3.getEmail() << " -> " << user3.getBudget() << std::endl;
    std::cout << user4.getEmail() << " -> " << user4.getBudget() << std::endl;

    return 0;
}


