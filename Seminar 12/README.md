# 12. Полиморфизъм. Статично и динамично свързване. Виртуални функции. Виртуални таблици. Абстрактни класове. Хетерогенни контейнери. Копиране на полиморфни обекти с clone

В обектно-ориентираното програмиране често имаме различни класове, които представляват различни конкретни видове на една по-обща идея.

Например:

- `Circle` е фигура
- `Rectangle` е фигура
- `Triangle` е фигура

Всички те са фигури, но всяка от тях изчислява лицето си по различен начин.

Искаме да можем да пишем код, който работи с „фигура“, без да се интересува дали конкретният обект е кръг, правоъгълник или триъгълник.

Например:

```cpp
void printArea(const Shape& shape)
{
    std::cout << shape.area() << '\n';
}
```

Тази функция не знае конкретния тип на обекта.

Тя знае само, че обектът е някакъв вид `Shape` и има функция `area()`.

Това е една от основните идеи на полиморфизма.

---

## Полиморфизъм

**Полиморфизъм** е един от основните ООП принципи. Той означава да работим с различни конкретни типове чрез общ базов интерфейс, като всяко конкретно поведение се избира според реалния тип на обекта.

- 1 име (_Animal_), с много различни имплементации (_Dog, Cat, Pig, Cow_)
- едни и същи действия се реализират по различен начин в зависимост от обектите, върху които се прилагат

В C++ това най-често се реализира чрез:

- наследяване
- виртуални функции
- указатели или референции към базов клас
- абстрактни базови класове

Пример:

```cpp
class Shape
{
public:
    virtual double area() const = 0;

    virtual ~Shape() = default;
};
```

Тук `Shape` казва:

> Всеки обект, който е наследник на `Shape`, трябва да може да изчисли лице.

Но `Shape` сам по себе си няма как да знае как точно се изчислява лицето. Това зависи от конкретния тип фигура.

```cpp
class Circle : public Shape
{
private:
    double radius;
    static constexpr double PI = 3.141592653589793;

public:
    explicit Circle(double radius)
        : radius(radius)
    {}

    double area() const override
    {
        return PI * radius * radius;
    }
};
```

```cpp
class Rectangle : public Shape
{
private:
    double width;
    double height;

public:
    Rectangle(double width, double height)
        : width(width), height(height)
    {}

    double area() const override
    {
        return width * height;
    }
};
```

Сега можем да напишем:

```cpp
void printArea(const Shape& shape)
{
    std::cout << shape.area() << '\n';
}
```

и да я използваме така:

```cpp
Circle circle(5);
Rectangle rectangle(3, 4);

printArea(circle);
printArea(rectangle);
```

Функцията `printArea` работи с `Shape`, но реално може да получи `Circle`, `Rectangle` или друг наследник.

Това е полиморфно поведение.

---

### Защо е полезен полиморфизмът?

Без полиморфизъм често бихме писали код от вида:

```cpp
// Лош дизайн
// ако е Circle -> изчисли лице като на кръг
// ако е Rectangle -> изчисли лице като на правоъгълник
// ако е Triangle -> изчисли лице като на триъгълник
```

Това има няколко проблема.

Първо, кодът започва да зависи от всички конкретни типове.

Второ, ако добавим нов тип, например `Triangle`, трябва да намерим всички места, където има такива проверки, и да ги променим.

Трето, логиката, която би трябвало да принадлежи на самия клас, се разпилява навън.

По-добрият подход е:

```cpp
class Triangle : public Shape
{
private:
    double base;
    double height;

public:
    Triangle(double base, double height)
        : base(base), height(height)
    {}

    double area() const override
    {
        return base * height / 2;
    }
};
```

След това съществуващият код, който работи с `Shape`, не се променя.

```cpp
void printArea(const Shape& shape)
{
    std::cout << shape.area() << '\n';
}
```

Той вече работи и с `Triangle`.

Това е основната полза от полиморфизма: кодът работи с абстракция, а конкретните класове сами реализират поведението си.

---

## Статично свързване (compile-time polymorphism)

- изборът коя функция ще бъде извикана става още по време на компилация.
- в контекст на наследяване, се определя от типа на указателя/референцията, от която се извиква функцията

До момента сме срещали следните примери за compile-time polymorphism:
- function overloading
    ```cpp
    void f();
    void f(int);
    void f(int, int);
    ```
- operator overloading
    ```cpp
    3 + 7
    "abc" + "def"
    ```

Пример при наследяване:

```cpp
class Animal
{
public:
    void speak() const
    {
        std::cout << "Animal speaks\n";
    }
};

class Dog : public Animal
{
public:
    void speak() const
    {
        std::cout << "Dog barks\n";
    }
};
```

Ако напишем:

```cpp
Dog dog;
dog.speak();
```

ще се извика:

```txt
Dog barks
```

Но ако имаме:

```cpp
void makeSound(const Animal& animal)
{
    animal.speak();
}
```

и извикаме:

```cpp
Dog dog;
makeSound(dog);
```

резултатът ще бъде:

```txt
Animal speaks
```

Причината е, че `speak()` не е виртуална функция.

Във функцията:

```cpp
void makeSound(const Animal& animal)
```

статичният тип на `animal` е `Animal`. Тук имаме статично свързване и изборът на функция която да се извика се случва по време на компилация, в зависимост от типа на референцията, която извиква функцията, който в случая е `Animal`.

Затова компилаторът избира `Animal::speak()`.

Реалният обект е `Dog`, но при невиртуална функция това не участва в избора.

---

## Динамично свързване (runtime polymorphism)

- изборът коя функция да се извика се прави по време на изпълнение на програмата, според реалния тип на обекта

За това използваме виртуални функции.

```cpp
class Animal
{
public:
    virtual void speak() const
    {
        std::cout << "Animal speaks\n";
    }

    virtual ~Animal() = default;
};

class Dog : public Animal
{
public:
    void speak() const override
    {
        std::cout << "Dog barks\n";
    }
};
```

Сега:

```cpp
void makeSound(const Animal& animal)
{
    animal.speak();
}
```

и:

```cpp
Dog dog;
makeSound(dog);
```

ще даде:

```txt
Dog barks
```

Този път `speak()` е виртуална функция.

Компилаторът знае, че работи с `Animal&`, но реалното извикване се избира според реалния тип на обекта.

---

## Виртуални функции

Виртуална функция е член-функция, която може да бъде предефинирана в наследник и да бъде извиквана полиморфно чрез базов тип.

```cpp
class Shape
{
public:
    virtual double area() const = 0;

    virtual ~Shape() = default;
};
```

Ключовата дума `virtual` казва:

> Тази функция участва в динамично свързване.

Тоест, ако имаме:

```cpp
const Shape& shape = circle;
shape.area();
```

ще се извика `Circle::area()`, ако реалният обект е `Circle`.

---

Полиморфизмът работи през базовия тип.

Ако искаме да напишем:

```cpp
void printArea(const Shape& shape)
{
    std::cout << shape.area() << '\n';
}
```

тогава `area()` трябва да бъде част от интерфейса на `Shape`.

Компилаторът гледа статичния тип `Shape`.

Ако `Shape` няма `area()`, този код няма да се компилира, дори реалният обект да е `Circle`.

Затова базовият клас трябва да съдържа операциите, които искаме да използваме полиморфно.

---

## Абстрактни класове

Абстрактен клас е клас, от който не могат да се създават директни обекти.

В C++ един клас става абстрактен, когато има поне една pure virtual функция.

Ако някой от наследниците на абстрактен клас не предефинира някоя от чисто виртуалните ф-ии, той също става абстрактен.

__Чисто виртуална функция (pure virtual)__ е виртуална функция, която няма имплементация и е предназначена да бъде имплементирана от наследниците.

```cpp
virtual void f() = 0;
```

>_Чисто виртуалните функции могат да имат и тяло (имплементация) в същия клас, в който са дефинирани, но тогава не могат да се извикват извън класовете. Пример: чисто виртуални деструктори_


```cpp
class Shape
{
public:
    virtual double area() const = 0;

    virtual ~Shape() = default;
};
```

Тук:

```cpp
virtual double area() const = 0;
```

означава:

> Базовият клас заявява, че всяка фигура трябва да има лице, но не знае как точно се изчислява то.

Затова не можем да напишем:

```cpp
Shape shape; // грешка
```

Това е правилно, защото „някаква фигура“ без конкретен тип няма достатъчно информация, за да изчисли лице.

---

Много често в учебни примери абстрактният клас изглежда като чист интерфейс:

```cpp
class Shape
{
public:
    virtual double area() const = 0;
    virtual void print() const = 0;

    virtual ~Shape() = default;
};
```

Това е валиден абстрактен клас, но не е единственият вариант.

Абстрактният клас може да съдържа:

- полета
- constructor
- обикновени member функции
- обща логика
- helper функции
- частично реализирано поведение
- pure virtual функции за частите, които наследниците трябва да дефинират

Абстрактният клас ни позволява да изнесем общата логика на едно място, вместо да я повтаряме във всеки наследник.

---

### Пример за абстрактен клас с обща логика

```cpp
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

class Shape
{
private:
    std::string label;

protected:
    explicit Shape(std::string label)
        : label(std::move(label))
    {
        if (this->label.empty())
        {
            throw std::invalid_argument("Shape label cannot be empty.");
        }
    }

public:
    const std::string& getLabel() const
    {
        return label;
    }

    void printInfo() const
    {
        std::cout << "Shape: " << getType() << '\n';
        std::cout << "Label: " << label << '\n';
        std::cout << "Area: " << area() << '\n';
    }

    bool hasLargerAreaThan(const Shape& other) const
    {
        return area() > other.area();
    }

    virtual std::string getType() const = 0;
    virtual double area() const = 0;
    virtual std::unique_ptr<Shape> clone() const = 0;

    virtual ~Shape() = default;
};
```

Този клас е абстрактен, защото има pure virtual функции:

```cpp
virtual std::string getType() const = 0;
virtual double area() const = 0;
virtual std::unique_ptr<Shape> clone() const = 0;
```

Но той не е просто интерфейс.

Той има собствено поле:

```cpp
std::string label;
```

Има constructor:

```cpp
explicit Shape(std::string label)
```

Има обща логика:

```cpp
const std::string& getLabel() const;
void printInfo() const;
bool hasLargerAreaThan(const Shape& other) const;
```

Това означава, че всички наследници автоматично получават тази логика.

Няма нужда всеки наследник да пази собствено име, да пише собствен `getLabel()` или да повтаря логиката за сравнение по лице.

---

### Наследници на този абстрактен клас

```cpp
class Circle final : public Shape
{
private:
    double radius;

public:
    Circle(std::string label, double radius)
        : Shape(std::move(label)), radius(radius)
    {
        if (radius <= 0)
        {
            throw std::invalid_argument("Radius must be positive.");
        }
    }

    std::string getType() const override
    {
        return "Circle";
    }

    double area() const override
    {
        return 3.141592653589793 * radius * radius;
    }

    std::unique_ptr<Shape> clone() const override
    {
        return std::make_unique<Circle>(*this);
    }
};
```

```cpp
class Rectangle final : public Shape
{
private:
    double width;
    double height;

public:
    Rectangle(std::string label, double width, double height)
        : Shape(std::move(label)), width(width), height(height)
    {
        if (width <= 0 || height <= 0)
        {
            throw std::invalid_argument("Rectangle sides must be positive.");
        }
    }

    std::string getType() const override
    {
        return "Rectangle";
    }

    double area() const override
    {
        return width * height;
    }

    std::unique_ptr<Shape> clone() const override
    {
        return std::make_unique<Rectangle>(*this);
    }
};
```

Сега можем да използваме общата логика от `Shape`:

```cpp
Circle circle("small circle", 3);
Rectangle rectangle("main rectangle", 4, 5);

circle.printInfo();
rectangle.printInfo();

if (rectangle.hasLargerAreaThan(circle))
{
    std::cout << "Rectangle is larger.\n";
}
```

Методите `printInfo()` и `hasLargerAreaThan()` не са написани в `Circle` и `Rectangle`.

Те са написани веднъж в абстрактния базов клас.

Това е една от основните причини да използваме абстрактен клас вместо да повтаряме една и съща логика във всеки наследник.

---

### Кога използваме абстрактен клас?

Използваме абстрактен клас, когато имаме обща концепция, която:

1. не трябва да се инстанцира директно
2. има общ интерфейс за всички наследници
3. може да има обща логика, която не искаме да повтаряме
4. има части от поведението, които зависят от конкретния наследник

Примери:

```cpp
class Shape;
class Employee;
class PaymentMethod;
class Command;
class Animal;
```

Например при `Employee` може да имаме обща логика за име, стаж и печатане на информация, но различни класове служители да изчисляват заплащане по различен начин.

```cpp
class Employee
{
private:
    std::string name;

protected:
    explicit Employee(std::string name)
        : name(std::move(name))
    {}

public:
    const std::string& getName() const
    {
        return name;
    }

    void printName() const
    {
        std::cout << "Employee: " << name << '\n';
    }

    virtual double calculateSalary() const = 0;

    virtual ~Employee() = default;
};
```

Тук `Employee` не е просто интерфейс.

Той пази общи данни и предоставя общо поведение.

Но остава абстрактен, защото конкретното изчисляване на заплата зависи от наследника.

---

### `override`

`override` казва на компилатора:

> Тази функция трябва да предефинира виртуална функция от базовия клас.

Пример:

```cpp
class Shape
{
public:
    virtual double area() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape
{
private:
    static constexpr double PI = 3.14159;
public:
    double area() const override {
        return PI * radius * radius;
    }
};
```

---
Без `override` можем лесно да допуснем грешка.

```cpp
class Shape
{
public:
    virtual double area() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape
{
private:
    static constexpr double PI = 3.14159;
public:
    double area() {
        return PI * radius * radius;
    }
};
```

Тук `Circle::area()` не override-ва `Shape::area()`.

Причината е, че в базовия клас функцията е:

```cpp
virtual double area() const = 0;
```

а в наследника е:

```cpp
double area()
```

Липсва `const`.

Ако напишем:

```cpp
double area() {
    return PI * radius * radius;
}
```

компилаторът ще даде грешка.

Това е полезно, защото грешката се хваща веднага и бързо можем да се усетим, че сме сгрешили сигнатурата на функцията.

Практическо правило:

> Когато предефинираме виртуална функция, използваме `override`.

---

### `final`

Когато клас е маркиран с `final`, той не може да бъде наследяван.

```cpp
class Circle final : public Shape
{
private:
    static constexpr double PI = 3.14159;
public:
    double area() const override
    {
        return PI * radius * radius;
    }
};
```

Това няма да се компилира:

```cpp
class SpecialCircle : public Circle
{
};
```

Използваме `final`, когато искаме да кажем:

> Този клас е крайна конкретна реализация и не е предназначен за наследяване.

---

Можем да сложим `final` и върху виртуална функция.

```cpp
class Base
{
public:
    virtual void print() const
    {
        std::cout << "Base\n";
    }

    virtual ~Base() = default;
};

class Derived : public Base
{
public:
    void print() const final
    {
        std::cout << "Derived\n";
    }
};
```

Това означава, че класове, които наследяват `Derived`, вече не могат да предефинират `print()`.

---

### Виртуален деструктор

Когато използваме полиморфизъм, често притежаваме обект от наследен клас чрез указател към базов клас.

Например:

```cpp
std::unique_ptr<Shape> shape = std::make_unique<Circle>("circle", 5);
```

Статичният тип е:

```cpp
std::unique_ptr<Shape>
```

Реалният обект е:

```cpp
Circle
```

Когато `shape` бъде унищожен, трябва да се извика деструкторът на реалния тип.

Затова базовият клас трябва да има виртуален деструктор:

```cpp
virtual ~Shape() = default;
```

Практическо правило:

> Ако класът се използва полиморфно, деструкторът му трябва да бъде виртуален.

---

## Виртуални таблици

Виртуалната таблица, често наричана **vtable**, е механизъм, който компилаторите обикновено използват, за да реализират виртуални функции.

Концептуално, за клас с виртуални функции компилаторът поддържа таблица с адресите на правилните виртуални функции.

Например:

```txt
Circle vtable:
- Circle::getType
- Circle::area
- Circle::clone
- Circle::~Circle
```

```txt
Rectangle vtable:
- Rectangle::getType
- Rectangle::area
- Rectangle::clone
- Rectangle::~Rectangle
```

Всеки полиморфен обект обикновено съдържа скрит указател към правилната виртуална таблица.

Този указател често се нарича `vptr`.

---

Ако имаме:

```cpp
void print(const Shape& shape)
{
    shape.printInfo();
}
```

`printInfo()` е функция от базовия клас.

Но вътре в нея има:

```cpp
std::cout << "Shape: " << getType() << '\n';
std::cout << "Area: " << area() << '\n';
```

`getType()` и `area()` са виртуални функции.

Ако реалният обект е `Circle`, ще се извикат:

```cpp
Circle::getType()
Circle::area()
```

Ако реалният обект е `Rectangle`, ще се извикат:

```cpp
Rectangle::getType()
Rectangle::area()
```

> Дори обща функция, дефинирана в абстрактния базов клас, може да използва виртуални функции, за да получи конкретно поведение от наследниците.

---

## Хетерогенен контейнер

Хетерогенен контейнер е контейнер, който съдържа обекти от различни конкретни типове, но ги управлява чрез общ базов тип.

Пример:

```cpp
std::vector<std::unique_ptr<Shape>> shapes;
```

Този контейнер може да съдържа:

```cpp
Circle
Rectangle
Triangle
```

защото всички те са наследници на `Shape`.

---

### Защо не използваме `std::vector<Shape>`?

Това е грешен подход:

```cpp
std::vector<Shape> shapes;
```

Ако `Shape` е абстрактен клас, това изобщо няма да се компилира.

Ако `Shape` не беше абстрактен, щяхме да имаме друг проблем — **object slicing**.

---

## Копиране на полиморфни обекти

Когато имаме полиморфен обект през базов тип, например:

```cpp
std::unique_ptr<Shape> shape;
```

ние знаем, че `shape` сочи към някакъв `Shape`.

Но не знаем директно дали реалният обект е:

```cpp
Circle
Rectangle
Triangle
```

При deep copy искаме да създадем нов обект от същия реален тип.

Ако реалният обект е `Circle`, трябва да се извика copy constructor на `Circle`.

Ако реалният обект е `Rectangle`, трябва да се извика copy constructor на `Rectangle`.

Ако реалният обект е `Triangle`, трябва да се извика copy constructor на `Triangle`.

Единият проблем е, че при колекция от unique_ptr-и например, единственият вариант да можем да копираме е ако правим deep copy на въпросните unique_ptr-и. Другият основен проблем е, че кодът, който държи `std::unique_ptr<Shape>`, не знае конкретния тип на фигурата която стои отдолу.

---

НЕ искаме да пишем логика от вида:

```cpp
// Лош дизайн
// ако е Circle -> копирай като Circle
// ако е Rectangle -> копирай като Rectangle
// ако е Triangle -> копирай като Triangle
```

Това би означавало, че външният код трябва да знае всички наследници.

Това разваля идеята на полиморфизма.

Ако в последствие добавим нов наследник `Ellipse`, трябва да променяме и копиращата логика.

---

## Решението: `clone()`

Решението е да дадем на самия обект отговорността да копира себе си.

В базовия клас добавяме:

```cpp
virtual std::unique_ptr<Shape> clone() const = 0;
```

Това означава:

> Всеки наследник трябва да може да създаде свое собствено копие.

Пример:

```cpp
class Circle final : public Shape
{
private:
    double radius;

public:
    Circle(std::string label, double radius)
        : Shape(std::move(label)), radius(radius)
    {}

    std::string getType() const override
    {
        return "Circle";
    }

    double area() const override
    {
        return 3.141592653589793 * radius * radius;
    }

    std::unique_ptr<Shape> clone() const override
    {
        return std::make_unique<Circle>(*this);
    }
};
```

Тук:

```cpp
return std::make_unique<Circle>(*this);
```

извиква copy constructor на `Circle`.

За `Rectangle`:

```cpp
std::unique_ptr<Shape> clone() const override
{
    return std::make_unique<Rectangle>(*this);
}
```

извиква copy constructor на `Rectangle`.

Външният код не пита какъв е реалният тип.

Той просто извиква:

```cpp
shape->clone()
```

Понеже `clone()` е виртуална функция, C++ избира правилната реализация според реалния тип на обекта.

Този подход е известен като **Prototype design pattern**.

Идеята на Prototype pattern е:

> Вместо външният код да знае как точно се създава копие на даден обект, самият обект предоставя операция за клониране.

В нашия случай тази операция е:

```cpp
virtual std::unique_ptr<Shape> clone() const = 0;
```

Всеки конкретен клас знае как да копира себе си.

Така добавянето на нов наследник изисква само той да реализира `clone()`.

Кодът, който копира колекцията, не се променя.

---

`unique_ptr` не е основната концептуална причина за `clone()`.

Концептуалната причина е:

> Искаме полиморфно deep copy с правилния реален тип.

Но `unique_ptr` влияе практически:

```cpp
std::vector<std::unique_ptr<Shape>>
```

не може да се копира автоматично, защото `unique_ptr` не може да се копира.

Това е добре, защото компилаторът ни принуждава да решим какво означава копиране.

При полиморфна колекция обикновено имаме избор:

1. да забраним копирането
2. да позволим само move
3. да направим deep copy чрез `clone()`
4. да използваме споделена собственост със `std::shared_ptr`, ако това наистина е желаният модел

---

## Защо се налага ръчно да разписваме копиращите операции при полиморфни колекции?

Ръчното разписване на копиращите операции не е самоцелно „защото има `unique_ptr`“.

Да, `unique_ptr` не може да се копира и затова default copy constructor-ът на хетерогенния контейнер няма да работи.

Но по-съществената причина е друга:

> Искаме правилно полиморфно deep copy.

Това означава, че ако оригиналният контейнер съдържа:

```txt
Circle
Rectangle
Circle
```

копираният контейнер трябва да съдържа:

```txt
нов Circle
нов Rectangle
нов Circle
```

Не искаме:

- да копираме само указатели
- да споделяме същите обекти неволно
- да губим реалния тип
- да правим проверки за конкретни наследници
- да получаваме object slicing

---

### Copy constructor

```cpp
Container(const Container& other)
{
    shapes.reserve(other.shapes.size());

    for (const auto& shape : other.shapes)
    {
        shapes.push_back(shape->clone());
    }
}
```

Тук:

```cpp
shape->clone()
```

е виртуално извикване.

Ако `shape` сочи към `Circle`, се извиква:

```cpp
Circle::clone()
```

Ако сочи към `Rectangle`, се извиква:

```cpp
Rectangle::clone()
```

Външният клас `Container` не знае и не трябва да знае конкретния тип.

```cpp
int main()
{
    Container c;

    c.add(std::make_unique<Circle>("first circle", 5));
    c.add(std::make_unique<Rectangle>("main rectangle", 3, 4));

    c.printAll();

    Container copy = c;

    std::cout << "Copied container:\n";
    c.printAll();

    return 0;
}
```

Тук `c` съдържа различни конкретни типове, но ги управлява чрез:

```cpp
std::vector<std::unique_ptr<Shape>>
```

При копиране се извиква `clone()` за всеки обект.

Така се създава нова независима колекция от обекти със същите реални типове.
