#include <iostream>
#include "Product.h"
#include "ProductFilter.h"

void filterProducts(const Product* products, size_t count, const ProductFilter& filter) {
    for (std::size_t i = 0; i < count; i++) {
        if (filter(products[i])) {
            std::cout << products[i] << std::endl;
        }
    }
}

int main() {
    Product p1("Notebook", 2200, 5);
    Product p2("WirelessMouse", 45, 30);
    Product p3("Monitor", 1800, 2);
    Product p4("MechanicalKeyboard", 120, 10);
    Product p5("DeskLamp", 2400, 7);

    Product products[] = { p1, p2, p3, p4, p5 };
    size_t productsCount = std::size(products); // this is the same as sizeof(products) / sizeof(Product)

    // filter products with max price of 2300 and min quantity of 3
    ProductFilter customFilter = ProductFilter::builder()
        .withMaxPrice(2300)
        .withMinQuantity(3)
        .build();

    filterProducts(products, productsCount, customFilter);
}
