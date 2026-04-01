#include <iostream>
using namespace std;

class Page {
    char* content = nullptr;
    bool isImportant = false;
    public:
    Page() = default;
    Page(const char* content, const bool isImportant) : isImportant(isImportant) {
        this -> content = new char[strlen(content) + 1];
        strcpy(this -> content, content);
    }
    Page(const Page& other) : isImportant(other.isImportant) {
        if (other.content) {
            this -> content = new char[strlen(other.content) + 1];
            strcpy(this -> content, other.content);
        }
        else {
            this -> content = nullptr;
        }
    }
    Page& operator=(const Page& other) {
        if (this != &other) {
            delete[] content;
            if (other.content) {
                this -> content = new char[strlen(other.content) + 1];
                strcpy(this -> content, other.content);
            }
            else {
                this -> content = nullptr;
            }
            this -> isImportant = other.isImportant;
        }
        return *this;
    }
    ~Page() {
        delete[] content;
    }
    const char* getContent() const {
        return this -> content;
    }
    void setContent(const char* newContent) {
        delete[] content;
        this -> content = new char[strlen(newContent) + 1];
        strcpy(this -> content, newContent);
    }
    bool getImportancy() const {
        return this -> isImportant;
    }
    void setImportancy(const bool newImportancy) {
        this -> isImportant = newImportancy;
    }
};
class Notebook {
    char* subject = nullptr;
    Page* pages = nullptr;
    int pageCount{};
    public:
    Notebook(const char* subject, const int pageCount) : pageCount(pageCount) {
        this -> subject = new char[strlen(subject) + 1];
        strcpy(this -> subject, subject);
        this -> pages = new Page[pageCount];
    }
    Notebook(const Notebook& other) : pageCount(other.pageCount) {
        if (other.subject) {
            this -> subject = new char[strlen(other.subject) + 1];
            strcpy(this -> subject, other.subject);
        }
        else {
            this -> subject = nullptr;
        }
        if (other.pages) {
            this -> pages = new Page[other.pageCount];
            for (int i = 0; i < other.pageCount; i++) {
                this -> pages[i] = other.pages[i];
            }
        }
        else {
            this -> pages = nullptr;
        }
    }
    Notebook& operator=(const Notebook& other) {
        if (this != &other) {
            delete[] subject;
            delete[] pages;
            this -> pageCount = other.pageCount;
            if (other.subject) {
                this -> subject = new char[strlen(other.subject) + 1];
                strcpy(this -> subject, other.subject);
            }
            else {
                this -> subject = nullptr;
            }
            if (other.pages) {
                this -> pages = new Page[other.pageCount];
                for (int i = 0; i < other.pageCount; i++) {
                    this -> pages[i] = other.pages[i];
                }
            }
            else {
                this -> pages = nullptr;
            }
        }
        return *this;
    }
    Notebook() = default;
    ~Notebook() {
        delete[] subject;
        delete[] pages;
    }
    bool addPage(const Page& page, const int pageNumber) {
        if (pageNumber > pageCount - 1 || pageNumber < 0) {
            return false;
        }
        pages[pageNumber] = page;
        return true;
    }
    bool append(const char* s, const int pageNumber) {
        if (pageNumber > pageCount - 1 || pageNumber < 0) {
            return false;
        }
        const auto newPage = new char[strlen(s) + strlen(pages[pageNumber].getContent()) + 1];
        strcpy(newPage, pages[pageNumber].getContent());
        strcat(newPage, s);
        pages[pageNumber].setContent(newPage);
        delete[] newPage;
        return true;
    }
    void print() {
        println("{} - {} pages", subject, pageCount);
        for (int i = 0; i < pageCount; i++) {
            if (pages[i].getImportancy()) {
                println("{} - !", pages[i].getContent());
            }
            else {
                println("{}", pages[i].getContent());
            }
        }
    }
    bool toggleImportancy(const int pageNumber) {
        if (pageNumber > pageCount - 1 || pageNumber < 0) {
            return false;
        }
        if (pages[pageNumber].getImportancy()) {
            pages[pageNumber].setImportancy(false);
        }
        else {
            pages[pageNumber].setImportancy(true);
        }
        return true;
    }
};
int main() {
    const Page p1("chapter1", false);
    const Page p2("chapter2", true);
    const Page p3("chapter3", false);
    const Page p4("chapter4", true);
    const Page p5("chapter5", false);
    Notebook book1("UP", 5);
    book1.addPage(p1, 0);
    book1.addPage(p2, 1);
    book1.addPage(p3, 2);
    book1.addPage(p4, 3);
    book1.addPage(p5, 4);
    book1.print();
    Notebook book2 = book1;
    book2.append("rumen", 4);
    book2.print();
    book1.toggleImportancy(0);
    book1.print();
}