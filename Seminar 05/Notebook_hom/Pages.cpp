#include "Pages.h"
#include<iostream>


void Pages::free(){
    delete[] text;
    text = nullptr;
    isImportant = false;
}

void Pages::copyFrom(const Pages &other) {
    text = new char[strlen(other.text)+1];
    isImportant = other.isImportant;
}


Pages::Pages() {
    text = new char[1];
    text[0] ='\0';
    isImportant = false;
}

Pages::Pages(const char *newText, bool important) {
    text = new char[strlen(text)+1];
    strcpy(text,newText);
    isImportant = important;
}

Pages::Pages(const Pages &other) {
    copyFrom(other);
}

Pages & Pages::operator=(const Pages &other) {
    if (this == &other) {
        return *this;
    }
    free();
    copyFrom(other);
    return *this;
}

Pages::~Pages() {
    free();
}

void Pages::setPageAsImportant() {
    isImportant = true;
}

void Pages::print() const {
    if (isImportant) {
        std::cout <<"Important" << std::endl;
    }
    std::cout << text << std::endl;
}

void Pages::append(const char *anotherText) {
    int newLen = strlen(text)+strlen(anotherText);
    char *newText = new char[newLen+1];
    strcpy(newText,text);
    strcat(newText,anotherText);
    delete[] text;
    text = newText;
}
