#include <iostream>
#include "Restaurant.h"

int main()
{
    Restaurant restaurant("Pointers Bistro");

    restaurant.addTable(1, 2);
    restaurant.addTable(2, 4);
    restaurant.addTable(5, 6);

    restaurant.addDish("Margherita", "Pizza", 12.50);
    restaurant.addDish("Pepperoni", "Pizza", 14.20);
    restaurant.addDish("Caesar Salad", "Salad", 9.80);
    restaurant.addDish("Water", "Drinks", 2.00);
    restaurant.addDish("Cola", "Drinks", 3.50);

    restaurant.sortMenuByPrice();
    restaurant.sortTablesByNumber();

    auto order1 = restaurant.createOrder(2);
    auto order2 = restaurant.createOrder(2);
    auto order3 = restaurant.createOrder(5);

    if (order1)
    {
        restaurant.addDishToOrder(order1->getId(), "Margherita", 2);
        restaurant.addDishToOrder(order1->getId(), "Water", 2);
    }

    if (order2)
    {
        restaurant.addDishToOrder(order2->getId(), "Pepperoni", 1);
        restaurant.addDishToOrder(order2->getId(), "Cola", 3);
    }

    if (order3)
    {
        restaurant.addDishToOrder(order3->getId(), "Caesar Salad", 2);
        restaurant.addDishToOrder(order3->getId(), "Water", 2);
    }

    std::cout << "Initial state:\n";
    std::cout << restaurant << "\n\n";

    std::cout << "Bill for table 2: " << restaurant.getTableBill(2) << '\n';
    std::cout << "Bill for table 5: " << restaurant.getTableBill(5) << '\n';
    std::cout << "Open orders: " << restaurant.countOpenOrders() << "\n\n";

    restaurant.closeOrder(order1->getId());
    restaurant.closeOrder(order2->getId());

    std::cout << "After closing two orders:\n";
    std::cout << restaurant << "\n\n";

    restaurant.removeClosedOrdersForTable(2);

    std::cout << "After removing closed orders for table 2:\n";
    std::cout << restaurant << "\n\n";

    restaurant.removeDish("Water");

    std::cout << "After removing dish 'Water' from menu:\n";
    std::cout << restaurant << "\n\n";

    restaurant.removeTable(5);

    std::cout << "After removing table 5:\n";
    std::cout << restaurant << "\n\n";

    if (restaurant)
    {
        std::cout << "Restaurant is busy.\n";
    }
    else
    {
        std::cout << "Restaurant is not busy.\n";
    }

    return 0;
}
