#include <iostream>
#include <string>
#include <print>
using namespace std;

class Date
{
private:
    int day;
    int month;
    int year;
public:
    ~Date() = default;
    Date() = default;
    Date(int d, int m, int y)
    {
        day = d;
        month = m;
        year = y;
    }
    void printDate() const
    {
        println("{}.{}.{}",day, month, year);
    }
};
class Exam
{
private:
    Date date;
    string subject;
    double grade;
public:
    ~Exam() = default;
    Exam() = default;
    Exam(Date d, double g,string subj)
    {
        date = d;
        grade = g;
        subject = subj;
    }
    double getGrade() const
    {
        return grade;
    }
    void printExam() const
    {
        print("{} - {} - ",subject,grade);
        date.printDate();
    }
};
class StudentResults
{
private:
    int capacity;
    int count;
    Exam* exams;
public:
    ~StudentResults()
    {
        delete[] exams;
    }
    StudentResults()
    {
        capacity = 10;
        count = 0;
        exams = new Exam[capacity];
    }
    void printAllResults() const
    {
        for (int i = 0;i < count;i++)
        {
            exams[i].printExam();
        }
    }
    Exam findBestResult() const
    {
        int index = 0;
        double max = exams[0].getGrade();
        for (int i = 1;i < count;i++)
        {
            if (exams[i].getGrade() > max)
            {
                index = i;
                max = exams[i].getGrade();
            }
        }
        print("Best result: ");
        exams[index].printExam();
        return exams[index];
    }
    double findAverageResult() const
    {
        double average = 0;
        for (int i = 0;i < count;i++)
        {
            average += exams[i].getGrade();
        }
        average /= count;
        println("Average result is: {:.2f}", average);
        return average;

    }
    void addExam(Exam examToAdd)
    {
        if (count == capacity)
        {
            int newCapacity = capacity + 10;
            Exam* tempArray = new Exam[newCapacity];
            for (int i = 0;i < capacity;i++)
            {
                tempArray[i] = exams[i];
            }
            delete[] exams;
            exams = tempArray;
            capacity = newCapacity;
        }
        exams[count++] = examToAdd;
    }
    StudentResults(int n,Exam* examArr)
    {
        capacity = 10;
        count = 0;
        exams = new Exam[capacity];
        for (int i = 0;i < n;i++)
        {
            addExam(examArr[i]);
        }
    }
};
int main()
{
    StudentResults results;
    println("Adding 16 exams...");
    for (int i = 0;i < 16;i++)
    {
        Date date(i, 8, 2026);
        string subject = "Subject " + to_string(i);
        double grade = 2 + i * 0.25;
        Exam exam(date, grade, subject);
        results.addExam(exam);
    }  
    println("\n16 Exams added");
    println("\n---Printing all exams---");
    results.printAllResults();
    println("\n---Finding best result---");
    results.findBestResult();
    println("\n---Finding average result---");
    results.findAverageResult();
}
