#include "Student.h"

int main() {
    //...
    Student stefo("Stefo");
    stefo.addGrade(5.50);
    stefo.addGrade(6.00);
    stefo.addGrade(3.25);
    printStudent(stefo);

    {
        Student stefoCopy = stefo;
        stefoCopy.addGrade(6.00);
        printStudent(stefoCopy);
    }

    printStudent(stefo);
}
