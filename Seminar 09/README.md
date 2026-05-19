# 09. Rule of Zero. `std::vector` и `std::string`. Итератори. Умни указатели (smart pointers)

## Съдържание

1. [Rule of Zero](#rule-of-zero)
2. [`std::string` и `std::vector`](#stdstring-и-stdvector)
3. [Итератори](#итератори)
4. [Алгоритми върху диапазони от итератори](#алгоритми-върху-диапазони-от-итератори)
5. [Smart pointers](#smart-pointers)
6. [Обобщение](#обобщение)

---

## Rule of Zero

**Rule of Zero** е принцип в съвременния C++, според който класът **НЕ** трябва сам да дефинира:

- деструктор;
- copy constructor;
- copy assignment operator;
- move constructor;
- move assignment operator;

ако не управлява директно ресурс.

Под „ресурс“ тук разбираме неща като:

- динамична памет (`new` / `delete`);
- файлови дескриптори;
- сокети;
- mutex-и;
- други външни ресурси, които трябва изрично да се освобождават.

Идеята е проста: когато използваме готови и безопасни типове като `std::string`, `std::vector`, `std::unique_ptr` и други RAII обекти, те вече знаят как да копират, местят и унищожават собствените си ресурси. Тогава нашият клас може да разчита на **генерираните от компилатора специални член-функции**.

### Защо това е полезно

Rule of Zero води до:

- по-малко код, следователно и по-чист
- по-малко грешки
- по-лесна поддръжка
- по-ясна отговорност за ownership-а

### Пример

Лош стил, ако не ни се налага да управляваме ресурс ръчно:

```cpp
class Student {
    char* name;
public:
    Student(const char* n);
    Student(const Student& other);
    Student& operator=(const Student& other);
    ~Student();
    //...
};
```

Този клас сам трябва да се грижи за динамичната памет, което отваря врата за много грешки.

По-добър вариант:

```cpp
#include <string>

class Student {
public:
    std::string name;
    int fn = 0;
    //...
};
```

Тук `std::string` се грижи за паметта си сам. Класът не се нуждае от специални член-функции.

### Rule of Three, Rule of Five и Rule of Zero

Тези правила са свързани:

- **Rule of Three**: ако пишеш един от деструктор, copy constructor, copy assignment, вероятно трябва да напишеш и трите.
- **Rule of Five**: в съвременния C++ към тях добавяме move constructor и move assignment.
- **Rule of Zero**: по-добре е изобщо да не пишем тези функции, ако можем да композираме класа от типове, които вече управляват ресурсите правилно.

Най-често Rule of Zero е предпочитаният стил.

---

## `std::string` и `std::vector`

`std::string` и `std::vector` са два от най-важните стандартни класове в C++. Те инкапсулират динамична памет и предоставят удобен, безопасен и богат интерфейс.

### `std::string`

`std::string` представлява динамичен низ от символи. Той е много по-удобен и безопасен от работа с масиви от `char` и C-style низове.

[Документация на `std::string`](https://cplusplus.com/reference/string/string/)

#### Често използвани операции

```cpp
#include <iostream>
#include <string>

int main() {
    std::string s = "Hello";

    s += " world";
    std::cout << s << '\n';           // Hello world
    std::cout << s.size() << '\n';    // 11
    std::cout << s.empty() << '\n';   // 0 (false)
    std::cout << s[1] << '\n';        // e
}
```

#### Полезни методи

- `size()` / `length()` — дължина на низа
- `empty()` — дали е празен
- `clear()` — изчиства съдържанието
- `push_back(ch)` — добавя символ в края
- `pop_back()` — маха последния символ
- `substr(pos, count)` — подниз
- `find(x)` — търсене
- `c_str()` — C-style представяне, когато ни трябва API / функция, която приема `const char*`

#### Пример с `find` и `substr`

```cpp
#include <iostream>
#include <string>

int main() {
    std::string text = "programming";

    std::size_t pos = text.find("gram");
    if (pos != std::string::npos) {
        std::cout << "Found at: " << pos << '\n';
        std::cout << text.substr(pos, 4) << '\n';
    }
}
```

#### Важни бележки

- `operator[]` не прави проверка за излизане от граници.
- `at()` прави проверка и може да хвърли изключение.
- `std::string` пази размера си и управлява паметта си автоматично.


Още от интерфейса на `std::string` може да видите на [този линк]().

---

### `std::vector`

`std::vector<T>` е динамичен масив. Елементите му се пазят **последователно в паметта**, което го прави много ефективен за често срещани операции.

[Документация на `std::vector`](https://cplusplus.com/reference/vector/vector/)

#### Често използвани операции

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3};

    v.push_back(4);
    v.push_back(5);

    std::cout << v.size() << '\n';     // 5
    std::cout << v[0] << '\n';         // 1
    std::cout << v.back() << '\n';     // 5

    v.pop_back();

    for (int x : v) {
        std::cout << x << ' ';
    }
}
```

#### Основни методи

- `size()` — брой елементи;
- `empty()` — дали е празен;
- `push_back(x)` — добавя в края;
- `pop_back()` — маха последния;
- `front()` / `back()` — първи и последен елемент;
- `clear()` — премахва всички елементи;
- `insert(...)` — вмъкване на позиция;
- `erase(...)` — премахване на елемент или диапазон;
- `reserve(n)` — заделя капацитет;
- `capacity()` — текущ капацитет;
- `resize(n)` — променя логическия размер.

#### Размер и капацитет

Важно е да различаваме:

- **size** — колко елемента има в момента;
- **capacity** — колко елемента могат да се поберат без нова реалокация.

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v;
    v.reserve(100);

    std::cout << "size = " << v.size() << '\n';
    std::cout << "capacity = " << v.capacity() << '\n';
}
```

Още от интерфейса на `std::vector` може да видите на [този линк]().

#### Защо `vector` е важен

`std::vector` е стандартният избор за динамична последователност, освен ако нямаме конкретна причина да използваме друг контейнер. Причините са:

- удобен интерфейс;
- бърз достъп по индекс;
- добра cache locality;
- съвместимост с алгоритмите от STL.

### Общи идеи за `string` и `vector`

И двата типа:

- управляват ресурсите си сами;
- са пример за RAII;
- се вписват естествено в Rule of Zero;
- предоставят итератори чрез `begin()`, `end()`, `cbegin()`, `cend()`.

---

## Итератори

Итераторите са един от фундаменталните механизми в STL. Те осигуряват **унифициран начин за обхождане на елементи**, независимо от конкретния контейнер.

За повече подробности виж [тук](./Iterator_design_pattern/)

Накратко:

- итераторът е обект, който „сочи“ към елемент в колекция
- чрез него можем да се местим, четем и понякога записваме
- STL алгоритмите работят върху диапазони от итератори, а не директно върху конкретен контейнер

Пример:

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {10, 20, 30};

    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << ' ';
    }
}
```

---

## Алгоритми върху диапазони от итератори

Една от големите идеи на STL е разделянето на:

- **контейнери** — пазят данни;
- **итератори** — осигуряват достъп;
- **алгоритми** — извършват операции върху диапазони.

Типичният интерфейс е:

```cpp
algorithm(first, last, ...);
```

където `[first, last)` е диапазон от итератори.

### Non-modifying algorithms

Тези алгоритми не променят самите елементи в диапазона, а ги четат, търсят, сравняват, броят или проверяват.

#### `std::find`

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {3, 5, 8, 13};

    auto it = std::find(v.begin(), v.end(), 8);
    if (it != v.end()) {
        std::cout << "Found: " << *it << '\n';
    }
}
```

#### `std::count`

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 1, 3, 1};
    std::cout << std::count(v.begin(), v.end(), 1) << '\n';
}
```

#### `std::all_of`, `std::any_of`, `std::none_of`

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {2, 4, 6};

    std::cout << std::all_of(v.begin(), v.end(), [](int x) {
        return x % 2 == 0;
    }) << '\n';
}
```

#### `std::for_each`

Полезен е, когато искаме да приложим операция върху всеки елемент.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3};

    std::for_each(v.begin(), v.end(), [](int x) {
        std::cout << x * x << ' ';
    });
}
```

---

### Modifying algorithms

Тези алгоритми променят елементи, подредба или съдържание.

#### `std::sort`

Работи с random access iterators, например върху `vector`.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {5, 1, 4, 2, 3};
    std::sort(v.begin(), v.end());

    for (int x : v) {
        std::cout << x << ' ';
    }
}
```

#### `std::reverse`

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4};
    std::reverse(v.begin(), v.end());

    for (int x : v) {
        std::cout << x << ' ';
    }
}
```

#### `std::replace`

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 2, 3};
    std::replace(v.begin(), v.end(), 2, 99);

    for (int x : v) {
        std::cout << x << ' ';
    }
}
```

#### `std::transform`

`transform` е много полезен, защото превръща елементи от един диапазон в друг.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3};
    std::vector<int> out(v.size());

    std::transform(v.begin(), v.end(), out.begin(), [](int x) {
        return x * 10;
    });

    for (int x : out) {
        std::cout << x << ' ';
    }
}
```

---

### Алгоритми, които логически премахват елементи

Тук е важно да се знае една тънкост: някои алгоритми не изтриват физически елементи от контейнера, а само преместват ненужните към края и връщат нов логически край.

Класически пример е `std::remove`.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 2, 4, 2};

    auto newEnd = std::remove(v.begin(), v.end(), 2);
    v.erase(newEnd, v.end());

    for (int x : v) {
        std::cout << x << ' ';
    }
}
```

---

### Защо алгоритмите са важни

Те позволяват:

- по-кратък и по-изразителен код
- по-добра повторна употреба
- по-малко ръчно писане на цикли
- по-добра абстракция между данни и операции

Добра практика е първо да мислим дали дадена задача не може да се реши със стандартен алгоритъм, вместо веднага да пишем ръчен `for` цикъл.

---

## Smart pointers

Умните указатели съществуват, за да моделират **ownership** на динамично заделени обекти по безопасен начин.

Умният указател е обвиващ клас за обикновен указател, който менажира автоматично паметта на обекта, към който сочи.

Целта е да не използваме директно `new` и `delete`, с цел да не пропуснем да освободим даден ресурс.

При raw pointer:

```cpp
User* p = new User("Alice");
```

имаме много въпроси:

- кой е собственикът на обекта
- кой и кога трябва да извика `delete`
- какво се случва, ако бъде хвърлено изключение
- как да избегнем memory leak

Smart pointer-ите решават тези проблеми чрез RAII. При създаване, умният указател поема собствеността над обекта. При изтриване — автоматично извиква деструктора му.

### Връзка с Rule of Zero

Те са един от основните инструменти, с които можем да пишем класове по Rule of Zero. Вместо сами да пишем деструктор и копиране/местене за управление на ресурс, вграждаме член като:

- `std::unique_ptr<T>`
- `std::shared_ptr<T>`

---

## `std::unique_ptr`

`std::unique_ptr<T>` представя **единствен собственик** на даден обект

Това означава:

- само един `unique_ptr` може да притежава конкретния ресурс в даден момент
- **НЕ** може да се копира
- може да се мести


```cpp
#include <iostream>
#include <memory>

struct User {
    User() { std::cout << "created\n"; }
    ~User() { std::cout << "destroyed\n"; }
};

int main() {
    std::unique_ptr<User> p = std::make_unique<User>();
}
```

Когато `p` излезе от scope, обектът автоматично се унищожава.


>За създаване на `unique_ptr` вместо `new` е по-добре да използваме функцията `std::make_unique`. Прочети повече [тук](https://towardsdev.com/why-std-make-unique-beats-new-in-modern-c-7e2ba653737e).

### Защо не може да се копира

Ако два `unique_ptr` можеха да сочат към един и същи обект като owners, вече нямаше да има „unique“ ownership. Затова копиращите операции са забранени.

```cpp
auto p1 = std::make_unique<int>(42);
// auto p2 = p1; // error
auto p2 = std::move(p1); // ok
```

### Типичен use-case

Използваме `unique_ptr`, когато:

- ownership-ът е еднозначен;
- искаме ясен lifecycle;
- не ни трябва споделено притежание;
- искаме най-леката и най-ясна форма на owning pointer.

В практиката това често е **предпочитаният избор по подразбиране**.

### Подаване във функции

Ако функцията само използва обекта, не е нужно да приема `unique_ptr` по стойност.

```cpp
void printUser(const User* user);
void printUser(const User& user);
```

Ако функцията трябва да вземе ownership:

```cpp
void consume(std::unique_ptr<User> user);
```

и се вика така:

```cpp
consume(std::move(p));
```

### Полезни операции

- `get()` — връща raw pointer;
- `release()` — отказва ownership и връща raw pointer;
- `reset()` — освобождава текущия ресурс;
- `operator*`, `operator->`, `operator bool`

### Custom deleter

`unique_ptr` може да използва и custom deleter. Това е полезно, когато ресурсът не се освобождава с обикновен `delete`.

```cpp
#include <cstdio>
#include <memory>

int main() {
    std::unique_ptr<FILE, decltype(&fclose)> file(std::fopen("data.txt", "r"), &fclose);
}
```

Тук при унищожаване ще се извика `fclose`, а не `delete`.

---

## `std::shared_ptr`

`std::shared_ptr<T>` представя **споделен ownership**.

Няколко `shared_ptr` могат да сочат към един и същ обект. Обектът се унищожава, когато последният owner изчезне.

### Пример

```cpp
#include <iostream>
#include <memory>

int main() {
    auto p1 = std::make_shared<int>(42);
    auto p2 = p1;

    std::cout << p1.use_count() << '\n'; // 2
}
```

>За създаване на `shared_ptr` вместо `new` е по-добре да използваме функцията `std::make_shared`. Прочети повече [тук](https://towardsdev.com/std-make-shared-vs-new-control-blocks-cache-lines-and-performance-5e12c7c013d7).

### Как работи концептуално

Обикновено има control block, в който се пазят:

- броят на `shared_ptr` owner-ите сочещи към обекта
- броят на `weak_ptr` наблюдателите (обикновено включва и бройката на shared_ptr-ите сочещи към обекта)

### Типичен use-case

Използваме `shared_ptr`, когато:

- наистина има споделена отговорност за живота на обекта
- ownership-ът не е еднозначен
- обектът трябва да остане жив, докато поне един собственик го използва

### Кога да внимаваме

`shared_ptr` не е „по-добър raw pointer“. Той има цена:

- допълнителен control block
- броячи
- по-сложна семантика
- възможност за циклични зависимости

Затова не е добре да се използва по подразбиране. По подразбиране предпочитаме `unique_ptr`, а `shared_ptr` само когато наистина има смисъл за споделен ownership.

### Подаване във функции

Ако функцията само чете обекта:

```cpp
void f(const User& user);
void f(const User* user);
void f(const std::shared_ptr<User>& user);
```

Ако във функцията искаме да имаме допълнителен owner:

```cpp
void f(std::shared_ptr<User> user);
```

Подаване по стойност ще увеличи ownership count-а (`use_count`) за времето на извикването.

---

⚠️ Никога не конструирай втори `shared_ptr<T>` от същия `T*`!
Това ще създаде нов брояч и при освобождаване ще доведе до двойно `delete`.

Пример:
```cpp
int* p = new int(42);

std::shared_ptr<int> s1(p);   // control-block #1, use_count = 1
std::shared_ptr<int> s2(p);   // control-block #2, use_count = 1  ← ГРЕШКА!

// при освобождаване:
// s1 -> delete p
// s2 -> delete p  (втори път)  → Undefined Behavior.
```

Тук по-правилно е следното:

```cpp
int* p = new int(42);

std::shared_ptr<int> s1(p);   // control-block #1, use_count = 1
std::shared_ptr<int> s2 = s1; // control-block #2 use_count = 2

// при освобождаване:
// s1 -> нищо
// s2 -> delete p
```

---

## `std::weak_ptr`

`std::weak_ptr<T>` е **не-owning reference** към обект, управляван от `shared_ptr`.

Той:

- не увеличава `use_count()`
- не държи обекта жив, т.е. няма ефект върху живота на обекта
- позволява да проверим дали обектът още съществува
- може да се превърне временно в `shared_ptr` чрез `lock()`

### Пример

```cpp
#include <iostream>
#include <memory>

int main() {
    std::weak_ptr<int> wp;

    {
        auto sp = std::make_shared<int>(42);
        wp = sp;

        if (auto locked = wp.lock()) {
            std::cout << *locked << '\n';
        }
    }

    std::cout << wp.expired() << '\n'; // true
}
```

### Кога се използва

Основно в два случая:

1. когато искаме да *наблюдаваме* обект без да го държим жив
2. когато трябва да прекъснем **циклична зависимост** между `shared_ptr`

---

## Циклична зависимост при `shared_ptr`

Това е един от най-важните практически проблеми.

### Проблемен пример

```cpp
#include <iostream>
#include <memory>
#include <string>

struct Person {
    std::string name;
    std::shared_ptr<Person> partner;

    Person(std::string n) : name(std::move(n)) {
        std::cout << "created: " << name << '\n';
    }

    ~Person() {
        std::cout << "destroyed: " << name << '\n';
    }
};

int main() {
    std::shared_ptr<Person> alice = std::make_shared<Person>("Alice");
    std::shared_ptr<Person> bob = std::make_shared<Person>("Bob");

    alice->partner = bob;
    bob->partner = alice;
}
```

Тук:

- Alice държи Bob чрез `shared_ptr`
- Bob държи Alice чрез `shared_ptr`

Когато външните указатели изчезнат, двата обекта продължават да се държат живи взаимно. `use_count` ще бъде 2 и за двата обекта и няма да се освободят заделените обекти. Това води до memory leak.

### Решение

Едната посока трябва да е `weak_ptr`.

```cpp
#include <iostream>
#include <memory>
#include <string>

struct Person {
    std::string name;
    std::weak_ptr<Person> partner;

    Person(std::string n) : name(std::move(n)) {
        std::cout << "created: " << name << '\n';
    }

    ~Person() {
        std::cout << "destroyed: " << name << '\n';
    }
};

int main() {
    auto alice = std::make_shared<Person>("Alice");
    auto bob = std::make_shared<Person>("Bob");

    alice->partner = bob;
    bob->partner = alice;
}
```

Сега връзката е наблюдаваща, не owning, и заделените обекти ще се освободят коректно без циклични зависимости.

---

## Кога кой smart pointer да предпочитаме

### Предпочитай `unique_ptr`, когато:

- имаш ясен единствен owner
- ownership-ът не трябва да се споделя
- искаш простота и нисък overhead
- моделираш ownership директно и ясно

### Използвай `shared_ptr`, когато:

- обектът действително има няколко owner-а
- lifecycle-ът трябва да продължи, докато поне един owner съществува
- дизайнът естествено изисква shared ownership

### Използвай `weak_ptr`, когато:

- искаш наблюдение без ownership
- искаш да прекъснеш циклична зависимост между `shared_ptr`
- искаш временен достъп чрез `lock()`

---

## Често срещани тънкости

### 1. Не използвай smart pointers без нужда

Ако обектът има ясен owner и не се създава динамично, често не ни трябва smart pointer изобщо. Понякога обикновен композиран обект като член-данна е най-доброто решение.

### 2. `shared_ptr` не решава автоматично всеки проблем

Той решава проблема с ownership-а, но може да създаде нови трудности:

- неясен lifecycle
- цикли
- overhead
- излишно споделяне на оwnership

### 3. `weak_ptr` не може да се dereference-не директно

Трябва да използваме `lock()`:

```cpp
if (auto sp = wp.lock()) {
    std::cout << *sp << '\n';
}
```

### 4. `make_unique` и `make_shared` са предпочитани

Те са по-четими и по-безопасни от ръчното `new`.

```cpp
auto p1 = std::make_unique<User>();
auto p2 = std::make_shared<User>();
```

---

## Обобщение

### Rule of Zero

- Не пишем специални член-функции, ако не управляваме директно ресурс.
- Използваме готови RAII типове.

### `std::string` и `std::vector`

- Това са фундаментални стандартни типове.
- Управляват паметта си сами.
- Имат богат и удобен интерфейс.
- Работят отлично с итератори и STL алгоритми.

### Итератори

- Осигуряват унифициран достъп до елементи.
- Позволяват алгоритмите да бъдат независими от конкретния контейнер.

### Алгоритми

- Работят върху диапазони от итератори.
- Правят кода по-изразителен и по-универсален.
- Често са по-добър избор от ръчно написани цикли.

### Smart pointers

- Моделират ownership по безопасен начин.
- `unique_ptr` — един owner;
- `shared_ptr` — много owner-и;
- `weak_ptr` — наблюдение без ownership.

---

## Финална препоръка

Добрата практическа интуиция е:

1. първо мислим за ownership
2. ако не ни трябва динамична памет, не използваме pointer
3. ако имаме един owner — `unique_ptr`
4. ако имаме истински shared ownership — `shared_ptr`
5. ако искаме наблюдение без ownership или трябва да оправим circular dependency — `weak_ptr`
6. ако можем да композираме класове от готови RAII типове — следваме **Rule of Zero**.

Това е една от най-важните идеи в съвременния C++: не управляваме ресурсите ръчно, ако можем да ги моделираме чрез правилните типове.