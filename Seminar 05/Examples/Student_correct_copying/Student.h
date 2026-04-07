#pragma once
#include <iostream>

class Student {
private:
    char* name = nullptr;
    double* grades = nullptr;
    size_t gradesCount;
    size_t gradesCapacity;

    static constexpr size_t INITIAL_CAPACITY = 8;

    void copyFrom(const Student& other);
    void free();

    void resizeGrades(size_t newCap);

public:
    Student();
    explicit Student(const char* name);
    Student(const Student& other);
    Student& operator=(const Student& other);
    ~Student();

    const char* getName() const;
    bool setName(const char* name);

    const double* getGrades() const;
    void addGrade(double grade);

    size_t getGradesCount() const;

    double getAverageGrade() const;

};

void printStudent(const Student& student, std::ostream& os = std::cout);
