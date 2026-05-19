#include <iostream>
#include "User.h"
#include "Event.h"
#include "ProfitCalculator.h"

int main() {
    User u1("Alice Johnson", "alice@mail.com", 19, 120.0);
    User u2("Bob Smith", "bob@mail.com", 17, 40.0);
    User u3("Chris Brown", "chris@mail.com", 68, 90.0);
    User u4("Diana Green", "diana@mail.com", 24, 150.0);
    User smallBudgetUser("Tiny Budget", "tiny@mail.com", 22, 5.0);

    Event seminar(
        "C++ OOP Seminar",
        "Dynamic memory, rule of 5 and arrays of pointers",
        EventType::SEMINAR,
        15.0, // nobody's paying for this one :D
        20
    );

    std::cout << "Initial users:\n";
    printUser(u1);
    printUser(u2);
    printUser(u3);
    printUser(u4);
    printUser(smallBudgetUser);
    std::cout << '\n';

    std::cout << "Initial event state:\n";
    printEvent(seminar);

    std::cout << "Register u1 on first free seat:\n";
    std::cout << seminar.registerUser(u1) << '\n';
    printEvent(seminar);

    std::cout << "Register u2 on seat 3:\n";
    std::cout << seminar.registerUserAtSeat(u2, 3) << '\n';
    printEvent(seminar);

    std::cout << "Register u3 on seat 3 again (should go to first free seat):\n";
    std::cout << seminar.registerUserAtSeat(u3, 3) << '\n';
    printEvent(seminar);

    std::cout << "Register u4 through pointer on seat 1:\n";
    std::cout << seminar.registerUserAtSeat(&u4, 1) << '\n';
    printEvent(seminar);

    std::cout << "Try to register user with too small budget:\n";
    std::cout << seminar.registerUser(smallBudgetUser) << '\n';
    printEvent(seminar);

    std::cout << "Budgets after registrations:\n";
    printUser(u1);
    printUser(u2);
    printUser(u3);
    printUser(u4);
    printUser(smallBudgetUser);
    std::cout << '\n';

    std::cout << "Remove registration from seat 3:\n";
    seminar.removeRegistration(3);
    printEvent(seminar);

    std::cout << "Register stefo on seat 15:\n";
    std::cout << seminar.registerUserAtSeat(new User("Stefo", "stf@test.cx", 22, 80.0), 15, true) << '\n';
    printEvent(seminar);

    ProfitCalculator profitCalculator = ProfitCalculator::builder()
        .withFixedCost(20.0)
        .withCostPerRegistration(4.5)
        .withPercentFee(5.0)
        .build();

    std::cout << "Estimated profit for event: "
              << profitCalculator(seminar) << '\n';
}
