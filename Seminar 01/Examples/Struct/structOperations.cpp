#include <iostream>
#include <cstring>

using namespace std;

struct Student {
    char name[32];
    int fn;
    double grade;

    void print() const {
        cout << name << " | FN: " << fn << " | grade: " << grade << "\n";
    }

    void sayHi() const {
        cout << "Hi, my name is " << name << "!\n";
    }

    // sneak peek into setters and member functions, we will look into this next week
    void setName(const char* newName) {
        int len = strlen(newName);
        if (len >= 32) {
            return;
        }
        strcpy(name, newName);
        name[len] = '\0';
    }
};

void readStudent(Student& s) {
    cin.getline(s.name, 32);
    cin >> s.name >> s.fn >> s.grade;
}

double averageGrade(const Student* arr, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += arr[i].grade;
    }
    return (n > 0) ? (sum / n) : 0.0;
}

int main() {
    // 1) Creation + setting properties
    Student a;                    // uninitialized fields
    a.setName("Ivan");
    a.fn = 12345;
    a.grade = 5.50;
    a.print();

    // 2) Initialization with aggregate init
    Student b = { "Maria", 23456, 6.00 };
    b.print();

    // 3) Struct with a pointer (dynamically allocated struct)
    Student* p = new Student{ "Georgi", 34567, 4.25 };
    p->print();
    p->grade = 4.75;              // using -> to access members through pointer
    (*p).fn = 99999;              // equivalent access with dereference
    p->print();
    delete p; // deleting dynamically allocated student from heap

    // 4) Array of structs (stack)
    Student group[3] = {
        { "Stefo", 11111, 3.00 },
        { "Serhan", 22222, 5.50 },
        { "Emil", 33333, 5.75 }
    };

    // 5) Dynamic array of structs
    int n;
    cout << "\nEnter n: ";
    cin >> n;

    Student* dynamicArr = new Student[n]; // n empty students in heap
    cout << "Enter n students: name fn grade\n";
    for (int i = 0; i < n; i++) {
        readStudent(dynamicArr[i]);
    }

    cout << "\nDynamic array:\n";
    for (int i = 0; i < n; i++) {
        dynamicArr[i].print();
    }
    cout << "Average: " << averageGrade(dynamicArr, n) << "\n";

    delete[] dynamicArr; // we still need to delete dynamically allocated resources

    // 6) Nested structs (struct containing another struct)
    struct Date {
        int day, month, year;
    };

    struct CourseRecord {
        Student student;
        Date examDate;

        void print() const {
            student.print();
            std::cout << "Exam date: "
                      << examDate.day << "." << examDate.month << "." << examDate.year
                      << "\n";
        }
    };

    // creating nested structs
    CourseRecord rec = { { "Rumen", 44444, 5.25 }, { 16, 2, 2026 } };
}
