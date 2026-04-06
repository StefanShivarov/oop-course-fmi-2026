#include <iostream>
#include "User.h"
#include "Event.h"
#include "EventProfit.h"

int main()
{
    
    User u1("ivan@abv.bg", 25, 200.0);
    User u2("maria@abv.bg", 30, 50.0);
    User u3("petar@abv.bg", 22, 10.0); 

    Event concert("Rock Concert", "Amazing rock concert", Type::CONCERT, 20.0, 5, 30.0);

    std::cout << "Free seats: " << concert.freeSeats() << "\n";       
    std::cout << "Occupied seats: " << concert.occupiedSeats() << "\n"; 

    std::cout << concert.registerUser(u1) << "\n"; 
    std::cout << concert.registerUser(u2) << "\n"; 
    std::cout << concert.registerUser(u3) << "\n"; 

    std::cout << "Free seats: " << concert.freeSeats() << "\n";       
    std::cout << "Occupied seats: " << concert.occupiedSeats() << "\n"; 

    concert.removeRegistration(u1);
    std::cout << "Free seats after remove: " << concert.freeSeats() << "\n"; 

    EventProfit profit = EventProfit::builder(concert)
        .withOrganisationalExp(3200.0)
        .withUsersExp(4.5)
        .withTax(5)
        .build();

    std::cout << "Total income: " << profit.getTotalIncome() << "\n";
    std::cout << "Profit: " << profit() << "\n";

    return 0;
}

