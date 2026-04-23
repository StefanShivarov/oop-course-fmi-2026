#include <iostream>
#include "User.h"
#include "Event.h"
#include "ProfitCalculator.h"

int main() {
    
    User u1("ivan@gmail.com", 20, 500);
    User u2("maria@gmail.com", 30, 200);
    User u3("simeon@gmail.com", 25, 50);
   
    ProfitCalculator calc = ProfitCalculator::builder()
        .withFixedCost(3200)
        .withCostPerUser(4.5)
        .withPercentFee(0.05)
        .withCharity(100) 
        .build();

    Event event("Concert", "Live music", Type::CONCERT, 3200, 100, 30);

    event.addUser(&u1);
    event.addUser(&u2);

    event.addUser(&u3, 10);
    event.addUser(User("georgi@gmail.com", 22, 100));

    std::cout << "Taken seats: " << event.takenSeats() << std::endl;
    std::cout << "Free seats: " << event.freeSeats() << std::endl;

    double revenue = event.calculateRevenue();
    std::cout << "Revenue: " << revenue << std::endl;

    double profit = calc(revenue, event.takenSeats());
    std::cout << "Profit: " << profit << std::endl;

    event.removeUser(0);

    std::cout << "After remove:\n";
    std::cout << "Taken seats: " << event.takenSeats() << std::endl;
    std::cout << "Free seats: " << event.freeSeats() << std::endl;

    return 0;
}