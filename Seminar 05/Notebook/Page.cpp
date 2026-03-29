#include "Page.h"
#include <iostream>
#include <cstring>
#pragma warning(disable: 4996)

void Page::setTextContent(const char* textContent) {
    if (!textContent) {
        this->textContent = new char[1];
        this->textContent[0] = '\0';
        length = 0;
        return;
    }

    length = strlen(textContent);
    this->textContent = new char[length + 1];
    strcpy(this->textContent, textContent);
}

void Page::copyFrom(const Page& other) {
    setTextContent(other.textContent);
    important = other.important;
}

void Page::free() {
    delete[] textContent;
    textContent = nullptr;
    length = 0;
}

Page::Page() : Page("") {}

Page::Page(const char* textContent, bool isImportant) : important(isImportant) {
    setTextContent(textContent);
}

Page::Page(const Page& other) {
    copyFrom(other);
}

Page& Page::operator=(const Page& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Page::~Page() {
    free();
}

bool Page::append(const char* text) {
    if (!text) {
        return false;
    }

    size_t addedLength = strlen(text);
    char* newText = new char[length + addedLength + 1];
    strcpy(newText, textContent);
    strcat(newText, text);

    delete[] textContent;
    textContent = newText;
    length += addedLength;

    return true;
}

void Page::markAsImportant() {
    important = true;
}

const char* Page::getTextContent() const {
    return textContent;
}

bool Page::isImportant() const {
    return important;
}

void printPage(const Page& page, std::ostream& os) {
    os << "Content: " << page.getTextContent() << '\n';
    os << "Important: " << (page.isImportant() ? "yes" : "no") << '\n';
}
