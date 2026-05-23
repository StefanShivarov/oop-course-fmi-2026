#include "Table.h"
#include "Order.h"

#include <algorithm>
#include <numeric>

Table::Table(unsigned number, unsigned seats)
    : number(number), seats(seats)
{
}

unsigned Table::getNumber() const
{
    return number;
}

unsigned Table::getSeats() const
{
    return seats;
}

void Table::addOrder(const std::shared_ptr<Order>& order)
{
    if (order)
    {
        orders.push_back(order);
    }
}

void Table::cleanupExpiredOrders()
{
    std::erase_if(orders,[](const std::weak_ptr<Order>& weakOrder){
        return weakOrder.expired();
    });
}

double Table::getBill() const
{
    return std::accumulate(orders.begin(), orders.end(), 0.0,
        [](double sum, const std::weak_ptr<Order>& weakOrder)
        {
            auto order = weakOrder.lock();
            if (!order)
            {
                return sum;
            }

            return sum + order->getTotal();
        });

    // alternatively:
    /*
    double total = 0.0;
    for (int i = 0; i < orders.size(); i++) {
        auto order = orders.at(i).lock();
        if (order) {
            total += order->getTotal();
        }
    }
    return total;
    */
}

size_t Table::getActiveOrdersCount() const
{
    return std::count_if(orders.begin(), orders.end(),
            [](const std::weak_ptr<Order>& weakOrder)
            {
                auto order = weakOrder.lock();
                return order && !order->isClosed();
            });
}

std::ostream& operator<<(std::ostream& os, const Table& table)
{
    os << "Table #" << table.number
       << " | Seats: " << table.seats
       << " | Active orders: " << table.getActiveOrdersCount()
       << " | Bill: " << table.getBill();
    return os;
}
