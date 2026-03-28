#include <iostream>
#include <print>
#include "Notebook.h"

int main()
{
    Notebook math("Mathematics", 3);

    math.addTextToPage(0, "Limits and derivatives.");
    math.addTextToPage(1, "Integrals.");
    math.addTextToPage(2, "Linear algebra.");

    math.markAsImportant(1);

    std::println("Original notebook:");
    math.print();

    Notebook copy = math;

    copy.addTextToPage(0, " (IMPORTANT TOPIC)");
    copy.markAsImportant(0);

    std::println ("Modified copy:");
    copy.print();

    return 0;
}

