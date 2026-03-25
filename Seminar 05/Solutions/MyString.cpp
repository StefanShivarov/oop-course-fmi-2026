//
// Created by Boris Bozhilov on 3/24/2026.
//

#include "MyString.h"

#include <cstring>
#include <iostream>

MyString::MyString() : string(nullptr) {
}

MyString::MyString(const char *string) : string(nullptr) {

    initializeStringData(this->string, string);
}

MyString::MyString(const MyString &other) : string(nullptr) {

    initializeStringData(this->string, other.string);
}

MyString& MyString::operator=(const MyString &other) {
    if (this == &other) return *this;

    freeStringData(string);

    initializeStringData(string, other.string);

    return *this;
}

MyString::~MyString() {

    freeStringData(string);
}

unsigned int MyString::getLength() const {

    if (string == nullptr) return -1;
    if (string[0] = '\0') return 0;

    return strlen(string);
}

void MyString::print() const {

    std::cout << string;
}

const char *MyString::getString() const {

    return string;
}

bool MyString::operator==(const MyString &other) const {

    if (this->string == nullptr) return false;
    if (other.string == nullptr) return false;

    if (this == &other) return true;

    if (this->string == other.string) return true;

    if (strlen(this->string) != strlen(other.string)) return false;

    return (strcmp(this->string, other.string) == 0);
}


void MyString::initializeStringData(char* &destination, const char *source) {

    if (source == nullptr) return;
    if (destination != nullptr) return;

    const unsigned int length = strlen(source);
    destination = new char[length + 1];

    strncpy(destination, source, length);
    destination[length] = '\0';
}

void MyString::freeStringData(char* &data) {
    delete[] data;
    data = nullptr;
}