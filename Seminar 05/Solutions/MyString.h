//
// Created by Boris Bozhilov on 3/24/2026.
//

#ifndef OOP_COURSE_FMI_2026_MYSTRING_H
#define OOP_COURSE_FMI_2026_MYSTRING_H


class MyString {

private:
    char* string;

    static void initializeStringData(char* &destination, const char* source);
    static void freeStringData(char* &data);

public:

    MyString();
    MyString(const char* string);

    MyString(const MyString &other);
    MyString& operator=(const MyString &other);

    ~MyString();

    void print() const;
    unsigned int getLength() const;
    const char* getString() const;

    bool operator==(const MyString &other) const;
};


#endif //OOP_COURSE_FMI_2026_MYSTRING_H