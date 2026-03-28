#pragma once
#include "Product.h"

class ProductFilter {
public:
    class Builder;

private:
    bool useName;
    bool useMinPrice;
    bool useMaxPrice;
    bool useMinQuantity;

    char* name;
    double minPrice;
    double maxPrice;
    int minQuantity;

    void copyFrom(const ProductFilter& other);
    void free();

    ProductFilter(
        bool useName,
        const char* name,
        bool useMinPrice,
        double minPrice,
        bool useMaxPrice,
        double maxPrice,
        bool useMinQuantity,
        int minQuantity
    );

public:
    // the only constructor we have is private, meaning objects of this class can only be created via the builder

    ProductFilter(const ProductFilter& other);
    ProductFilter& operator=(const ProductFilter& other);
    ~ProductFilter();

    bool operator()(const Product& product) const; // this allows the filter to act as a function

    static Builder builder(); // this static function returns a builder instance
                              // it's a common practice when implementing builder pattern
};

class ProductFilter::Builder {
private:
    bool useName = false;
    bool useMinPrice = false;
    bool useMaxPrice = false;
    bool useMinQuantity = false;

    char* name = nullptr;
    double minPrice = 0;
    double maxPrice = 0;
    int minQuantity = 0;

public:
    Builder();
    // we can forbid the copy operations for builders
    Builder(const Builder& other) = delete;
    Builder& operator=(const Builder& other) = delete;
    ~Builder();

    Builder& withName(const char* name);
    Builder& withMinPrice(double minPrice);
    Builder& withMaxPrice(double maxPrice);
    Builder& withMinQuantity(int minQuantity);

    ProductFilter build() const;
};