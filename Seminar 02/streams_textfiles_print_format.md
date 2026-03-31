# Потоци. Четене и писане в текстов файл. std::print и std::format

### Видове потоци

Поток (stream) - последователност от байтове данни влизащи в и излизащи от програмата.

- При операциите за вход, байтовете идват от източник за вход (клавиатура, файл, мрежа или друга програма)
- При операциите за изход, байтовете данни излизат от програмата и се "вливат" във външно "устройство" (конзола, файл, мрежа или друга програма)
- Потоците служат като посредници между програмите и самите IO устройства по начин, който освобождава програмиста от боравене с тях.
- Потокът дефинира интерфейс с операции върху него, които не зависят от избора на IO устройство

  ![enter image description here](https://github.com/GeorgiTerziev02/Object-oriented_programming_FMI/raw/main/Sem.%2002/img/streams.png)  
  За да извърши вход или изход, една C++ програма:

  - Създава поток;
  - Свързва потока с IO устройството (напр. конзола, клавиатура, файл, мрежа или друга програма);
  - Извършва операции за вход/изход върху потока;
  - Прекъсва връзка с потока;
  - Освобождава потока;

Видове потоци:

- Потоци за вход ([istream](https://en.cppreference.com/w/cpp/io/basic_istream)).
- Потоци за изход ([ostream](https://en.cppreference.com/w/cpp/io/basic_ostream)).

![enter image description here](https://github.com/GeorgiTerziev02/Object-oriented_programming_FMI/raw/main/Sem.%2002/img/hierarchy.png)

##### Пример за работа с вход от конзолата. [cin](https://en.cppreference.com/w/cpp/io/cin) (обект от тип istream).

```c++
#include <iostream>

int main() {
	int a, b;
	std::cin >> a >> b; // read two integers from the console input stream
}
```

Четем от стандартния вход.

##### Пример за работа с поток за изход. [cout](https://en.cppreference.com/w/cpp/io/cout) (обект от тип ostream).

```c++
#include <iostream>

int main() {
	int a = 10;
	int b = 12;
	int c = a + b;

	std::cout << a << " + " << b << " = " << c << std::endl; // write two integers in the console output stream
}
```


```plaintext
                 ios
              /        \
       istream          ostream
      /       \        /       \
  ifstream     iostream      ofstream
              /       \
        fstream      stringstream
```

Всички потоци за вход (`ifstream`) в себе си съдържат **get** указател. Всички потоци за изход (`ofstream`) в себе си съдържат **put** указател. 

В себе си `fstream` съдържа `един` **get** и **put** указател, като при входна операция, след изходна, трябва да се прави синхронизация на потока: `flush() <=> seekg(tellg())`



## Основно правило
**Потоците НЕ се копират.**  
Винаги се подават **по референция**.
В стандарта на C++ **копирането на потоци е забранено**.
Класовете `iostream` имат изтрит копи-конструктор (deleted copy constructor). Ако се опитате да подадете поток без `&`, кодът просто няма да се компилира.

---

### 1. Подаване на `ifstream` (четене)

```cpp
#include <fstream>

void readData(std::ifstream& ifs) {
    int x;
    ifs >> x;   // чете от файла
}
```
## Форматиран вход и изход
- **Форматиран вход:** `<Поток за вход> >> <Обект>`
- **Форматиран изход:** `<Поток за изход> << <Обект>`

Операторите `>>` и `<<`:
- Пропускат whitespaces (`' '`), но не и newlines (`\n`)
- Връщат референция към потока, което позволява да ги **chain**-ваме

**Пример:**

```c++
std::cout << "Test product: " << 3 << " * " << 7 << " = " << 21 << std::endl;
```

- `std::cout` е обект от тип `ostream`, като това ни позволява да използваме оператор `<<`
- `std::cin` е обект от тип `istream`, като това ни позволява да използваме оператор `>>`

## Неформатиран вход и изход

### Неформатиран изход:

- `ostream& put(char ch)` - поставя символ на позицията, където сочи **put** указателя, като премества **put** указателя една позиция напред
- `ostream& write(const char* str, size)` - писане в двоичен файл

### Неформатиран вход:

- `int get()` - връща ASCII код, отговарящ на символа, към който сочи **get** указателя, като го премества една позиция напред
- `int peek()` - връща ASCII код, отговарящ на символа, към който сочи **get** указателя, като **НЕ** го мести напред
- `istream& get(<buffer>, <size>, <delimiter>)` - прочита символи от потока, докато не се прочетат **(size - 1)** на брой символа, или докато не се срещне подаденият разделител. По **default**, ако не означим разделител, се използва newline (`\n`).
- `istream& getline(<buffer>, <size>, <delimiter>)` - прочита символи от потока, докато не се прочетат **size** на брой символа, или докато не се срещне подаденият разделител. По **default**, ако не означим разделител, се използва newline (`\n`).
- `istream& read(char* str, size)` - четене от двоичен файл
- `istream& ignore()` - премества **get** указателя с една позиция
- `istream& ignore(<size>, <delimiter>)` - премества **get** указателя с **n** позиции напред, или докато срещне подадения разделител

**ВАЖНО!!!** При `.get()` разделителят не се прочита, докато при `.getline()` се прочита

## Позициониране при потоците за вход и изход

### Позициониране при потоците за изход

- `.tellp()` - връща позицията на **put** указателя
- `.seekp(<position>)` - мести **put** указателя до дадения **position**
- `.seekp(<offset>, <direction>)` - мести **put** указателя с **offset** на брой позиции спрямо **direction**

### Позициониране при потоците за вход

- `.tellg()` - връща позицията на **get** указателя
- `.seekg(<position>)` - мести **get** указателя до дадената позиция
- `.seekg(<offset>, <direction>)` -  мести **get** указателя с **offset** на брой позиции спрямо **direction**

`direction` може да бъде една от следните позиции:
- `std::ios::beg` - начало на файла
- `std::ios::cur` - текуща позиция във файла
- `std::ios::end` - край на файла

### [Режими на работа](https://en.cppreference.com/w/cpp/io/ios_base/openmode)

```c++
std::ifstream str("file.txt", <режим на работа>).
```

### Комбиниране на режими на работа

```c++
std::ofstream ofs(<file_name>, std::ios::out | std::ios::app);
```

Режимът на работа е цяло число. Ако искаме да зададем повече от един ги изреждаме с двоично или('|').

| ios              | Ефект:                                                                                                                           |   Бит  |
| ---------------- | -------------------------------------------------------------------------------------------------------------------------------- | --- |
| ios::in          | Отваря файл за извличане.                                                                                                        | 1   |
| ios::out         | Отваряне на файл за вмъкване. Допуска се вмъкване на произволни места във файла. Ако файлът съществува, съдържанието се изтрива. | 2   |
| ios::ate         | Отваря за вмъкване и установява указателя put в края на файла. Допуска вмъкване на произволни места.                             | 4   |
| ios::app         | Отваря за вмъкване и установява указателя put в края на файла                                                                    | 8   |
| ios::trunc       | Ако файлът съществува, съдържанието се изтрива.                                                                                  | 16  |
| ios::binary      | Превключва режима от текстов в двоичен                                                                                           | 32  |
| ios::\_Nocreate  | Отваря за вмъкване, само ако файлът с указаното име съществува.                                                                  | 64  |
| ios::\_Noreplace | Отваря за вмъкване само ако файлът с указаното име не съществува.                                                                | 128 |


### [Флагове на състоянията на потока](https://en.cppreference.com/w/cpp/io/ios_base/iostate)

| Флаг:                                                       | Значение:                                                                   |
| ----------------------------------------------------------- | --------------------------------------------------------------------------- |
| `.bad()`                                                       | Има невъзстановима грешка в потока. |
| ``.fail()``                                                      | Последната входно/изходна операция е невалидна.                             |
| ``.good() ``                                                     | Потокът няма зададени флагове за грешка.                                      |
| ``.clear()``                                                     | Изчиства състоянието на потока (Вече good() ще върне истина).               |
| [``.eof()``](https://en.cppreference.com/w/cpp/io/basic_ios/eof) | Достигнат е края на файла.


### Работа с поток за вход от файл ([ifstream](https://en.cppreference.com/w/cpp/io/basic_ifstream))

Пример за четене от файл!

```c++
#include <iostream>
#include <fstream>

constexpr char FILE_NAME[] = "myFile.txt";

int main() {
	std::ifstream file(FILE_NAME); // create input file stream associated with myFile.txt

	if (!file.is_open()) {
		std::cout << "Error!" << std::endl;
		return -1;
	}

	int a, b;
	file >> a >> b;

	file.close();
}
```

Пример за прочитане на цялото съдържание файл:

```c++
#include <iostream>
#include <fstream>

constexpr int BUFF_SIZE = 1024;
constexpr char FILE_NAME[] = "myFile.txt";

int main() {
	std::ifstream file(FILE_NAME);

	if (!file.is_open()) {
		std::cout << "Error!" << std::endl;
		return -1;
	}

	while (!file.eof()) {
		char buff[BUFF_SIZE];
		file.getline(buff, BUFF_SIZE);

		//do something with the line
		std::cout << buff << std::endl;
	}

	file.close();
}
```

### Работа с поток за изход към файл ([ofstream](https://en.cppreference.com/w/cpp/io/basic_ofstream))

```c++
#include <iostream>
#include <fstream>

constexpr char FILE_NAME[] = "myFile.txt";

int main() {
	std::ofstream file(FILE_NAME);  // create output file stream associated with myFile.txt

	if (!file.is_open()) {
		std::cout << "Error!" << std::endl;
		return -1;
	}

	int a = 3;
	int b = 10;

	file << a << " " << b << " " << a + b << std::endl; // write into the output file stream

	if(!file.eof()) { //check if the file has ended
		std::cout << "The file contains more data after the two integers!" << std::endl;
	}

	file.close();
}
```

- (istream) [get](https://en.cppreference.com/w/cpp/io/basic_istream/get) - функция, която чете следващия character в потока.
- (ostream) [put](https://en.cppreference.com/w/cpp/io/basic_ostream/put) - функция, която поставя на следваща позиция character в потока.
- ifstream или istream - съдържа get указател, който реферира елемента, който ще се прочете при следващата входна операция.
- ofstream или ostream - съдържа put указател, който реферира мястото, където ще се запише следващият елемент.
- put и get не са [форматирани](https://www.geeksforgeeks.org/unformatted-input-output-operations-in-cpp/) за разлика от operator<< и operator>>, тоест не пропускат whitespaces и др.
---

## Управление на грешки в файловите потоци в C++ (`fstream`)

Когато работим с файлови потоци в C++ (`std::fstream`, `std::ifstream`, `std::ofstream`), могат да възникнат грешки, които засягат функционалността на различни операции.

---

### **Флагове за грешки в `std::fstream`**

Файловите потоци в C++ (`std::fstream`) използват вътрешни флагове за посочване на различни видове грешки:

| Флаг      | Условие на задействане                                                    | Ефект върху потока                                                 |
| --------- | ------------------------------------------------------------------------- | ------------------------------------------------------------------ |
| `eofbit`  | Достигнат е краят на файла (EOF)                                          | Спира четенето, но не означава сериозна грешка                     |
| `failbit` | Грешен формат на входа (например опит за четене на число от текст)        | Блокира входните операции като `>>`, `get()`, `seekg()`, `seekp()` |
| `badbit`  | Сериозна повреда на потока (например хардуерен проблем или повреден файл) | Напълно блокира потока, трудно за възстановяване                   |

---
**ВАЖНО!!!** Ако се вдигне `badbit` => вдига се `failbit`

## **Операции и тяхната работа при различни флагове**

| Операция     | Работи при `eofbit` | Работи при `failbit` | Работи при `badbit` |
| ------------ | ------------------- | -------------------- | ------------------- |
| `read()`     | ❌                  | ❌                   | ❌                  |
| `write()`    | ✅                  | ✅                   | ❌                  |
| `seekg()`    | ❌                  | ❌                   | ❌                  |
| `seekp()`    | ✅                  | ❌                   | ❌                  |
| `clear()`    | ✅                  | ✅                   | ✅                  |
| `eof()`      | ✅                  | ✅                   | ❌                  |
| `fail()`     | ✅                  | ✅                   | ❌                  |
| `bad()`      | ✅                  | ✅                   | ✅                  |
| `get()`      | ❌                  | ❌                   | ❌                  |
| `getline()`  | ❌                  | ❌                   | ❌                  |
| `operator>>` | ❌                  | ❌                   | ❌                  |
| `operator<<` | ✅                  | ✅                   | ❌                  |

**Забележка:**

- `clear()` винаги работи и може да бъде използван за възстановяване на потока.
- `seekg()` и `seekp()` не работят, докато има активен `failbit` или `badbit`.
- `operator<<` работи дори при `eofbit` и `failbit`, защото записът може да продължи въпреки EOF или грешен вход.

---

## **Кога се активират `failbit` и `badbit`?**

### **`failbit` – Грешен входен формат**

✅ **Пример: Опит за четене на число, но срещаме текст**

```cpp
std::ifstream ifs("file.txt");
int num;
ifs >> num; // Ако във файла има "hello", `failbit` ще се активира

if (ifs.fail()) {
    std::cout << "failbit е активен!" << std::endl;
}
```

❌ **Резултат:** `failbit` се активира, защото входът не е число.

---

### **`badbit` – Критична грешка в потока**

✅ **Пример: Ръчно задаване на `badbit` за симулиране на грешка**

```cpp
std::ifstream ifs("file.txt");
ifs.setstate(std::ios::badbit); // Симулиране на `badbit` грешка

if (ifs.bad()) {
    std::cout << "badbit е активен!" << std::endl;
}
```

🔴 **Ако `badbit` е активен, потокът става напълно неизползваем.**

---

### **`eofbit` – Достигнат е краят на файла**

✅ **Пример: Четене до края на файла**

```cpp
std::ifstream ifs("file.txt");
char ch;
while (ifs.get(ch)) {
    std::cout << ch;
}

if (ifs.eof()) {
    std::cout << "Край на файла!" << std::endl;
}
```

📌 **Забележка:** `eofbit` **не означава грешка**, но предотвратява по-нататъшно четене.

---

## **Как да изчистим грешките и да продължим работа?**

Ако някой от тези флагове се активира, **трябва да извикаме `clear()`**, за да възстановим нормалното състояние на потока.

✅ **Поправка с `clear()`**

```cpp
std::ifstream ifs("file.txt");

int num;
ifs >> num; // Ако четенето е неуспешно, `failbit` се активира

if (ifs.fail()) {
    std::cout << "failbit открит! Изчистване..." << std::endl;
    ifs.clear();  // Изчистване на всички грешки
    ifs.seekg(0); // Връщане на позицията на курсора в началото на файла
}
```

---

## **Обобщение**

| Флаг      | Причина                    | Ефект                              | Решение                |
| --------- | -------------------------- | ---------------------------------- | ---------------------- |
| `eofbit`  | Достигнат е краят на файла | Спира четенето                     | `clear(); seekg(0);`   |
| `failbit` | Грешен входен формат       | Блокира входа, `seekg()` не работи | `clear(); seekg();`    |
| `badbit`  | Критична повреда на потока | Потокът напълно спира да работи    | Обикновено непоправимо |

## _(за любознателните)_: `stringstream `


- Поток за работа със символни низове
- Достъп до всички методи на `iostream` (както при **fstream**, трябва да синхронизираме потока)
- Позволява форматирано четене / писане от низове
- Автоматично преобразуване между типовете при четене / писане

**Пример:**

```c++
#include <iostream>
#include <sstream>

constexpr size_t SIZE = 1024;

int main()
{
	std::stringstream ss("21 42.42 ABC");

	int x;
	ss >> x;

	double d;
	ss >> d;

	char buff[SIZE + 1];
	ss >> buff;

	std::cout << x << " " << d << " " << buff << std::endl; // 21 42.42 ABC

	return 0;
}
```



## `std::print`, `std::println`, `std::format` (C++20/23)

---

### `std::print` и `std::println` — директен печат с формат

```cpp
#include <print>   // std::print, std::println
```

- `std::print(fmt, args...)` печата **без** автоматичен `\n`
- `std::println(fmt, args...)` печата **с** автоматичен `\n`

```cpp
#include <print>

int main() {
    int a = 3;
    int b = 7;

    std::print("{} + {} = {}", a, b, a + b);
    std::println("abcd"); // добавя '\n'
}
```

---

### Принтиране към различни потоци (не само `std::cout`)

Можем да печатаме към **всеки `std::ostream`** (файл, `std::cerr`, stringstream, ...), като ползваме overload-а с първи аргумент поток:

```cpp
#include <print>
#include <iostream>

int main() {
    std::println(std::cerr, "Error: code={} msg={}", 404, "Not found");
}
```

#### Към файл (`std::ofstream`)
```cpp
#include <print>
#include <fstream>

int main() {
    std::ofstream logsFile("log.txt");
    if (!logsFile.is_open()) {
        std::println(std::cerr, "Cannot open log.txt");
        return 1;
    }

    std::println(logsFile, "[{}] {}", 1, "Hello from file!");
    std::println(logsFile, "value={:.3f}", 3.14159);
}
```

#### Унифицираща функция: печат към произволен поток
```cpp
#include <print>
#include <ostream>

void printStudent(std::ostream& out, const Student& st) {
    std::println(out, "Student: name='{}', fn={}", st.name, st.fn);
}
```

---

### Форматни шаблони (patterns) — placeholders `{}`

Форматът използва **placeholders** от вида `{}`.

#### “По ред” (automatic indexing)
```cpp
#include <print>

int main() {
    std::println("Hello {}, you are {} years old.", "Alice", 20);
}
```

#### Позиционни аргументи (reordering)
```cpp
#include <print>

int main() {
    std::println("{1} then {0}", "first", "second"); // "second then first"
}
```

---

### Спецификатори след `:` — ширина, подравняване, precision, bases

#### Ширина и подравняване
- `:<8` — left align, ширина 8
- `:>8` — right align
- `:^8` — center

```cpp
#include <print>

int main() {
    std::println("|{:<8}|{:^8}|{:>8}|", "left", "center", "right");
}
```

#### Запълване (fill)
Първият символ е fill, после подравняване:

```cpp
#include <print>

int main() {
    std::println("|{:*<8}|{:->8}|{:.^8}|", "a", "b", "c");
}
```

#### Цели числа — бази и префикси
- `:d` (default) — десетично
- `:x` / `:X` — hex
- `:o` — oct
- `:b` — bin
- `:#x` — с `0x` префикс (аналогично за `b`, `o`)

```cpp
#include <print>

int main() {
    int n = 255;
    std::println("dec={} hex={:#x} HEX={:#X} bin={:#b} oct={:#o}", n, n, n, n, n);
}
```

#### Floating point — precision
- `:.2f` — 2 цифри след точката
- `:.3e` — scientific
- `:.4g` — general

```cpp
#include <print>

int main() {
    double pi = 3.1415926535;
    std::println("pi={:.2f}  sci={:.3e}  gen={:.4g}", pi, pi, pi);
}
```

---

##  `std::format`

`std::format` е стандартна C++20 функция за type-safe форматиране на текст по шаблон (format string) с {} placeholders.

- Приема форматен низ (напр. "x={} y={:.2f}") и аргументи.

- Поддържа спецификатори като ширина, подравняване, запълване, бази (hex/bin), precision за floating point и др.

- Връща std::string.

```cpp
#include <format>

int main() {
    std::string s = std::format("id={} x={:.2f}", 42, 3.14159);
    std::println("{}", s);
}
```


