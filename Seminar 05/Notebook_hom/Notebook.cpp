#include "Notebook.h"
#include<cstring>
#include <iostream>
#include <ostream>

void Notebook::copyFrom(const Notebook &other) {
    title= new char[strlen(other.title)+1];
    strcpy(title,other.title);

    pagesCount= other.pagesCount;
    pages = new Pages[pagesCount];
    for(int i=0;i<pagesCount;i++) {
        pages[i]=other.pages[i];
    }
}

void Notebook::free() {
    delete[] title;
    delete[] pages;
    title = nullptr;
    pages = nullptr;
    pagesCount = 0;
}

Notebook::Notebook(const char *title_, unsigned maxPages_) {
    title = new char[strlen(title_)+1];
    strcpy(title,title_);
    pagesCount = maxPages_;
    pages = new Pages[pagesCount];
}

Notebook::Notebook(const Notebook &other) {
    copyFrom(other);
}

Notebook Notebook::operator=(const Notebook &other) {
    if (this == &other) {
        return *this;
    }
    free();
    copyFrom(other);
    return *this;
}

Notebook::~Notebook() {
    free();
}

unsigned Notebook::getPagesCount() const {
    return pagesCount;
}

const char * Notebook::getTitle() const {
    return title;
}

void Notebook::addTextToPage(const char *text, unsigned index) {
    if (index > pagesCount) {
        return;
    }
    pages[index].append(text);
}

void Notebook::markPageAsImportant(unsigned index) {
    if (index >= pagesCount) {
        return;
    }
    pages[index].setPageAsImportant();
}

const Pages & Notebook::getPage(unsigned index) const {
    return pages[index];
}

void Notebook::print() const {
    std::cout << title << std::endl;
    std::cout << pagesCount << std::endl;

    for(int i=0;i<pagesCount;i++) {
        pages[i].print();
    }
}
