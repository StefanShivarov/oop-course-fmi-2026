#pragma once

class Notebook
{
private:
    char *title = nullptr;
    char **textOnPage = nullptr;
    int pages = 0;
    int importantPagesStorage = 0;
    void freeMemory();
    void copyFrom(const Notebook &other);
    bool pageCheck(int page);

public:
    Notebook();
    Notebook(const char *title, const char **textOnPage, const int pages, const int importantPagesStorage);
    Notebook(const Notebook &other);
    Notebook &operator=(const Notebook &other);
    ~Notebook();
    void writeMoreToPage(const int page, const char *text);
    void markPageAsImportant(const int page);
    void print();
};