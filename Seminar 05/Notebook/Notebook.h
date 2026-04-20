#pragma once
#include "Page.h"

class Notebook {
private:
    char* title = nullptr;
    Page* pages = nullptr;
    size_t pagesCount = 0;

    static constexpr size_t DEFAULT_PAGES_COUNT = 30;

    void copyFrom(const Notebook& other);
    void free();

public:
    Notebook();
    Notebook(const char* title, size_t pagesCount);
    Notebook(const Notebook& other);
    Notebook& operator=(const Notebook& other);
    ~Notebook();

    void setTitle(const char* title);

    bool appendToPage(size_t index, const char* text);
    void markPageAsImportant(size_t index);

    const Page& getPage(size_t index) const;

    const char* getTitle() const;
    size_t getPagesCount() const;
};

void printNotebook(const Notebook& notebook, std::ostream& os = std::cout);
