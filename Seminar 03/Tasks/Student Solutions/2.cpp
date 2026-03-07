#include <iostream>
#include "classDate.h"

class Result
{
private:
    unsigned int grade = 2;
    Date date;

public:
    unsigned int getGrade() const
    {
        return grade;
    }
    Date getDate() const
    {
        return date;
    }
    void setDate(const Date date)
    {
        this->date = date;
    }
    bool setGrade(const unsigned int grade)
    {
        if (grade > 1 && grade <= 6)
        {
            this->grade = grade;
            return true;
        }
        else
            return false;
    }
    void printResult() const
    {
        std::cout << "\nResult:";
        this->date.printDate();
        std::cout << "\nGrade: " << this->grade;
    }
    Result()
    {
    }
    Result(unsigned int grade, Date date)
    {
        if (!setGrade(grade))
        {
            grade = 2;
        }
        this->date = date;
    }
};

class StudentResults
{
private:
    Result *results = nullptr;
    size_t size = 1;
    size_t occupied = 0;

public:
    StudentResults() : size(1), occupied(0)
    {
        results = new Result[size];
    }
    StudentResults(size_t size) : size(size), occupied(0)
    {
        results = new Result[size];
    }
    ~StudentResults()
    {
        delete[] results;
    }
    void addNewResult(Result newResult)
    {
        if (occupied >= size)
        {
            size_t newSize = size * 2;
            Result *newArray = new Result[newSize];
            for (int i = 0; i < size; i++)
            {
                newArray[i] = results[i];
            }
            size = newSize;
            delete[] results;
            results = newArray;
        }
        *(results + occupied) = newResult;
        occupied++;
    }

    void printAllResults() const
    {
        for (int i = 0; i < occupied; i++)
        {
            results[i].printResult();
        }
    }
    void printBestResult() const
    {
        if (occupied == 0)
        {
            std::cout << "No results.";
        }
        else
        {
            Result max = results[0];
            for (int i = 1; i < occupied; i++)
            {
                if (max.getGrade() < results[i].getGrade())
                {
                    max = results[i];
                }
            }
            max.printResult();
        }
    }
    double averageGrade() const
    {
        if (occupied == 0)
        {
            return 0.0;
        }
        double sum = 0;
        for (int i = 0; i < occupied; i++)
        {
            sum += results[i].getGrade();
        }
        return sum / occupied;
    }
};

int main()
{
    Date d(2, 4, 1980);
    Result result1(3, d);
    Result result2(5, d);
    StudentResults student;
    for (int i = 0; i < 100; i++)
    {
        student.addNewResult(result1);
    }
    student.addNewResult(result2);
    for (int i = 0; i < 43; i++)
    {
        student.addNewResult(result1);
    }
    // student.printAllResults();
    student.printBestResult();
    std::cout << "\nAverage:" << student.averageGrade();
}