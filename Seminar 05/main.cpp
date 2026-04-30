#include "notebook.h"
#include <iostream>

int main()
{
    const char *title = "Geometry";
    const int pages = 5;
    const char *textOnPage[pages] = {"Dot product", "Cross product", "Mixed product", "A(1,0,6), B(0,0,13)", "Medicenter"};
    int important = 0b100;
    Notebook tetradkataNaStefo(title, textOnPage, pages, important);
    Notebook tetradkataNaSerhan = tetradkataNaStefo;
    tetradkataNaSerhan.writeMoreToPage(0, " Evklidovo prostranstvo");
    tetradkataNaSerhan.print();
    std::cout << "\n";
    tetradkataNaStefo.print();
}