#pragma once
#include <string>
#include <ostream>

class Dish
{
private:
    std::string name;
    std::string category;
    double price;

public:
    Dish(const std::string& name, const std::string& category, double price);

    const std::string& getName() const;
    const std::string& getCategory() const;
    double getPrice() const;

    void setPrice(double newPrice);

    friend std::ostream& operator<<(std::ostream& os, const Dish& dish);
};
