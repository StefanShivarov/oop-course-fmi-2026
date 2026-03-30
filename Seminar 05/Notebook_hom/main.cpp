#include "Pages.h"
#include "Notebook.h"
#include <iostream>


int main() {
    Notebook notebook("Object-Oriented Programming", 3);

    notebook.addTextToPage("Classes and objects.", 0);
    notebook.addTextToPage(" Constructors and destructors.", 0);

    notebook.addTextToPage("Inheritance.",1);
    notebook.markPageAsImportant(1);

    notebook.addTextToPage("Polymorphism.", 2);

    std::cout << "Original notebook:" << std::endl;
    notebook.print();

    std::cout << std::endl;

    Notebook copyNotebook = notebook;
    copyNotebook.addTextToPage(" Copy changed.", 0);
    copyNotebook.markPageAsImportant(2);

    std::cout << "Copied notebook after changes:" << std::endl;
    copyNotebook.print();

    std::cout << std::endl;

    std::cout << "Original notebook again (must stay unchanged):" << std::endl;
    notebook.print();

    return 0;
}