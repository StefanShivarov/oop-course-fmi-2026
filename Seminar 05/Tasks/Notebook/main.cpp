#include <iostream>
#include "Notebook.h"

int main()
{
    Notebook oop("Object Oriented Programming");
    oop.setNumberOfPages(3);


    oop.writeOnPage("Introduction to Classes and Objects.", 1);
    oop.writeOnPage("Constructosrs and Destructors.", 2);
    oop.writeOnPage("Memory management and Big 3.", 3);

    oop.markPageAsImportant(3);

    oop.writeOnPage("This is very important for the exam!", 3);

    std::cout << "--- Original Notebook (OOP) ---" << std::endl;
    oop.printNotebook();

    Notebook copyOfOop = oop;

    copyOfOop.setSubject("Copy of OOP Notes");
    copyOfOop.writeOnPage("STRANGE TEXT THAT SHOULD NOT BE IN THE ORIGINAL", 1);
    copyOfOop.markPageAsImportant(1);
    std::cout << std::endl;

    std::cout << "--- Copy of Notebook (Modified) ---" << std::endl;
    copyOfOop.printNotebook();


    std::cout << std::endl;
    std::cout << "--- Original Notebook after copy was modified (Should remain same) ---" << std::endl;
    oop.printNotebook();

    return 0;
}


