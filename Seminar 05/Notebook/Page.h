#pragma once
#include <iostream>

class Page {
private:
    char* textContent = nullptr;
    size_t length = 0;
    bool important = false;

    void copyFrom(const Page& other);
    void free();
    void setTextContent(const char* textContent);

public:
    Page();
    explicit Page(const char* textContent, bool isImportant = false);
    Page(const Page& other);
    Page& operator=(const Page& other);
    ~Page();

    bool append(const char* text);
    void markAsImportant();

    const char* getTextContent() const;
    bool isImportant() const;
};

void printPage(const Page& page, std::ostream& os = std::cout);
