#include <iostream>
#include "User.h"
#include "Event.h"
#include "Registration.h"
#include "EventProfit.h"

using std::cout;

int main()
{
    User fan1("fan1@gmail.com", 25, 1000);
    User fan2("fan2@gmail.com", 30, 700);
    User fan3("fan3@gmail.com", 22, 500);

    Event worldCup("World Cup Final 2026", "VIP Box", "Sport Event", 40, 0,600);
    double totalCost = 600.0;

    cout << "Free seats: " << worldCup.getFreeSpacesCount() << "\n";
    cout << "Occupied seats: " << worldCup.getTakenSpacesCount() <<'\n';

    cout << '\n';

    if (fan1.pay(totalCost)) {
        Registration r1(&fan1, totalCost); 

        worldCup.registеrUser(r1);
        cout << "Register fan1: Successful registration\n";
    }


    if (fan2.pay(totalCost)) { 
        Registration r2(&fan2, totalCost);

        worldCup.registеrUser(r2);
        cout << "Register fan2: Successful registration\n";
    }


    if (fan3.pay(totalCost)) { 
        Registration r3(&fan3, totalCost); 

        worldCup.registеrUser(r3);
        cout << "Register fan3: Successful registration\n";
    }
    else { 
        cout << "Register fan3: Error! Not enough budget\n";
    }

    cout << '\n';

    cout << "Free seats: " << worldCup.getFreeSpacesCount() << "\n";
    cout << "Occupied seats: " << worldCup.getTakenSpacesCount() << '\n';

    cout << '\n';

    worldCup.remove(0);
    std::cout << "Free seats after remove: " << worldCup.getFreeSpacesCount() << "\n\n";

    EventProfit profitCalc = EventProfit::builder()
        .withExpenseForEvent(150.0)  
        .withExpenseForUser(25.0)    
        .withProfitTaxRate(0.10)     
        .build();

    cout << "Profit: " << worldCup.calculateProfit(profitCalc) << "\n";
    
}