#include <iostream>
#include "Notebook.h"

using namespace std;

int main() {
    Notebook notebook("Stefcho's magical notebook", 5);
    notebook.appendToPage(0, "Dstr2 Lekciq 1");
    notebook.appendToPage(1, "Determinirane na avtomat\nTrivialno");

    Notebook copy = notebook;
    copy.setTitle("copy of notebook");
    printNotebook(copy);

    printNotebook(notebook);
}
