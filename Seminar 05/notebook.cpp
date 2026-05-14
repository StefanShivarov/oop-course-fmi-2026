#include "notebook.h"
#include <iostream>
#include <cstring>
Notebook::Notebook()
{
}
void Notebook::copyFrom(const Notebook &other)
{
    if (other.title != nullptr)
    {
        title = new char[std::strlen(other.title) + 1];
        std::strcpy(title, other.title);
    }
    else
    {
        title = nullptr;
    }
    textOnPage = new char *[other.pages];
    for (int i = 0; i < other.pages; i++)
    {
        if (other.textOnPage[i] != nullptr)
        {
            textOnPage[i] = new char[std::strlen(other.textOnPage[i]) + 1];
            std::strcpy(textOnPage[i], other.textOnPage[i]);
        }
        else
        {
            textOnPage[i] = nullptr;
        }
    }
    pages = other.pages;
    importantPagesStorage = other.importantPagesStorage;
}
Notebook &Notebook::operator=(const Notebook &other)
{
    if (this != &other)
    {
        freeMemory();
        copyFrom(other);
    }
    return *this;
}
Notebook::Notebook(const Notebook &other)
{
    copyFrom(other);
}

Notebook::Notebook(const char *title, const char **textOnPage, const int pages, const int importantPagesStorage) : pages(pages), importantPagesStorage(importantPagesStorage)
{
    this->title = new char[std::strlen(title) + 1];
    std::strcpy(this->title, title);
    this->textOnPage = new char *[pages];
    for (int i = 0; i < pages; i++)
    {
        this->textOnPage[i] = new char[std::strlen(textOnPage[i]) + 1];
        std::strcpy(this->textOnPage[i], textOnPage[i]);
    }
}
Notebook::~Notebook()
{
    freeMemory();
}
void Notebook::freeMemory()
{
    for (int i = 0; i < pages; i++)
    {
        delete[] textOnPage[i];
    }
    delete[] textOnPage;
    delete[] title;
}

void Notebook::writeMoreToPage(const int page, const char *text)
{
    if (!pageCheck(page))
    {
        return;
    }
    char *newText = new char[strlen(textOnPage[page]) + strlen(text) + 1];
    std::strcpy(newText, textOnPage[page]);
    std::strcat(newText, text);
    delete[] textOnPage[page];
    textOnPage[page] = newText;
}

bool Notebook::pageCheck(int page)
{
    if (page < 0 || page >= pages)
    {
        std::cout << "Page does not exist";
        return false;
    }
    return true;
}
void Notebook::markPageAsImportant(int page)
{
    if (!pageCheck(page))
    {
        return;
    }
    importantPagesStorage |= (1 << page);
}

void Notebook::print()
{
    std::cout << title;
    for (int i = 0; i < pages; i++)
    {
        std::cout << "\nPage " << i << " :\n";
        if (importantPagesStorage & (1 << i))
        {
            std::cout << "IMPORTANT!\n";
        }
        std::cout << textOnPage[i];
        std::cout << "\n";
    }
}
