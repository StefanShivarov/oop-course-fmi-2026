#include "ProductFilter.h"
#include <cstring>
#pragma warning(disable:4996)

void ProductFilter::copyFrom(const ProductFilter& other) {
    useName = other.useName;
    useMinPrice = other.useMinPrice;
    useMaxPrice = other.useMaxPrice;
    useMinQuantity = other.useMinQuantity;

    minPrice = other.minPrice;
    maxPrice = other.maxPrice;
    minQuantity = other.minQuantity;

    if (other.name) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    } else {
        name = nullptr;
    }
}

void ProductFilter::free() {
    delete[] name;
}

ProductFilter::ProductFilter(
    bool useName,
    const char* name,
    bool useMinPrice,
    double minPrice,
    bool useMaxPrice,
    double maxPrice,
    bool useMinQuantity,
    int minQuantity
)
    : useName(useName),
      useMinPrice(useMinPrice),
      useMaxPrice(useMaxPrice),
      useMinQuantity(useMinQuantity),
      minPrice(minPrice),
      maxPrice(maxPrice),
      minQuantity(minQuantity) {
    if (name) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    } else {
        this->name = nullptr;
    }
}

ProductFilter::ProductFilter(const ProductFilter& other) {
    copyFrom(other);
}

ProductFilter& ProductFilter::operator=(const ProductFilter& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

ProductFilter::~ProductFilter() {
    free();
}

bool ProductFilter::operator()(const Product& product) const {
    if (useName && strcmp(product.getName(), name) != 0) {
        return false;
    }

    if (useMinPrice && product.getPrice() < minPrice) {
        return false;
    }

    if (useMaxPrice && product.getPrice() > maxPrice) {
        return false;
    }

    if (useMinQuantity && product.getQuantity() < minQuantity) {
        return false;
    }

    return true;
}

ProductFilter::Builder ProductFilter::builder() {
    return Builder();
}

// Builder

ProductFilter::Builder::Builder() = default;

ProductFilter::Builder::~Builder() {
    delete[] name;
}

ProductFilter::Builder& ProductFilter::Builder::withName(const char* name) {
    delete[] this->name;
    this->name = nullptr;

    if (name) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        useName = true;
    } else {
        useName = false;
    }

    return *this;
}

ProductFilter::Builder& ProductFilter::Builder::withMinPrice(double minPrice) {
    this->minPrice = minPrice;
    useMinPrice = true;
    return *this;
}

ProductFilter::Builder& ProductFilter::Builder::withMaxPrice(double maxPrice) {
    this->maxPrice = maxPrice;
    useMaxPrice = true;
    return *this;
}

ProductFilter::Builder& ProductFilter::Builder::withMinQuantity(int minQuantity) {
    this->minQuantity = minQuantity;
    useMinQuantity = true;
    return *this;
}

ProductFilter ProductFilter::Builder::build() const {
    return ProductFilter(
        useName,
        name,
        useMinPrice,
        minPrice,
        useMaxPrice,
        maxPrice,
        useMinQuantity,
        minQuantity
    );
}
