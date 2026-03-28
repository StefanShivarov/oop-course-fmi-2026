#include "Student.h"
#include <iostream>
#include <cstring>
#pragma warning(disable:4996)

void Student::copyFrom(const Student& other) {
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);

    gradesCount = other.gradesCount;
    gradesCapacity = other.gradesCapacity;

    grades = new double[gradesCount];
    for (size_t i = 0; i < gradesCount; i++) {
        grades[i] = other.grades[i];
    }
}

void Student::resizeGrades(size_t newCap) {
    double* resizedGrades = new double[newCap];
    for (size_t i = 0; i < gradesCount; i++) {
        resizedGrades[i] = grades[i];
    }
    delete[] grades;
    grades = resizedGrades;
    gradesCapacity = newCap;
}

void Student::free() {
    delete[] name;
    delete[] grades;

    name = nullptr;
    grades = nullptr;
    gradesCount = 0;
    gradesCapacity = 0;
}

Student::Student() : Student("undefined") {}

Student::Student(const char* name) : gradesCount(0), gradesCapacity(INITIAL_CAPACITY) {
    setName(name);
    this->grades = new double[gradesCapacity];
}

Student::Student(const Student& other) : gradesCount(other.gradesCount), gradesCapacity(other.gradesCapacity) {
    copyFrom(other);
}

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Student::~Student() {
    free();
}

const char* Student::getName() const {
    return name;
}

const double* Student::getGrades() const {
    return grades;
}

size_t Student::getGradesCount() const {
    return gradesCount;
}

bool Student::setName(const char* name) {
    if (name == nullptr) {
        return false;
    }
    delete[] this->name;
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    return true;
}

void Student::addGrade(double grade) {
    if (gradesCount >= gradesCapacity) {
        resizeGrades(gradesCapacity + INITIAL_CAPACITY);
    }
    grades[gradesCount++] = grade;
}

void printStudent(const Student& student, std::ostream&) {
    std::cout << "Name: " << student.getName() << '\n';
    std::cout << "Grades: ";
    size_t gradesCount = student.getGradesCount();
    const double* grades = student.getGrades();
    for (size_t i = 0; i < gradesCount; i++) {
        std::cout << grades[i] << ' ';
    }
    std::cout << "Average grade: " << student.getAverageGrade() << '\n';
}

double Student::getAverageGrade() const {
    if (grades == nullptr || gradesCount == 0) {
        return 0.0;
    }
    double sum = 0.0;
    for (size_t i = 0; i < gradesCount; i++) {
        sum += grades[i];
    }
    return sum / (double) gradesCount;
}
