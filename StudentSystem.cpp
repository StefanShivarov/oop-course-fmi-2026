// StudentSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Course.h"
#include "Student.h"
#include "AdmissionService.h"
#include "MinimumCreditsRequirement.h"

int main()
{
    Course oop( "OOP", 6, CourseType::Programming,true);

    Course dsa("DSA", 6,CourseType::Programming, true);

    Student student("12345", "Ivan Ivanov", 4.20);

    student.addCourse(oop);
    student.addCourse(dsa);

    AdmissionService service;

    service.addRequirement( std::make_shared<MinimumCreditsRequirement>(240));

    AdmissionResult result = service.checkAdmission(student);

    if (result.isAdmitted())
    {
        std::cout<< "Student is admitted.\n";
    }
    else
    {
        std::cout<< "Student is NOT admitted:\n";

        for (const auto& msg : result.getMessages())
        {
            std::cout << "- "  << msg << std::endl;
        }
    }

    return 0;
}


