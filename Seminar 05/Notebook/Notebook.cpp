#include "Notebook.h"
#include <iostream>
#include <cstring>
#pragma warning(disable:4996)

void Notebook::setTitle(const char* title) {
    if (!title) {
        this->title = new char[1];
        this->title[0] = '\0';
        return;
    }

    this->title = new char[strlen(title) + 1];
    strcpy(this->title, title);
}

void Notebook::copyFrom(const Notebook& other) {
    setTitle(other.title);
    pagesCount = other.pagesCount;
    pages = new Page[pagesCount];

    for (size_t i = 0; i < pagesCount; i++) {
        pages[i] = other.pages[i];
    }
}

void Notebook::free() {
    delete[] title;
    delete[] pages;

    title = nullptr;
    pages = nullptr;
    pagesCount = 0;
}

Notebook::Notebook() : Notebook("Notebook", DEFAULT_PAGES_COUNT) {
    setTitle("");
    pages = nullptr;
}

Notebook::Notebook(const char* title, size_t pagesCount) : pagesCount(pagesCount) {
    setTitle(title);
    pages = new Page[pagesCount];
}

Notebook::Notebook(const Notebook& other) {
    copyFrom(other);
}

Notebook& Notebook::operator=(const Notebook& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Notebook::~Notebook() {
    free();
}

bool Notebook::appendToPage(size_t index, const char* text) {
    if (index >= pagesCount) {
        return false;
        // throw std::out_of_range("Invalid page index");
    }
    pages[index].append(text);
    return true;
}

void Notebook::markPageAsImportant(size_t index) {
    if (index >= pagesCount) {
        //throw std::out_of_range("Invalid page index");
        return;
    }
    pages[index].markAsImportant();
}

size_t Notebook::getPagesCount() const {
    return pagesCount;
}

const char* Notebook::getTitle() const {
    return title;
}

const Page& Notebook::getPage(size_t index) const {
    if (index >= pagesCount) {
        // throw exception would be better, but for now we can do this
        return pages[pagesCount - 1];
    }
    return pages[index];
}

void printNotebook(const Notebook& notebook, std::ostream& os) {
    os << "Notebook title: " << notebook.getTitle() << '\n';
    size_t pagesCount = notebook.getPagesCount();
    os << "Pages count: " << pagesCount << "\n\n";

    for (size_t i = 0; i < pagesCount; i++) {
        os << "Page #" << i + 1 << ":\n";
        printPage(notebook.getPage(i));
        os << '\n';
    }

}