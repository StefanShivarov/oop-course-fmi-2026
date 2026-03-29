#include <iostream>
#include"Notebook.h"

int main()
{
    Notebook oop("OOP", 3);

    oop.addTextToPage(0, "Value semantics");
    oop.addTextToPage(1, "Rule of 3");
    oop.addTextToPage(2, "Move semantics");
	oop.addTextToPage(3, "Operators");

    oop.markPageAsImportant(1);

    std::println("Original notebook:");
    oop.printNotebook();
    std::println();

    Notebook copyNotebook = oop;

    copyNotebook.addTextToPage(2, " (added in copy)");
    copyNotebook.markPageAsImportant(0);

    std::println("Modified copy notebook:");
    copyNotebook.printNotebook();
    std::println();

	Notebook assigmentNotebook;
    assigmentNotebook = copyNotebook;

	assigmentNotebook.addTextToPage(1, " (added in assignment)");
    std::println("Modified assignment notebook:");
	assigmentNotebook.printNotebook();

    return 0;
}

