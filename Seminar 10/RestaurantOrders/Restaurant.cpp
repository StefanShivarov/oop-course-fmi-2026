#include "Restaurant.h"
#include "Table.h"
#include "Dish.h"
#include "Order.h"

#include <algorithm>

Restaurant::Restaurant(const std::string& name)
    : name(name)
{
}

const std::string& Restaurant::getName() const
{
    return name;
}

bool Restaurant::addTable(unsigned number, unsigned seats)
{
    if (findTable(number))
    {
        return false;
    }

    tables.push_back(std::make_shared<Table>(number, seats));
    return true;
}

bool Restaurant::removeTable(unsigned number)
{
    const auto oldSize = tables.size();

    tables.erase(
        std::remove_if(tables.begin(), tables.end(),
            [&number](const std::shared_ptr<Table>& table)
            {
                return table->getNumber() == number;
            }),
        tables.end()
    );

    if (tables.size() == oldSize)
    {
        return false;
    }

    cleanupExpiredOrders();
    return true;
}

std::shared_ptr<Table> Restaurant::findTable(unsigned number) const
{
    auto it = std::find_if(tables.begin(), tables.end(),
        [&number](const std::shared_ptr<Table>& table)
        {
            return table->getNumber() == number;
        });

    return it == tables.end() ? nullptr : *it;
}

bool Restaurant::addDish(const std::string& name, const std::string& category, double price)
{
    if (findDish(name))
    {
        return false;
    }

    menu.push_back(std::make_shared<Dish>(name, category, price));
    return true;
}

bool Restaurant::removeDish(const std::string& name)
{
    const auto oldSize = menu.size();

    std::erase_if(menu, [&name](const std::shared_ptr<Dish>& dish){
        return dish->getName() == name;
    });

    if (menu.size() == oldSize)
    {
        return false;
    }

    cleanupInvalidDishReferences();
    return true;
}

std::shared_ptr<Dish> Restaurant::findDish(const std::string& name) const
{
    auto it = std::find_if(menu.begin(), menu.end(),
        [&name](const std::shared_ptr<Dish>& dish)
        {
            return dish->getName() == name;
        });

    return it == menu.end() ? nullptr : *it;
}

std::shared_ptr<Order> Restaurant::createOrder(unsigned tableNumber)
{
    auto table = findTable(tableNumber);
    if (!table)
    {
        return nullptr;
    }

    auto order = std::make_shared<Order>(table);
    orders.push_back(order);
    table->addOrder(order);

    return order;
}

std::shared_ptr<Order> Restaurant::findOrder(unsigned orderId) const
{
    auto it = std::find_if(orders.begin(), orders.end(),
        [&orderId](const std::shared_ptr<Order>& order)
        {
            return order->getId() == orderId;
        });

    return it == orders.end() ? nullptr : *it;
}

bool Restaurant::addDishToOrder(unsigned orderId, const std::string& dishName, unsigned quantity)
{
    auto order = findOrder(orderId);
    auto dish = findDish(dishName);

    if (!order || !dish || order->isClosed())
    {
        return false;
    }

    order->addDish(dish, quantity);
    return true;
}

bool Restaurant::closeOrder(unsigned orderId)
{
    auto order = findOrder(orderId);
    if (!order)
    {
        return false;
    }

    order->close();
    return true;
}

double Restaurant::getTableBill(unsigned tableNumber) const
{
    auto table = findTable(tableNumber);
    return table ? table->getBill() : 0.0;
}

std::vector<std::shared_ptr<Order>> Restaurant::getOrdersForTable(unsigned tableNumber) const
{
    std::vector<std::shared_ptr<Order>> result;

    std::ranges::copy_if(orders, std::back_inserter(result),
    [&tableNumber](const std::shared_ptr<Order>& order){
        auto table = order->getTable();
        return table && table->getNumber() == tableNumber;
    });

    // or alternatively:
    /*
    result.reserve(orders.size());
    for (const auto& order : orders)
    {
        auto table = order->getTable();
        if (table && table->getNumber() == tableNumber)
        {
            result.push_back(order);
        }
    }
    */

    return result;
}

void Restaurant::cleanupExpiredOrders()
{
    std::erase_if(orders, [](const std::shared_ptr<Order>& order){
        return !order->isValid();
    });

    for (auto& table : tables)
    {
        table->cleanupExpiredOrders();
    }
}

void Restaurant::cleanupInvalidDishReferences()
{
    for (auto& order : orders)
    {
        order->removeInvalidDishes();
    }
}

void Restaurant::removeClosedOrdersForTable(unsigned tableNumber)
{
    std::erase_if(orders,
    [&tableNumber](const std::shared_ptr<Order>& order){
        auto table = order->getTable();
        return table && table->getNumber() == tableNumber && order->isClosed();
    });

    for (auto& table : tables)
    {
        table->cleanupExpiredOrders();
    }
}

size_t Restaurant::countOpenOrders() const
{
    return std::count_if(orders.begin(), orders.end(),
    [](const std::shared_ptr<Order>& order){
        return !order->isClosed();
    });
}

void Restaurant::sortMenuByPrice()
{
    std::sort(menu.begin(), menu.end(),
        [](const std::shared_ptr<Dish>& lhs, const std::shared_ptr<Dish>& rhs)
        {
            if (lhs->getPrice() == rhs->getPrice())
            {
                return lhs->getName() < rhs->getName();
            }

            return lhs->getPrice() < rhs->getPrice();
        });
}

void Restaurant::sortTablesByNumber()
{
    std::sort(tables.begin(), tables.end(),
        [](const std::shared_ptr<Table>& lhs, const std::shared_ptr<Table>& rhs)
        {
            return lhs->getNumber() < rhs->getNumber();
        });
}

Restaurant::operator bool() const
{
    return !tables.empty() && countOpenOrders() >= tables.size();
}

std::ostream& operator<<(std::ostream& os, const Restaurant& restaurant)
{
    os << "Restaurant: " << restaurant.name << '\n';

    os << "\nMenu:\n";
    if (restaurant.menu.empty())
    {
        os << "  <empty>\n";
    }
    else
    {
        for (const auto& dish : restaurant.menu)
        {
            os << "  " << *dish << '\n';
        }
    }

    os << "\nTables:\n";
    if (restaurant.tables.empty())
    {
        os << "  <empty>\n";
    }
    else
    {
        for (const auto& table : restaurant.tables)
        {
            os << "  " << *table << '\n';
        }
    }

    os << "\nOrders:\n";
    if (restaurant.orders.empty())
    {
        os << "  <empty>\n";
    }
    else
    {
        for (const auto& order : restaurant.orders)
        {
            os << "  " << *order << '\n';
        }
    }

    return os;
}
