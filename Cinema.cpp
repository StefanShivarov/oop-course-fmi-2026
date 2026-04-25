#include "Cinema.h"

void Cinema::copyDynamicMemory(const Cinema& other) {
    this->name = new char[std::strlen(other.name) + 1];
    std::strcpy(this->name, other.name);

    this->projections = new Projection[other.capacity];
    for (int i = 0; i < other.size; i++) {
        this->projections[i] = other.projections[i];
    }
}

void Cinema::freeDynamicMemory() {
    delete[] name;
    delete[] projections;
}

void Cinema::resize() {
    this->capacity *= 2;

    Projection* newProjections = new Projection[this->capacity];
    for (int i = 0; i < size; i++) {
        newProjections[i] = this->projections[i];
    }

    delete[] projections;
    projections = newProjections;
}

Cinema::Cinema(const char* name) : size(0), capacity(4) {
    this->name = new char[std::strlen(name) + 1];
    std::strcpy(this->name, name);

    this->projections = new Projection[this->capacity];
}

Cinema::Cinema(const Cinema & other) : size(other.size), capacity(other.capacity) {
    copyDynamicMemory(other);
}

Cinema& Cinema::operator=(const Cinema & other) {
    if (this != &other) {
        this->size = other.size;
        this->capacity = other.capacity;

        freeDynamicMemory();
        copyDynamicMemory(other);
    }

    return *this;
}

Cinema::~Cinema() {
    freeDynamicMemory();
}

void Cinema::addProjection(const Projection& projection) {
    if (size == capacity) resize();

    projections[size++] = projection;
}

void Cinema::removeProjection(unsigned id) {
    for (int i = 0; i < size; i++) {
        if (id == projections[i].getId()) {
            for (int j = i; j < size - 1; j++) {
                projections[j] = projections[j + 1];
            }

            size--;
            return;
        }
    }
}

void Cinema::displayProjections() const {
    std::cout << "\n=======================\n";
    std::cout << "Cinema \"" << this->name << "\"\n";
    std::cout << "=======================\n\n";
    for (int i = 0; i < size; i++) {
        projections[i].displayInformation();
    }
}
