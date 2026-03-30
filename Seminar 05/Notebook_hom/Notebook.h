#pragma once
#include "Pages.h"

class Notebook {
    Pages* pages;
    char* title;
    unsigned MAX_PAGES;
    unsigned pagesCount;
    void copyFrom(const Notebook& other);
    void free();

    public:
    Notebook(const char* title_, unsigned maxPages_ );
    Notebook(const Notebook& other);
    Notebook operator=(const Notebook& other);
    ~Notebook();
    unsigned getPagesCount() const;
    const char* getTitle() const;
    void addTextToPage(const char* text, unsigned index);
    void markPageAsImportant(unsigned index);
    const Pages& getPage(unsigned index) const;

    void print()const;

};


