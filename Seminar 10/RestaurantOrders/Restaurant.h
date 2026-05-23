#pragma once
#include <string>
#include <vector>
#include <memory>
#include <ostream>
#include "Dish.h"
#include "Order.h"

class Restaurant
{
private:
    std::string name;

    // we could use std::vector<std::unique_ptr<Table>> if we didn't have pointers to the tables in the Order class
    std::vector<std::shared_ptr<Table>> tables;

    // we could use std::vector<std::unique_ptr<Dish>> if we didn't have pointers to the dishes in the Order class
    std::vector<std::shared_ptr<Dish>> menu;

    // we could use std::vector<std::unique_ptr<Order>> if we didn't have pointers to orders in the Table class
    std::vector<std::shared_ptr<Order>> orders;

public:
    explicit Restaurant(const std::string& name);

    const std::string& getName() const;

    bool addTable(unsigned number, unsigned seats);
    bool removeTable(unsigned number);
    std::shared_ptr<Table> findTable(unsigned number) const;

    bool addDish(const std::string& name, const std::string& category, double price);
    bool removeDish(const std::string& name);
    std::shared_ptr<Dish> findDish(const std::string& name) const;

    std::shared_ptr<Order> createOrder(unsigned tableNumber);
    std::shared_ptr<Order> findOrder(unsigned orderId) const;

    bool addDishToOrder(unsigned orderId, const std::string& dishName, unsigned quantity = 1);
    bool closeOrder(unsigned orderId);

    double getTableBill(unsigned tableNumber) const;
    std::vector<std::shared_ptr<Order>> getOrdersForTable(unsigned tableNumber) const;

    void cleanupExpiredOrders();
    void cleanupInvalidDishReferences();
    void removeClosedOrdersForTable(unsigned tableNumber);

    size_t countOpenOrders() const;

    void sortMenuByPrice();
    void sortTablesByNumber();

    explicit operator bool() const;

    friend std::ostream& operator<<(std::ostream& os, const Restaurant& restaurant);
};
