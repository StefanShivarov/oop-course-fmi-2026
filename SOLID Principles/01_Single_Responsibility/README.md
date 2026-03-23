# Single Responsibility Principle


**Single Responsibility Principle** от SOLID принципите казва, че един клас трябва да има **само една причина да се променя**
или *„един клас трябва да има само една отговорност“*.

Тоест, ако един клас едновременно:

- държи бизнес данни;
- валидира вход;
- печата на конзолата;
- сериализира към файл;
- десериализира от поток;

тогава той вече обслужва няколко различни аспекта на системата. Това обикновено води до:

- трудна поддръжка
- силно обвързан код
- трудни unit тестове
- неясни граници между домейн логика и I/O логика

Това се среща много често, защото понякога е изкушаващо да сложим „още една удобна функция“ вътре в класа.

---

## Интуиция

Да кажем, че имаме клас `Student`.

Ако класът се променя, когато:

- се промени моделът на данните за студент;
- се промени форматът на принтиране;
- се промени файловият формат;
- се промени начинът на четене от поток;

значи имаме **няколко причини за промяна** и съответно нарушаваме SRP.

---

### Лош пример: един клас прави твърде много

```cpp
#include <iostream>
#include <cstring>

class Student {
private:
    char* name = nullptr;
    unsigned fn = 0;
    double grade = 0.0;

    void copyFrom(const Student& other) {
        name = new char[std::strlen(other.name) + 1];
        std::strcpy(name, other.name);
        fn = other.fn;
        grade = other.grade;
    }

    void free() {
        delete[] name;
        name = nullptr;
    }

public:
    Student() {
        name = new char[1];
        name[0] = '\0';
    }

    Student(const char* name, unsigned fn, double grade) {
        this->name = new char[std::strlen(name) + 1];
        std::strcpy(this->name, name);
        this->fn = fn;
        this->grade = grade;
    }

    Student(const Student& other) {
        copyFrom(other);
    }

    Student& operator=(const Student& other) {
        if (this != &other) {
            free();
            copyFrom(other);
        }
        return *this;
    }

    ~Student() {
        free();
    }

    void print() const {
        std::cout << "Student: " << name
                  << ", fn: " << fn
                  << ", grade: " << grade << '\n';
    }

    void serialize(std::ostream& os) const {
        os << name << '\n' << fn << '\n' << grade << '\n';
    }

    void deserialize(std::istream& is) {
        char buffer[1024];
        is.getline(buffer, 1024);

        delete[] name;
        name = new char[std::strlen(buffer) + 1];
        std::strcpy(name, buffer);

        is >> fn >> grade;
        is.ignore();
    }
};
```

### Какъв е проблемът тук

Този клас има поне няколко роли:

1. **Представя студент** като обект от домейна.
2. **Знае как да се визуализира** на конзолата.
3. **Знае как да се записва** във външен формат.
4. **Знае как да се чете** от външен формат.

Тоест, `Student` не е просто домейн модел. Той е и formatter, и serializer, и parser.

---

### Защо функцията `print()` често е подозрителна

Член-функция като:

```cpp
void print() const;
```

изглежда удобна, но често смесва:

- състоянието на обекта;
- начина, по който искаме да го представим.

Проблемите са няколко:

- Ако утре искаме различен формат за конзолата, класът се променя.
- Ако искаме различни формати на принтиране (кратко, подробно, table row, json), пак класът се променя.

---

## По-добър вариант №1: отделяме представянето от данните

```cpp
#include <iostream>
#include <cstring>

class Student {
private:
    char* name = nullptr;
    unsigned fn = 0;
    double grade = 0.0;

    void copyFrom(const Student& other) {
        name = new char[std::strlen(other.name) + 1];
        std::strcpy(name, other.name);
        fn = other.fn;
        grade = other.grade;
    }

    void free() {
        delete[] name;
        name = nullptr;
    }

public:
    Student() {
        name = new char[1];
        name[0] = '\0';
    }

    Student(const char* name, unsigned fn, double grade) {
        this->name = new char[std::strlen(name) + 1];
        std::strcpy(this->name, name);
        this->fn = fn;
        this->grade = grade;
    }

    Student(const Student& other) {
        copyFrom(other);
    }

    Student& operator=(const Student& other) {
        if (this != &other) {
            free();
            copyFrom(other);
        }
        return *this;
    }

    ~Student() {
        free();
    }

    const char* getName() const { return name; }
    unsigned getFn() const { return fn; }
    double getGrade() const { return grade; }
};

void printStudent(std::ostream& os, const Student& st) {
    os << "Student: " << st.getName()
       << ", fn: " << st.getFn()
       << ", grade: " << st.getGrade() << '\n';
}
```

## Защо е по-добре

Сега `Student` се грижи само за това да бъде `Student`.  
Функцията `printStudent` се грижи за представянето.

Така:

- форматът може да се променя без да пипаме класа;
- разделяме домейн модела от I/O логиката.

В случая още по-естествен вариант би бил вместо printStudent функцията да предефинираме `operator<<` за обекти от класа Student.

---

### `serialize()` / `deserialize()` вътре в класа — защо също може да е проблем

Да видим този тип интерфейс:

```cpp
void serialize(std::ostream& os) const;
void deserialize(std::istream& is);
```

Той не е автоматично „лош“, но често е сигнал, че:

- класът знае прекалено много за външния формат;
- класът става зависим от конкретен механизъм за съхранение;
- смесваме домейн модел с input / output логика

Особено ако по-късно се появят:

- текстов формат
- бинарен формат
- CSV
- различни входни източници

тогава класът започва да расте в грешната посока.

---

## По-добър вариант №2: външен serializer / parser

```cpp
#include <iostream>
#include <cstring>
#include <stdexcept>

class Student {
private:
    char* name = nullptr;
    unsigned fn = 0;
    double grade = 0.0;

    void copyFrom(const Student& other) {
        name = new char[std::strlen(other.name) + 1];
        std::strcpy(name, other.name);
        fn = other.fn;
        grade = other.grade;
    }

    void free() {
        delete[] name;
        name = nullptr;
    }

public:
    Student() {
        name = new char[1];
        name[0] = '\0';
    }

    Student(const char* name, unsigned fn, double grade) {
        this->name = new char[std::strlen(name) + 1];
        std::strcpy(this->name, name);
        this->fn = fn;
        this->grade = grade;
    }

    Student(const Student& other) {
        copyFrom(other);
    }

    Student& operator=(const Student& other) {
        if (this != &other) {
            free();
            copyFrom(other);
        }
        return *this;
    }

    ~Student() {
        free();
    }

    const char* getName() const { return name; }
    unsigned getFn() const { return fn; }
    double getGrade() const { return grade; }
};

class StudentTextSerializer {
public:
    static void serialize(std::ostream& os, const Student& st) {
        os << st.getName() << '\n'
           << st.getFn() << '\n'
           << st.getGrade() << '\n';
    }

    static Student deserialize(std::istream& is) {
        char buffer[1024];
        unsigned fn;
        double grade;

        if (!is.getline(buffer, 1024)) {
            throw std::runtime_error("Could not read name");
        }

        if (!(is >> fn >> grade)) {
            throw std::runtime_error("Could not read fn/grade");
        }

        is.ignore();
        return Student(buffer, fn, grade);
    }
};
```

### Какво печелим

- `Student` няма нужда да знае как изглежда текстовият формат.
- Ако форматът се смени, променяме serializer-а, не самия модел.
- Можем да имаме няколко serializer-а:

```cpp
class StudentBinarySerializer;
class StudentCsvSerializer;
```

Това е много по-скалируемо.

---

## По-добър вариант №3: отделяме четенето и записването на различни отговорности

Понякога дори `serialize` и `deserialize` заедно в един helper клас може да са твърде много, ако проектът е по-голям.

```cpp
class StudentWriter {
public:
    static void writeText(std::ostream& os, const Student& st) {
        os << st.getName() << '\n'
           << st.getFn() << '\n'
           << st.getGrade() << '\n';
    }
};

class StudentReader {
public:
    static Student readText(std::istream& is) {
        char buffer[1024];
        unsigned fn;
        double grade;

        if (!is.getline(buffer, 1024)) {
            throw std::runtime_error("Invalid input: name");
        }

        if (!(is >> fn >> grade)) {
            throw std::runtime_error("Invalid input: fn/grade");
        }

        is.ignore();
        return Student(buffer, fn, grade);
    }
};
```

Това е полезно, когато:

- четенето и записването се развиват различно
- имат различни правила за валидиране
- имат различни формати или зависимости

---

## SRP и ООП

Понякога хората си мислят:

> „Щом нещо е свързано със Student, то трябва да е вътре в класа Student.“

Това не е добра ООП интуиция.

В ООП не е задължително всичко, което „работи със Student“, да бъде член на `Student`.  
Често е по-добре:

- данните и инвариантите да са в класа;
- операциите за вход/изход, форматиране, persistence и parsing да са извън него.

Тоест доброто ООП не означава „максимално много member functions“, а **добре разпределени отговорности**.

---

### Ползи от спазването на SRP

- Класовете са по-малки и по-ясни
- Промените са по-локализирани
- Кодът е по-лесен за тестване
- По-лесно добавяме нови функционалности
- Намаляваме coupling-а между домейн логика и инфраструктурна логика

---

### Недостатък на прекаленото раздробяване

Все пак има и другата крайност:

- твърде много дребни класове;
- твърде много indirection;
- кодът става по-труден за навигация.

Затова добрият въпрос не е:

> „Мога ли да извадя още една функция извън класа?“

а:

> „Има ли отделна причина този код да се променя независимо от останалото?“
