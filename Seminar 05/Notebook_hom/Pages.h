#pragma once
class Pages {
    char *text;
    bool isImportant;
    void free();
    void copyFrom(const Pages& other);
    public:
    Pages();
    Pages(const char* newText,bool important= false);
    Pages(const Pages& other);
    Pages& operator=(const Pages& other);
    ~Pages();
    void setPageAsImportant();
    void print() const;
    void append(const char* anotherText);



};
