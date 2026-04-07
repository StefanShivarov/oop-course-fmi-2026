# Knowledge check: Move семантики и rvalue референции

>_За всички въпроси приемаме, че са include-нати нужните неща._

### Въпрос 1

Какво ще се отпечата на конзолата след изпълнението на следния код?

```cpp
#include <iostream>
#include <utility>

class A {};

void f(const A&)
{
    std::cout << "f(const A&)\n";
}

void f(A&&)
{
    std::cout << "f(A&&)\n";
}

int main()
{
    A a;
    const A ca;

    f(a);
    f(ca);
    f(A());
    f(std::move(a));
    f(std::move(ca));
}
```

<details>
<summary>Отговор</summary>

Ще се изведе:

```text
f(const A&)
f(const A&)
f(A&&)
f(A&&)
f(const A&)
```

Обяснение:
- `a` е lvalue, затова се избира `f(const A&)`
- `ca` е const lvalue, затова се избира `f(const A&)`
- `A()` е rvalue, затова се избира `f(A&&)`
- `std::move(a)` е xvalue, затова се избира `f(A&&)`
- `std::move(ca)` е `const A&&`, което не може да се върже към `A&&`, затова се избира `f(const A&)`

</details>

---

### Въпрос 2

Ще се компилира ли? Ако да — какво ще се отпечата? Ако не - защо?

```cpp
#include <iostream>

class A
{
public:
    A() = default;

    A(const A&)
    {
        std::cout << "A(const A&)\n";
    }

    A(A&&)
    {
        std::cout << "A(A&&)\n";
    }
};

void g(A&& obj)
{
    A other = obj;
}

int main()
{
    g(A());
}
```

<details>
<summary>Отговор</summary>

Да, кодът ще се компилира.

Ще се изведе:

```text
A(const A&)
```

Обяснение:
- параметърът `obj` е от тип `A&&`
- но понеже е **именувана променлива**, вътре във функцията `obj` е lvalue израз
- затова `A other = obj;` извиква copy constructor-а, а не move constructor-а

За да се извика move constructor-ът, трябва да се напише `A other = std::move(obj);`.

</details>

---

### Въпрос 3

Какво ще се отпечата на конзолата след изпълнението на следния код?

```cpp
#include <iostream>
#include <utility>

class B
{
public:
    B() = default;

    B(const B&)
    {
        std::cout << "B(const B&)\n";
    }

    B& operator=(const B&)
    {
        std::cout << "B::operator=(const B&)\n";
        return *this;
    }

    ~B() = default;
};

int main()
{
    B b1;
    B b2 = std::move(b1);

    B b3;
    b3 = std::move(b2);
}
```

<details>
<summary>Отговор</summary>

Ще се изведе:

```text
B(const B&)
B::operator=(const B&)
```

Обяснение:
- класът има user-declared copy constructor
- има user-declared copy assignment operator
- има user-declared destructor
- move операциите не се генерират автоматично
- `std::move(...)` само превръща израза в rvalue/xvalue, но не гарантира, че move операция съществува
- понеже move constructor и move assignment operator липсват, се използват copy операциите

</details>

---

### Въпрос 4

Какво ще се отпечата на конзолата след изпълнението на следния код?

```cpp
#include <iostream>

class B
{
public:
    B() = default;

    B(const B&)
    {
        std::cout << "B(const B&)\n";
    }

    B& operator=(const B&)
    {
        std::cout << "B::operator=(const B&)\n";
        return *this;
    }

    B(B&&)
    {
        std::cout << "B(B&&)\n";
    }

    B& operator=(B&&)
    {
        std::cout << "B::operator=(B&&)\n";
        return *this;
    }

    ~B() = default;
};

class C {
    B b;
public:
    C() = default;

    ~C() {
    }
};

int main()
{
    C c1;
    C c2 = std::move(c1);
}
```

<details>
<summary>Отговор</summary>

Ще се компилира и ще се отпечата:

```
B(const B&)
```
Причината е, че класът `C` има дефиниран деструктор и заради това компилаторът не генерира move constructor. Имплицитният move constructor се декларира само ако няма user-declared copy constructor, copy assignment, move assignment и destructor.

Затова се извиква копиращия конструктор.

</details>

---

### Въпрос 5

Какво ще се отпечата на конзолата след изпълнението на следния код?

```cpp
#include <iostream>

struct Part
{
    Part() = default;

    Part(const Part&)
    {
        std::cout << "Part(const Part&)\n";
    }

    Part(Part&&) noexcept
    {
        std::cout << "Part(Part&&)\n";
    }
};

struct Holder
{
    Part part;

    Holder(Part&& part) : part(part) {}
};

int main()
{
    Part p;
    Holder h(std::move(p));
}
```

<details>
<summary>Отговор</summary>


```text
Part(const Part&)
```

Обяснение:
- параметърът `part` е от тип `Part&&`
- но в constructor initializer list самото `part` е **именувана променлива**, следователно е lvalue
- затова `part(part)` извиква copy constructor-а, а не move constructor-а

За move трябва да бъде:

```cpp
Holder(Part&& part) : part(std::move(part)) {}
```

</details>

---

### Въпрос 6

Ще се компилира ли следния код? Ако не - защо?

```cpp
#include <utility>

struct Engine
{
    Engine() = default;
    Engine(const Engine&) = default;
    Engine(Engine&&) = delete;
};

struct Car
{
    Engine engine;
};

int main()
{
    Car c1;
    Car c2 = std::move(c1);
}
```

<details>
<summary>Отговор</summary>

Не, кодът няма да се компилира.

Обяснение:
- `Car` съдържа член `engine` от тип `Engine`
- `Engine(Engine&&)` е забранен (`delete`)
- следователно имплицитно генерираният move constructor на `Car` също става deleted
- при `Car c2 = std::move(c1);` overload resolution избира move constructor-а на `Car`, но той е deleted и съответно не се компилира

</details>

---

### Въпрос 7

Какво ще се отпечата на конзолата след изпълнението на следния код?

```cpp
#include <iostream>

struct Wheel
{
    Wheel() = default;

    Wheel(const Wheel&)
    {
        std::cout << "Wheel(const Wheel&)\n";
    }

    Wheel(Wheel&&) noexcept
    {
        std::cout << "Wheel(Wheel&&)\n";
    }
};

struct Engine
{
    Engine() = default;

    Engine(const Engine&)
    {
        std::cout << "Engine(const Engine&)\n";
    }

    Engine(Engine&&) noexcept
    {
        std::cout << "Engine(Engine&&)\n";
    }
};

struct Car
{
    Engine engine;
    Wheel wheel;

    Car(Engine&& e, Wheel&& w)
        : engine(std::move(e)), wheel(w) {}
};

int main()
{
    Engine e;
    Wheel w;
    Car c(std::move(e), std::move(w));
}
```

<details>
<summary>Отговор</summary>

Ще се изведе:

```text
Engine(Engine&&)
Wheel(const Wheel&)
```

Обяснение:
- `engine(std::move(e))` извиква move constructor-а на `Engine`
- `wheel(w)` използва `w` като именувана променлива, следователно като lvalue
- затова за `wheel` се извиква copy constructor-ът, а не move constructor-ът

</details>

---

### Въпрос 8

Какво ще се изведе на конзолата?

```cpp
struct Buffer
{
    Buffer() = default;

    Buffer(const Buffer&)
    {
        std::cout << "Buffer(const Buffer&)\n";
    }

    Buffer(Buffer&&)
    {
        std::cout << "Buffer(Buffer&&)\n";
    }
};

struct Container
{
    Buffer buffer;

    Container() = default;
    Container(const Container&) = default;
};

int main()
{
    Container c1;
    Container c2 = std::move(c1);
}
```

<details>
<summary>Отговор</summary>

```text
Buffer(const Buffer&)
```

Обяснение:
`Container` има user-declared copy constructor (`Container(const Container&) = default;`). Заради това компилаторът не генерира имплицитен move constructor за `Container`. После при `Container c2 = std::move(c1);` move constructor няма, затова се използва copy constructor-ът на `Container`, който копира члена buffer. Така се извиква `Buffer(const Buffer&)`.

</details>

---

### Въпрос 9

Какво ще се изведе на конзолата?

```cpp
#include <iostream>

class A {
public:
    A() {
        std::cout << "A()" << std::endl;
    }

    A(const A& other) {
        std::cout << "A(const A& other)" << std::endl;
    }

    A& operator=(const A& other) {
        std::cout << "A& operator=(const A& other)" << std::endl;
        return *this;
    }

    A(A&& other) noexcept {
        std::cout << "A(A&& other)" << std::endl;
    }

    A& operator=(A&& other) noexcept {
        std::cout << "operator=(A&& other)" << std::endl;
        return *this;
    }

    ~A() {
        std::cout << "~A()" << std::endl;
    }
};

A&& g() {
    return A();
}

int main()
{
    A obj = g();
}
```

<details>
<summary>Отговор</summary>

Undefined behaviour, в повечето случаи ще се принтира:
```text
A()
~A()
A(A&& other)
~A()
```

Обяснение:
- A() в g() създава временен обект
→ `A()`
- Временният обект се унищожава при излизане от g()
→ `~A()`
- В main се вика move constructor към dangling reference (висяща референция)
→ `A(A&& other)`
- Накрая obj се унищожава
→ `~A()`

Това е Undefined behaviour и не е правилно. Правилното е функцията да връща нов обект от тип A.

</details>

---

### Въпрос 10

Какво ще се изведе на конзолата?

```cpp
#include <iostream>

class A {
public:
    A() {
        std::cout << "A()" << std::endl;
    }

    A(const A& other) {
        std::cout << "A(const A& other)" << std::endl;
    }

    A& operator=(const A& other) {
        std::cout << "A& operator=(const A& other)" << std::endl;
        return *this;
    }

    A(A&& other) noexcept {
        std::cout << "A(A&& other)" << std::endl;
    }

    A& operator=(A&& other) noexcept {
        std::cout << "operator=(A&& other)" << std::endl;
        return *this;
    }

    ~A() {
        std::cout << "~A()" << std::endl;
    }
};

A g() {
    return A();
}

int main()
{
    A obj = g();
}
```

<details>
<summary>Отговор</summary>

```text
A()
~A()
```

Обяснение:

Тук има RVO (Return Value Optimization или guaranteed copy elision).
Идеята е, че резултатът от функцията се конструира директно на мястото, където ще бъде крайният обект.
Затова при `A obj = g();` обектът obj се създава директно.
Последователността е:
- извиква се A()
- при края на main се извиква ~A()

</details>

---

## Въпрос 11

Какво ще се изведе на конзолата?

```cpp
class B{};

class A {
private:
    B b;
public:
    A() {
        std::cout << "A()" << std::endl;
    }

    explicit A(B b) {
        std::cout << "A(B)" << std::endl;
    }

    explicit A(const B& b) {
        std::cout << "A(const B&)" << std::endl;
    }
};

int main()
{
    B b;
    A a(b);
}
```


<details>
<summary>Отговор</summary>

Нищо няма да се изведе, защото програмата няма да се компилира. Извикването `A a(b);` е двусмислено: и `A(B)`, и `A(const B&)` могат да приемат както lvalue, така и rvalue от тип B, затова и двата конструктора са подходящи за аргумента b. В този случай компилаторът не може да избере еднозначно кой конструктор да извика.

</details>
