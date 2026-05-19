#pragma once
#include <memory>
#include <vector>
#include <string>
#include <ostream>

#include "Dish.h"
#include "Table.h"

class Order
{
private:
    static unsigned nextOrderId;
    unsigned id;
    std::weak_ptr<Table> table;
    std::vector<std::weak_ptr<Dish>> dishes;
    bool closed = false;

public:
    Order(const std::shared_ptr<Table>& table);

    unsigned getId() const;
    bool isClosed() const;
    bool isValid() const;

    void close();

    void addDish(const std::shared_ptr<Dish>& dish, unsigned quantity = 1);
    bool removeOneDish(const std::string& dishName);
    void removeInvalidDishes();

    double getTotal() const;
    std::shared_ptr<Table> getTable() const;
    size_t getDishCount() const;
    bool containsDish(const std::string& dishName) const;

    friend std::ostream& operator<<(std::ostream& os, const Order& order);
};
