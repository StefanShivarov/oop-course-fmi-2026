# 11. Наследяване. Видове наследяване. Изключения(exceptions). Обработване на грешки и exception-и.

## Наследяване

Наследяването е механизъм, чрез който един клас се дефинира като разширение на друг клас. Класът, който се наследява, се нарича **base class** или **parent class**, а класът, който наследява, се нарича **derived class** или **child class**.

Когато даден клас наследи друг клас, обектите от наследения клас съдържат вътре в себе си част, която е обект от базовия клас. Тази част често се нарича **base subobject**. Това е важно, защото наследяването не е просто “копиране на методи” от един клас в друг. То създава реална структурна връзка между типовете: всеки обект от наследения тип има базова част, която се конструира, използва и разрушава по правилата на базовия клас.

```cpp
class Person {
public:
    void introduce() const {
        // ...
    }
};

class Student : public Person {
public:
    void study() const {
        // ...
    }
};

int main() {
    Student s;

    s.introduce(); // OK: introduce идва от Person
    s.study();     // OK: study е дефинирана в Student
}
```

В примера `Student` наследява `Person`. Това означава, че `Student` обектът съдържа `Person` част и допълнителна `Student` част.

Концептуално:

```text
Student object
+--------------------------+
| Person part              |
|   Person member data     |
|   Person member funcs    |
+--------------------------+
| Student part             |
|   Student member data    |
|   Student member funcs   |
+--------------------------+
```

Това обяснява защо върху `Student` можем да извикаме публични методи на `Person`: тези методи работят върху `Person` частта, която реално съществува вътре в `Student` обекта. Представянето в паметта много наподобява _композиция_.

---

### Защо използваме наследяване?

Наследяването се използва, когато искаме да изразим, че един тип е по-специален случай на друг тип. То е подходящо, когато между класовете има **is-a** отношение.

Примери:

```text
Student is a Person
Teacher is a Person
Circle is a Shape
Car is a Vehicle
```

Ако казваме, че `Student` наследява `Person`, ние казваме, че навсякъде, където има смисъл да работим с човек като обща концепция, студентът може да бъде разглеждан като такъв. Той има всички основни свойства и поведение на човек, но добавя и свои специфични данни и операции.

Наследяването е полезно, когато искаме:

- да отделим общото поведение в базов клас
- да избегнем повторение на еднакви член-данни и методи
- да изградим йерархия от по-общи към по-специализирани типове

Важно е обаче да не използваме наследяване само защото два класа имат някакъв общ код. Ако връзката между тях не е `is-a`, наследяването може да направи дизайна по-объркан. В такива случаи композицията често е по-добро решение.

---

### Наследяване не означава “вземи кода от друг клас”

Често в началото наследяването се възприема като начин да “преизползваме код”. Това е вярно донякъде, но е непълно обяснение. По-важното е, че наследяването създава връзка между типовете.

Например:

```cpp
class Engine {
public:
    void start() {}
};

class Car : public Engine {
    // Лош модел
};
```

Това може да ни позволи да извикаме `start()` върху `Car`, но моделът е грешен: колата **не е** двигател. Колата **има** двигател. Тук композицията е по-подходяща.

```cpp
class Engine {
public:
    void start() {}
};

class Car {
private:
    Engine engine;

public:
    void start() {
        engine.start();
    }
};
```

Наследяването трябва да описва правилна връзка между понятията, а не просто да се използва като shortcut за достъп до функции.

---

### Основна терминология

#### Base class / Parent class

Базовият клас е по-общият клас в йерархията. Той съдържа общите данни и поведение, които наследниците могат да използват или разширят.

```cpp
class Person {
    // общи неща за всички хора
};
```

#### Derived class / Child class

Наследеният клас е по-специализираният клас. Той съдържа базовата част и добавя специфични данни и функции.

```cpp
class Student : public Person {
    // специфични неща за студент
};
```

#### Generalization / Обобщение

Обобщението е процесът, при който забелязваме общи характеристики между няколко класа и ги изнасяме в по-общ базов клас.

```text
Student, Teacher, Assistant -> Person
```

Ако `Student`, `Teacher` и `Assistant` всички имат име, възраст и email, тези данни може да принадлежат в `Person`, а не да се повтарят във всеки клас.

#### Specialization / Специализация

Специализацията е обратната посока: започваме от по-общ клас и създаваме по-конкретни класове, които добавят специфично поведение или данни.

```text
Person -> Student
Person -> Teacher
```

Например `Student` може да има факултетен номер и оценки, а `Teacher` може да има катедра и списък от курсове.

#### Class hierarchy / Йерархия от класове

Йерархията показва как класовете са свързани чрез наследяване.

```text
Person
├── Student
└── Teacher
```

Колкото по-нагоре сме в йерархията, толкова по-обща е концепцията. Колкото по-надолу сме, толкова по-специализиран е типът.

---

### Наследяване vs. Kомпозиция

#### Наследяване

Наследяването описва `is-a` отношение. Ако `Student` наследява `Person`, казваме, че студентът е вид човек. Това позволява да използваме `Student` там, където очакваме `Person`, поне за операциите, които са част от интерфейса на `Person`.

```cpp
class Person {
private:
    std::string name;

public:
    explicit Person(std::string name)
        : name(std::move(name)) {}

    const std::string& getName() const {
        return name;
    }
};

class Student : public Person {
private:
    std::string facultyNumber;

public:
    Student(std::string name, std::string facultyNumber)
        : Person(std::move(name)),
          facultyNumber(std::move(facultyNumber)) {}

    const std::string& getFacultyNumber() const {
        return facultyNumber;
    }
};
```

Тук `Student` не просто използва `Person`; той е специален вид `Person`.

#### Композиция

Композицията описва `has-a` отношение. Един клас съдържа друг клас като член-данна.

```cpp
class Engine {
private:
    int horsepower = 0;

public:
    explicit Engine(int horsepower)
        : horsepower(horsepower) {}

    int getHorsepower() const {
        return horsepower;
    }
};

class Car {
private:
    std::string model;
    Engine engine;

public:
    Car(std::string model, Engine engine)
        : model(std::move(model)),
          engine(std::move(engine)) {}
};
```

`Car` не е `Engine`. `Car` има `Engine`. Затова композицията е правилният модел.


| Наследяване | Композиция |
|---|---|
| `is-a` отношение | `has-a` отношение |
| `Student is a Person` | `Car has an Engine` |
| Наследникът получава базова част | Класът съдържа друг обект като член-данна |
| Връзката между класовете е по-силна | Връзката е по-гъвкава и по-слаба |
| Подходящо за йерархии от типове | Подходящо за изграждане на сложни обекти от по-малки части |

Когато се колебаем между наследяване и композиция, добър въпрос е: “Мога ли смислено да кажа, че обектът от наследения клас **е** обект от базовия клас?” Ако отговорът е не, най-вероятно трябва композиция.

---

### Видове наследяване според броя базови класове

#### Single inheritance

При единичното наследяване един клас наследява точно един базов клас.

```cpp
class Person {
    // ...
};

class Student : public Person {
    // ...
};
```

Това е най-често срещаният и най-лесният за разбиране случай. Йерархията е ясна: `Student` има една базова част — `Person`.

#### Multiple inheritance

При множественото наследяване един клас наследява повече от един базов клас.

```cpp
class Printable {
public:
    void print() const {
        // ...
    }
};

class Identifiable {
public:
    int getId() const {
        return 0;
    }
};

class Document : public Printable, public Identifiable {
    // ...
};
```

Тук `Document` съдържа две базови части: една от `Printable` и една от `Identifiable`. Множественото наследяване може да бъде полезно, но лесно усложнява дизайна, особено ако базовите класове имат припокриващи се имена на функции или ако се появят по-сложни йерархии. Затова се използва внимателно и само когато моделът наистина го изисква.

---

### Видове наследяване според достъпа до член-данните

В C++ можем да наследим базов клас по три начина:

```cpp
class B : public A { };
class C : protected A { };
class D : private A { };
```

Този модификатор не променя факта, че `B`, `C` или `D` съдържат `A` част. Той променя **какъв достъп има външният код и наследниците до наследения интерфейс**.

При `class` наследяването по подразбиране е `private`.

```cpp
class B : A {
    // private inheritance по подразбиране
};
```

При `struct` наследяването по подразбиране е `public`.

```cpp
struct C : A {
    // public inheritance по подразбиране
};
```

Добра практика е да се пише модификаторът явно, дори когато съвпада с default поведението.

---

### Public inheritance

`public` наследяването запазва публичния интерфейс на базовия клас публичен и през наследника.

```cpp
class Person {
public:
    void introduce() const {
        // ...
    }
};

class Student : public Person {
public:
    void study() const {
        // ...
    }
};

int main() {
    Student s;
    s.introduce(); // OK
    s.study();     // OK
}
```

Това е видът наследяване, който най-често използваме за `is-a` отношение. Причината е, че ако `Student` наистина е `Person`, тогава публичните операции, които са позволени върху `Person`, трябва да са позволени и върху `Student`.

С други думи, публичното наследяване казва: “Наследникът може да бъде използван като базовия тип.” На този етап това се вижда най-вече при подаване на `Student` към функция, която приема `Person&` или `const Person&`.

---

### Protected inheritance

При `protected` наследяване публичните членове на базовия клас стават `protected` в наследника, а `protected` членовете остават `protected`.

```cpp
class A {
public:
    int x = 0;

protected:
    int y = 0;

private:
    int z = 0;
};

class B : protected A {
public:
    void f() {
        x = 1; // OK: x е protected в B
        y = 2; // OK
        // z = 3; // Error: z е private в A
    }
};

int main() {
    B obj;
    // obj.x = 10; // Error: x вече не е public през B
}
```

Това означава, че `B` може да използва публичния интерфейс на `A` вътрешно, но не го показва като публичен интерфейс към външния свят. Така protected наследяването казва: “Използвам базовия клас като част от имплементацията си и евентуално искам моите наследници да имат достъп до тази част, но не искам външен код да я вижда директно.”

На практика protected inheritance се среща по-рядко от public inheritance. Използва се в по-специфични дизайни, когато искаме да споделим имплементация надолу по йерархията, но не и да изложим интерфейса навън.

---

### Private inheritance

При `private` наследяване публичните и protected членовете на базовия клас стават private в наследника.

```cpp
class A {
public:
    void f() {}
};

class B : private A {
public:
    void g() {
        f(); // OK: B може да използва A::f вътрешно
    }
};

int main() {
    B obj;
    obj.g(); // OK
    // obj.f(); // Error: f не е public през B
}
```

Private inheritance обикновено не изразява `is-a` отношение. Ако `B` наследява `A` private, външният код не може да третира `B` като `A`. Това по-скоро означава, че `B` използва `A` като имплементационен детайл.

В много случаи композицията е по-ясна алтернатива на private inheritance:

```cpp
class B {
private:
    A a;

public:
    void g() {
        a.f();
    }
};
```

Композицията по-добре показва, че `A` е вътрешна част на `B`, а не базов тип. Затова private inheritance трябва да се използва само когато наистина има причина да се възползваме от механизма на наследяването, а не просто защото искаме да използваме някакви функции от друг клас.

---

## Таблица за достъп при наследяване

```cpp
class A {
public:
    int x;

protected:
    int y;

private:
    int z;
};
```

| Вид наследяване | `A::x` в наследника | `A::y` в наследника | `A::z` в наследника |
|---|---|---|---|
| `public A` | `public` | `protected` | недостъпен |
| `protected A` | `protected` | `protected` | недостъпен |
| `private A` | `private` | `private` | недостъпен |

Важно: `private` членове на базовия клас **съществуват** в обекта наследник, но не са директно достъпни от кода на наследника. Достъпът до тях става само чрез публични или protected функции на базовия клас.

Това разделение е важно за капсулацията. Ако наследникът можеше директно да променя private член-данните на базовия клас, базовият клас нямаше да може да пази собствените си инварианти. Затова C++ позволява на базовия клас да контролира какво точно да бъде видимо за наследниците чрез `protected`, а какво да остане напълно скрито чрез `private`.

---

### Какво се наследява и какво не?

Когато казваме, че клас наследява друг клас, това не означава, че всички неща от базовия клас стават обикновени членове на наследника по един и същи начин.

#### Наследяват се като част от базовата подобектна част:

- член-данните на базовия клас;
- член-функциите на базовия клас;
- публичният и protected интерфейс според вида наследяване.

Тези неща са част от `Base` частта на `Derived` обекта. Ако достъпът го позволява, можем да ги използваме през наследника.

#### Не се наследяват като обикновени функции:

- конструктори
- деструктори
- копиращи и move операции

Конструкторите на базовия клас не стават автоматично конструктори на наследения клас, защото наследеният клас има свои член-данни и своя логика за валидно състояние. Компилаторът не може просто да приеме, че начинът за създаване на `Base` е достатъчен за създаване на `Derived`.

Въпреки това, когато създаваме `Derived`, конструктор на `Base` задължително се извиква, защото `Base` частта трябва да бъде създадена преди `Derived` частта.

---

### Конструктори и деструктори при наследяване

При създаване на `Derived` обект първо трябва да се създаде неговата `Base` част. Причината е, че `Derived` разширява `Base`, а не обратното. Член-функциите и логиката на `Derived` могат да разчитат, че базовата част вече е валидна.

Редът е:

1. Конструират се базовите класове.
2. Конструират се член-данните на наследения клас.
3. Изпълнява се тялото на конструктора на наследения клас.

```cpp
#include <iostream>
#include <string>

class Person {
private:
    std::string name;

public:
    explicit Person(std::string name)
        : name(std::move(name)) {
        std::cout << "Person constructor\n";
    }

    ~Person() {
        std::cout << "Person destructor\n";
    }
};

class Student : public Person {
private:
    std::string facultyNumber;

public:
    Student(std::string name, std::string facultyNumber)
        : Person(std::move(name)),
          facultyNumber(std::move(facultyNumber)) {
        std::cout << "Student constructor\n";
    }

    ~Student() {
        std::cout << "Student destructor\n";
    }
};

int main() {
    Student s("Ivan", "12345");
}
```

Примерен изход:

```text
Person constructor
Student constructor
Student destructor
Person destructor
```

`Person` се създава първи, защото `Student` съдържа `Person` част. При разрушаване редът е обратен: първо се разрушава най-специализираната част (`Student`), после базовата част (`Person`).

---

### Избор на конструктор на базовия клас

Конструкторът на базовия клас се избира в initialization list на конструктора на наследника.

```cpp
class Base {
private:
    int value = 0;

public:
    Base() = default;

    explicit Base(int value)
        : value(value) {}
};

class Derived : public Base {
private:
    std::string text;

public:
    Derived(int value, std::string text)
        : Base(value),
          text(std::move(text)) {}
};
```

Тук `Derived` казва явно: “За моята `Base` част използвай конструктора `Base(int)`.” Това е нужно, защото `Derived` трябва да реши как да инициализира базовата си част на база параметрите, които получава.

Ако не посочим конструктор на базовия клас, компилаторът ще опита да извика default constructor на базовия клас.

```cpp
class Base {
public:
    explicit Base(int value) {}
};

class Derived : public Base {
public:
    Derived() {
        // Error: Base няма default constructor
    }
};
```

Правилно:

```cpp
class Derived : public Base {
public:
    Derived()
        : Base(0) {}
};
```

Това правило е логично: ако `Base` няма начин да бъде създаден без аргументи, `Derived` трябва изрично да подаде нужните аргументи.

---

### Защо деструкторите се извикват в обратен ред?

При разрушаване първо се изпълнява деструкторът на наследника, после се разрушават неговите член-данни, и накрая се разрушава базовата част.

Причината е, че `Derived` частта може да използва `Base` частта. Докато деструкторът на `Derived` работи, базовата част все още трябва да е валидна. Ако `Base` се разрушеше първи, `Derived` можеше да остане с достъп до вече разрушено състояние.

Този обратен ред е същият принцип като при локални обекти в scope: последно създаденият обект се разрушава първи.

---

### Копиране и местене при наследяване

В примери, които следват Rule of Zero, обикновено не пишем ръчно copy/move операции. Причината е, че стандартните член-данни като `std::string` и `std::vector` вече знаят как да се копират, местят и унищожават коректно.

```cpp
class Person {
private:
    std::string name;

public:
    Person() = default;

    explicit Person(std::string name)
        : name(std::move(name)) {}
};

class Student : public Person {
private:
    std::string facultyNumber;
    std::vector<double> grades;

public:
    Student() = default;

    Student(std::string name, std::string facultyNumber)
        : Person(std::move(name)),
          facultyNumber(std::move(facultyNumber)) {}
};
```

В такъв клас компилаторът може да генерира коректни:

- copy constructor;
- copy assignment operator=;
- move constructor;
- move assignment operator=;
- destructor.

Ако обаче по някаква причина решим да пишем copy/move логика ръчно в наследник, трябва да помним, че `Derived` има и `Base` част. Ако забравим да копираме или присвоим базовата част, получаваме непълен или грешен обект.

```cpp
class Base {
public:
    Base() = default;
    Base(const Base&) = default;
    Base& operator=(const Base&) = default;
};

class Derived : public Base {
private:
    std::string value;

public:
    Derived() = default;

    Derived(const Derived& other)
        : Base(other),
          value(other.value) {}

    Derived& operator=(const Derived& other) {
        if (this != &other) {
            Base::operator=(other);
            value = other.value;
        }

        return *this;
    }
};
```

Тук `Base(other)` копира базовата част в copy constructor-а, а `Base::operator=(other)` присвоява базовата част в copy assignment operator-а.

Това е една от причините Rule of Zero да е толкова удобен: избягваме ръчното синхронизиране между базова и наследена част, освен когато наистина имаме нужда от custom поведение.

---

### Подаване на Base и Derived към функции

Нека имаме следните класове:

```cpp
#include <iostream>
#include <string>

class Person {
private:
    std::string name;

public:
    explicit Person(std::string name)
        : name(std::move(name)) {}

    const std::string& getName() const {
        return name;
    }
};

class Student : public Person {
private:
    std::string facultyNumber;

public:
    Student(std::string name, std::string facultyNumber)
        : Person(std::move(name)),
          facultyNumber(std::move(facultyNumber)) {}

    const std::string& getFacultyNumber() const {
        return facultyNumber;
    }
};
```

---

#### Функция, която приема Base по reference

```cpp
void printPersonName(const Person& person) {
    std::cout << person.getName() << '\n';
}

int main() {
    Person p("Maria");
    Student s("Ivan", "12345");

    printPersonName(p); // OK
    printPersonName(s); // OK
}
```

Това работи, защото при public наследяване `Student` може да бъде разгледан като `Person`. В `Student` обекта има `Person` част, а `const Person&` може да се свърже точно с тази част.

Но вътре във функцията типът на параметъра е `const Person&`. Това означава, че функцията знае само за интерфейса на `Person`. Дори реалният обект отвън да е `Student`, тази функция не може да използва `getFacultyNumber()`, защото такава функция не съществува в `Person`.

```cpp
void printPersonName(const Person& person) {
    std::cout << person.getName() << '\n';

    // person.getFacultyNumber(); // Error
}
```

Това е много важно разграничение: обектът може реално да е `Student`, но функцията работи през гледната точка на `Person`.

---

#### Функция, която приема наследник по референция

```cpp
void printStudentInfo(const Student& student) {
    std::cout << student.getName() << '\n';
    std::cout << student.getFacultyNumber() << '\n';
}

int main() {
    Person p("Maria");
    Student s("Ivan", "12345");

    printStudentInfo(s); // OK
    // printStudentInfo(p); // Error
}
```

Тук функцията изисква конкретно `Student`. Не можем да подадем `Person`, защото не всеки човек е студент. Един `Person` обект няма `facultyNumber`, така че функцията няма как безопасно да използва студентския интерфейс.

Това показва посоката на отношението:

```text
Student -> Person     OK
Person  -> Student    не е OK
```

Всеки `Student` е `Person`, но не всеки `Person` е `Student`.

---

### Подаване по стойност и object slicing

```cpp
void printByValue(Person person) {
    std::cout << person.getName() << '\n';
}

int main() {
    Student s("Ivan", "12345");

    printByValue(s); // OK, но има slicing
}
```

Когато функцията приема `Person` по стойност, тя трябва да създаде нов обект от тип `Person`. Ако подадем `Student`, няма къде да се запази `Student` частта, защото параметърът е точно `Person`, а не `Student`.

Получава се **object slicing**:

```text
Original Student object: [Person part][Student part]
Copied Person parameter: [Person part]
```

`facultyNumber` и всички други специфични за `Student` данни се губят в копието. Това не означава, че оригиналният `Student` се поврежда. Означава, че параметърът във функцията е отделен `Person` обект, получен само от базовата част.

Затова при наследяване обикновено избягваме подаване на базов клас по стойност:

```cpp
void f(Person person); // риск от slicing
```

Предпочитаме reference:

```cpp
void f(const Person& person); // няма slicing
```

Reference не създава нов `Person` обект, а се свързва с вече съществуващата `Person` част на подадения обект.

---

### Защо `std::vector<Base>` не е колекция от различни наследници?

На пръв поглед може да изглежда логично да напишем:

```cpp
std::vector<Person> people;

Student s("Ivan", "12345");
people.push_back(s);
```

Това се компилира, но не прави това, което често начинаещите очакват. `std::vector<Person>` съдържа обекти от тип `Person`. Всеки елемент във вектора има точно размер и структура на `Person`. Когато подадем `Student`, той трябва да бъде преобразуван до `Person`, за да влезе във вектора.

Резултатът е slicing:

```text
Student object:        [Person part][Student part]
Stored vector element: [Person part]
```

Във вектора не се пази `Student` обект. Пази се нов `Person` обект, създаден от базовата част на `Student`.

Това е причината `std::vector<Base>` да не е подходящ за съхранение на различни наследени типове. Той е контейнер от реални `Base` обекти, не от “каквото и да е, което наследява Base”.

---

### Защо не използваме `Base*` като масив от наследници?

```cpp
Student students[3] = {
    Student("A", "1"),
    Student("B", "2"),
    Student("C", "3")
};

Person* ptr = students;
```

Първото преобразуване може да изглежда естествено: първият `Student` има `Person` част, така че `Person*` може да сочи към нея. Проблемът идва, ако използваме `ptr` като масив:

```cpp
// ptr[1] // проблемна идея
```

Pointer arithmetic зависи от типа на указателя. Ако `ptr` е `Person*`, тогава `ptr + 1` се премества с `sizeof(Person)` байта. Но реалният масив съдържа `Student` обекти, които обикновено са по-големи от `Person`.

Концептуално:

```text
students array:
[ Student ][ Student ][ Student ]

Student = [ Person part ][ Student part ]
```

Ако вървим през `Person*`, компилаторът очаква масивът да изглежда така:

```text
[ Person ][ Person ][ Person ]
```

Но това не е вярно. Затова `ptr[1]` няма надеждно да сочи към `Person` частта на втория `Student`. Може да попадне в средата на първия `Student` обект, което е грешно и опасно.

Затова не използваме `Base*` като начин да обхождаме масив от `Derived` обекти.

По-правилно би било да ползваме колекция от указатели към Base. Тоест:
- `Base**`
- `std::vector<Base*>`
- `std::vector<unique_ptr<Base>>`
---

## Exceptions (изключения)

Exception е механизъм за сигнализиране, че дадена операция не може да завърши нормално. Вместо функцията да върне специална стойност, която означава грешка, тя може да прекъсне нормалния поток и да хвърли exception.

Това е полезно, когато грешката не може или не трябва да бъде игнорирана. Например, ако функция трябва да раздели две числа, но второто е нула, тя не може да върне коректен резултат. Ако функция трябва да отвори файл, но файлът не съществува или няма права за достъп, тя не може да изпълни договора си.

```cpp
#include <stdexcept>

int divide(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("division by zero");
    }

    return a / b;
}
```

Тук `divide` казва: “Ако ми дадеш невалиден аргумент, не мога да върна смислен резултат.” Вместо да връща фиктивна стойност като `0`, тя хвърля exception.

---

Един класически подход е функцията да върне код за грешка:

```cpp
bool divide(int a, int b, int& result) {
    if (b == 0) {
        return false;
    }

    result = a / b;
    return true;
}
```

Това може да е напълно валиден дизайн. Но има недостатък: всеки извикващ код трябва да провери резултата. Ако някой забрави, програмата може да продължи с невалидни данни.

Exceptions позволяват да отделим нормалния поток от обработката на грешки. Кодът, който може да се справи с проблема, го хваща. Кодът, който не може да се справи, не е принуден да проверява всяка операция ръчно, а оставя exception-а да продължи нагоре.

Това не означава, че exceptions са винаги най-добрият избор. За очаквани, чести и нормални ситуации понякога е по-добре да използваме return value, `std::optional`, `std::expected` или друг подход.

---

### `throw`

`throw` хвърля exception обект.

```cpp
throw std::runtime_error("Something went wrong");
```

Технически в C++ можем да хвърлим почти всякакъв тип:

```cpp
throw 5;
throw "error";
```

Но добрата практика е да хвърляме обекти от тип, наследен от `std::exception`. Причината е, че така кодът, който обработва грешки, може да използва общ интерфейс като `what()` и да хваща различни грешки чрез общ базов тип.

---

### `try` / `catch`

Кодът, който може да хвърли exception, се поставя в `try` блок. След него пишем един или повече `catch` блокове, които описват какви exception-и можем да обработим.

```cpp
#include <iostream>
#include <stdexcept>

int divide(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("division by zero");
    }

    return a / b;
}

int main() {
    try {
        std::cout << divide(10, 0) << '\n';
    } catch (const std::invalid_argument& ex) {
        std::cout << "Invalid argument: " << ex.what() << '\n';
    }
}
```

Когато `divide(10, 0)` хвърли exception, изпълнението на `try` блока спира. Кодът след хвърлянето в `try` блока не продължава. Вместо това C++ започва да търси подходящ `catch` блок.

Ако намери такъв, изпълнението продължава в него. Ако не намери, exception-ът продължава към извикващата функция. Ако никъде няма подходящ `catch`, програмата приключва чрез механизма за необработени exceptions.

---

#### Защо хващаме exception по reference?

Правилно:

```cpp
catch (const std::exception& ex) {
    std::cout << ex.what() << '\n';
}
```

Не толкова добре:

```cpp
catch (std::exception ex) {
    std::cout << ex.what() << '\n';
}
```

Когато хващаме по стойност, exception обектът се копира. Това е излишно, но по-важният проблем е slicing. Ако реално е хвърлен `std::invalid_argument`, а ние хванем по стойност като `std::exception`, ще се копира само базовата `std::exception` част.

Когато хващаме по `const&`, не копираме exception-а и запазваме реалния му тип. Това позволява коректно да се извика `what()` и да не губим информация за конкретния exception.

`const` се използва, защото обикновено не трябва да променяме exception обекта, а само да го прочетем.

---

### Ред на `catch` блоковете

Редът на `catch` блоковете е важен. По-специфичните типове трябва да са преди по-общите.

```cpp
try {
    // ...
} catch (const std::invalid_argument& ex) {
    std::cout << "invalid_argument\n";
} catch (const std::runtime_error& ex) {
    std::cout << "runtime_error\n";
} catch (const std::exception& ex) {
    std::cout << "std::exception\n";
}
```

Причината е, че C++ проверява `catch` блоковете отгоре надолу. Ако първо сложим `catch (const std::exception&)`, той може да хване много стандартни exception-и преди по-конкретните блокове да имат шанс.

Лош ред:

```cpp
try {
    // ...
} catch (const std::exception& ex) {
    // ще хване и invalid_argument
} catch (const std::invalid_argument& ex) {
    // практически недостижим за invalid_argument
}
```

Това е подобно на `if` проверки: първо поставяме конкретните случаи, после общия fallback.

---

### `catch (...)`

`catch (...)` хваща всеки exception, независимо от типа.

```cpp
try {
    // ...
} catch (...) {
    std::cout << "Unknown error\n";
}
```

Този блок обикновено се поставя последен. Използва се, когато искаме да предотвратим излизане на exception извън дадена граница, например в `main`, в thread функция или в код, който не трябва да позволява exception да премине навън.

Недостатъкът е, че нямаме директен достъп до типа и съобщението на exception-а. Затова `catch (...)` не трябва да се използва като заместител на нормална обработка на конкретни грешки.

---

### Йерархия на стандартните exceptions

Основният базов клас е:

```cpp
std::exception
```

Той има метод:

```cpp
const char* what() const noexcept;
```

Този метод връща текстово описание на грешката. На този етап не разглеждаме виртуални функции подробно, но е достатъчно да знаем, че различните стандартни exception типове предоставят описание чрез `what()`.

Често използвана част от йерархията:

```text
std::exception
├── std::logic_error
│   ├── std::invalid_argument
│   ├── std::domain_error
│   ├── std::length_error
│   └── std::out_of_range
│
└── std::runtime_error
    ├── std::range_error
    ├── std::overflow_error
    └── std::underflow_error
```

---

#### `std::logic_error`

`std::logic_error` и наследниците му описват грешки, които обикновено показват проблем в логиката на програмата или в начина, по който е извикана функция.

Пример: функция очаква неотрицателна възраст, но получава отрицателна стойност.

```cpp
#include <stdexcept>

void setAge(int age) {
    if (age < 0) {
        throw std::invalid_argument("age cannot be negative");
    }
}
```

Тук проблемът не е във външна среда като файлова система или мрежа. Проблемът е, че кодът е подал аргумент, който нарушава очакванията на функцията.

---

#### `std::out_of_range`

`std::out_of_range` се използва, когато индекс, позиция или стойност излиза извън позволения диапазон.

```cpp
#include <stdexcept>
#include <vector>

int getAt(const std::vector<int>& values, std::size_t index) {
    if (index >= values.size()) {
        throw std::out_of_range("index is out of range");
    }

    return values[index];
}
```

Това е логическа грешка в извикването: функцията е получила индекс, който не може да бъде използван валидно.

---

#### `std::runtime_error`

`std::runtime_error` и наследниците му описват проблеми, които възникват по време на изпълнение и не са задължително резултат от грешна логика в кода.

Пример: файл не може да бъде отворен.

```cpp
#include <fstream>
#include <stdexcept>
#include <string>

void openFile(const std::string& path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("cannot open file: " + path);
    }
}
```

Тук извикващият код може да е подал напълно валиден път, но файлът да липсва, да няма права за четене или устройството да е недостъпно. Това е runtime проблем.

---

### Stack unwinding

Когато се хвърли exception, C++ започва да търси подходящ `catch` блок. Ако такъв блок не е в текущата функция, текущата функция се прекъсва и търсенето продължава в извикващата функция. Ако и там няма подходящ `catch`, процесът продължава нагоре по call stack-а.

Докато това става, всички локални обекти, които са били успешно създадени, се разрушават автоматично. Това се нарича **stack unwinding**.

Този механизъм е изключително важен, защото гарантира, че ресурсите, управлявани от обекти, ще бъдат освободени дори при грешка. Ако имаме `std::vector`, `std::string`, `std::unique_ptr`, `std::ifstream` или друг RAII обект, неговият деструктор ще бъде извикан при излизане от scope, включително при exception.

---

#### Пример за stack unwinding

```cpp
#include <iostream>
#include <stdexcept>
#include <string>

class Logger {
private:
    std::string name;

public:
    explicit Logger(std::string name)
        : name(std::move(name)) {
        std::cout << "Construct " << this->name << '\n';
    }

    ~Logger() {
        std::cout << "Destroy " << name << '\n';
    }
};

void f() {
    Logger a("a in f");
    throw std::runtime_error("error in f");
}

void g() {
    Logger b("b in g");
    f();
}

int main() {
    try {
        g();
    } catch (const std::exception& ex) {
        std::cout << "Caught: " << ex.what() << '\n';
    }
}
```

Примерен изход:

```text
Construct b in g
Construct a in f
Destroy a in f
Destroy b in g
Caught: error in f
```

Първо се създава `b` в `g`, после `a` във `f`. Когато `f` хвърли exception, `f` не завършва нормално. Преди да се напусне `f`, локалният обект `a` се разрушава. После се връщаме към `g`, която също не може да продължи нормално, затова `b` се разрушава. Накрая exception-ът стига до `catch` блока в `main`.

---        

### Хвърляне на exceptions в конструктори

Конструктор може да хвърли exception и това е нормален начин да кажем, че обектът не може да бъде създаден във валидно състояние.

```cpp
#include <stdexcept>
#include <string>

class Person {
private:
    std::string name;
    int age = 0;

public:
    Person(std::string name, int age)
        : name(std::move(name)), age(age) {
        if (this->name.empty()) {
            throw std::invalid_argument("name cannot be empty");
        }

        if (this->age < 0) {
            throw std::invalid_argument("age cannot be negative");
        }
    }
};
```

Конструкторът има задача да създаде валиден обект. Ако параметрите са такива, че валиден обект не може да бъде създаден, по-добре е конструкторът да хвърли exception, отколкото да остави обекта в полувалидно състояние.

Например `Person` без име може да е невалиден според правилата на програмата. Ако позволим такъв обект да съществува, после всички функции трябва да проверяват дали името е празно. По-чисто е да не позволяваме създаване на невалиден обект.

Ако constructor хвърли exception, обектът не се счита за успешно създаден. Това има важна последица: деструкторът на самия клас не се извиква, защото няма напълно създаден обект за разрушаване.

Но частите, които вече са били успешно създадени, трябва да бъдат разрушени. Това включва:

- вече конструирани базови класове;
- вече конструирани член-данни.

```cpp
#include <iostream>
#include <stdexcept>
#include <string>

class Base {
public:
    Base() {
        std::cout << "Base constructed\n";
    }

    ~Base() {
        std::cout << "Base destroyed\n";
    }
};

class Member {
public:
    Member() {
        std::cout << "Member constructed\n";
    }

    ~Member() {
        std::cout << "Member destroyed\n";
    }
};

class Derived : public Base {
private:
    Member member;

public:
    Derived() {
        std::cout << "Derived constructor body\n";
        throw std::runtime_error("Derived construction failed");
    }

    ~Derived() {
        std::cout << "Derived destroyed\n";
    }
};

int main() {
    try {
        Derived d;
    } catch (const std::exception& ex) {
        std::cout << "Caught: " << ex.what() << '\n';
    }
}
```

Примерен изход:

```text
Base constructed
Member constructed
Derived constructor body
Member destroyed
Base destroyed
Caught: Derived construction failed
```

`Derived destroyed` не се отпечатва, защото `Derived` обектът не е бил напълно създаден. Но `member` и `Base` са били създадени успешно, затова техните деструктори се извикват.

Това поведение е важно за exception safety. Ако член-данните управляват ресурси, те ще ги освободят дори когато конструкторът на целия обект се провали.

---

### ⚠️ Хвърляне на exceptions в деструктори

### Защо деструкторите НЕ трябва да хвърлят?

Деструкторите се извикват при нормално излизане от scope, но също и по време на stack unwinding. Ако вече има активен exception и по време на разрушаването на локален обект неговият деструктор хвърли втори exception, програмата ще извика `std::terminate()`.

Причината е, че C++ не може безопасно да обработва 2+ едновременно активни exception ситуации по този начин. Първият exception вече търси `catch` блок, а вторият се появява по време на cleanup.

```cpp
class BadDestructor {
public:
    ~BadDestructor() {
        throw std::runtime_error("error in destructor");
    }
};
```

Затова деструкторите трябва да бъдат cleanup механизъм, който не хвърля. Ако cleanup операция може да се провали и тази грешка е важна, тя трябва да се обработи преди деструктора чрез отделна функция.

---

### `noexcept` guarantee

`noexcept` е обещание, че дадена функция няма да хвърля exception.

```cpp
void f() noexcept {
    // не трябва да хвърля exception
}
```

Това обещание е важно както за човека, който чете кода, така и за компилатора и стандартната библиотека. Ако функция, маркирана с `noexcept`, все пак хвърли exception, програмата няма просто да потърси `catch` блок по нормалния начин. Вместо това ще бъде извикан `std::terminate()`.
Затова `noexcept` не трябва да се поставя механично навсякъде. То трябва да означава реална гаранция.

Много стандартни контейнери, например `std::vector`, понякога трябва да преместят елементите си в нова памет. Това се случва, когато капацитетът вече не стига и векторът трябва да задели по-голям блок памет.

Примерно:

```cpp
std::vector<MyType> values;
values.push_back(MyType{});
```

Ако при добавяне на нов елемент векторът трябва да се разшири, той трябва да премести или копира старите елементи в новата памет.

Тук възниква важен въпрос: какво става, ако move constructor-ът хвърли exception по средата на преместването?

Контейнерите се стремят да пазят силни гаранции за безопасност при грешки. Например, ако операцията по разширяване не успее, старият вектор не трябва да остане в повредено състояние.

Ако move constructor-ът е `noexcept`, `std::vector` знае, че може безопасно да мести елементите. Ако move не може да хвърли, няма риск преместването да се провали по средата и да остави част от елементите преместени, а друга част не.

Ако move constructor-ът не е `noexcept`, `std::vector` може да предпочете копиране вместо местене, ако копирането е налично. Причината е, че при копиране старите елементи остават непроменени, докато новите копия се създават. Ако копирането се провали, старият вектор все още е цял.

С други думи:

```text
noexcept move -> контейнерът може спокойно да мести
potentially throwing move -> контейнерът може да копира, за да пази exception safety
```

Това може да има performance ефект. Move обикновено е по-евтино от copy, особено за типове, които притежават ресурси като динамична памет. Ако move constructor-ът е `noexcept`, стандартните контейнери по-често могат да използват по-бързия път.

---

#### Пример за `noexcept` move

```cpp
class Example {
private:
    std::string value;

public:
    Example() = default;

    Example(Example&& other) noexcept = default;
    Example& operator=(Example&& other) noexcept = default;
};
```

При Rule of Zero обикновено не е нужно да пишем тези операции ръчно. Ако всички член-данни имат безопасни move операции, компилаторът може да генерира подходящо поведение.

Но ако все пак пишем move constructor или move assignment operator ръчно и знаем, че те не хвърлят, е полезно да ги маркираме като `noexcept`.

---

### Защо деструкторите обикновено са `noexcept`?

Деструкторите трябва да освобождават ресурси безопасно. Ако деструктор хвърли exception, особено по време на stack unwinding, програмата може да приключи чрез `std::terminate()`.

Затова деструкторите в C++ обикновено се разглеждат като функции, които не трябва да хвърлят.

---


### Rethrow

Понякога искаме да хванем exception, да добавим контекст или да логнем информация, и после да го хвърлим отново.

```cpp
try {
    openFile("config.txt");
} catch (const std::exception& ex) {
    std::cerr << "Failed while loading configuration: " << ex.what() << '\n';
    throw;
}
```

Важно е да използваме:

```cpp
throw;
```

Това прехвърля същия exception нататък.

Не е същото като:

```cpp
throw ex;
```

`throw ex;` хвърля нов exception обект и може да доведе до slicing, ако `ex` е хванат като базов тип. Затова при rethrow почти винаги правилното е просто `throw;`.

---

### Custom exception клас

Можем да създадем собствен exception тип, когато искаме да различаваме конкретна грешка от други грешки.

```cpp
#include <stdexcept>
#include <string>

class InvalidFacultyNumber : public std::logic_error {
public:
    explicit InvalidFacultyNumber(const std::string& message)
        : std::logic_error(message) {}
};

void validateFacultyNumber(const std::string& fn) {
    if (fn.empty()) {
        throw InvalidFacultyNumber("faculty number cannot be empty");
    }
}
```

Използване:

```cpp
try {
    validateFacultyNumber("");
} catch (const InvalidFacultyNumber& ex) {
    std::cout << "Invalid faculty number: " << ex.what() << '\n';
} catch (const std::exception& ex) {
    std::cout << "General error: " << ex.what() << '\n';
}
```

Custom exception типът е полезен, когато обработващият код трябва да реагира различно на различни категории грешки. Ако само искаме различно съобщение, често стандартните exception типове са достатъчни.

---

### Stacktrace

Stacktrace е списък от активните function calls в даден момент. Той показва пътя, по който изпълнението е стигнало до определено място.

Примерно:

```text
main()
 -> runApplication()
 -> loadConfig()
 -> openFile()
```

Това е полезно при debug-ване, защото често самото съобщение за грешка не е достатъчно. Ако видим само “cannot open file”, може да не знаем кой код се е опитал да отвори файла. Stacktrace показва контекста.

---

### Добри практики при exceptions

#### 1. Хвърляйте exception, когато функцията не може да изпълни договора си

```cpp
Student createStudent(std::string name, std::string fn) {
    if (name.empty()) {
        throw std::invalid_argument("name cannot be empty");
    }

    if (fn.empty()) {
        throw std::invalid_argument("faculty number cannot be empty");
    }

    return Student(std::move(name), std::move(fn));
}
```

Договорът на функцията е: “Ще създам валиден студент.” Ако параметрите не позволяват това, exception е нормален начин да сигнализираме проблема.

---

#### 2. Не използвайте exceptions за нормален контрол на потока

Лоша идея:

```cpp
try {
    // търсим елемент
} catch (...) {
    // елементът го няма
}
```

Ако липсата на елемент е нормална и очаквана ситуация, по-добре е да я моделираме явно чрез `if`, `std::optional` или друг подход.

```cpp
if (found) {
    // използваме елемента
} else {
    // няма такъв елемент
}
```

Exceptions са по-подходящи за ситуации, в които нещо нарушава очакванията на операцията, а не за всяко разклонение в логиката.

---

#### 3. Хващайте exception-и по `const&`

```cpp
catch (const std::exception& ex) {
    std::cout << ex.what() << '\n';
}
```

Така избягваме копиране и slicing, и запазваме информацията за реалния exception тип.

---

#### 4. Не хващайте exception, ако не можете да направите нещо смислено

Лошо:

```cpp
try {
    importantOperation();
} catch (const std::exception& ex) {
    // празен catch блок
}
```

Това скрива грешката. Програмата може да продължи в невалидно състояние, а причината за проблема да стане много трудна за откриване.

По-добре:

```cpp
try {
    importantOperation();
} catch (const std::exception& ex) {
    std::cerr << "Operation failed: " << ex.what() << '\n';
    throw;
}
```

Тук логваме контекст и после позволяваме exception-ът да продължи нагоре.

---

#### 5. Използвайте RAII, за да няма resource leaks

```cpp
void process() {
    std::vector<int> data;
    std::unique_ptr<Student> student = std::make_unique<Student>("Ivan", "12345");

    // Ако тук бъде хвърлен exception,
    // vector и unique_ptr ще се почистят автоматично.
}
```

Идеята е ресурсите да са собственост на обекти, чиито деструктори ще се извикат при stack unwinding.

---
