#pragma once
#include <memory>
#include <vector>
#include <ostream>

class Order;

class Table
{
private:
    unsigned number;
    unsigned seats;
    std::vector<std::weak_ptr<Order>> orders;

public:
    Table(unsigned number, unsigned seats);

    unsigned getNumber() const;
    unsigned getSeats() const;

    void addOrder(const std::shared_ptr<Order>& order);
    void cleanupExpiredOrders();

    double getBill() const;
    size_t getActiveOrdersCount() const;

    friend std::ostream& operator<<(std::ostream& os, const Table& table);
};
