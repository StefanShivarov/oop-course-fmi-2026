# TaskManager - Система за задачи и подзадачи ☑️

Да се реализира система за управление на задачи. Използвайте _Rule of Zero_.

---

В системата има различни **задачи**.

Всяка задача се характеризира с:
- заглавие
- описание
- статус (`completed` / `not completed`)
- списък от подзадачи

Важно:
- Всяка подзадача принадлежи на точно една задача.
- Една и съща подзадача не може да бъде част от две различни задачи едновременно.

Очаквани функционалности:
- добавяне на подзадача
- премахване на подзадача по заглавие
- намиране на подзадача по заглавие
- отбелязване на задача като завършена
- пресмятане на общия брой подзадачи, включително вложените
- проверка дали всички подзадачи на дадена задача са завършени
- извеждане на стандартния изход

---

Системата се управлява от **TaskManager**.

TaskManager се характеризира с:
- име
- списък от основни задачи

### Функционалности
- добавяне на нова основна задача
- премахване на задача по заглавие
- намиране на задача по заглавие
- достъп до задача по заглавие
- намиране на общия брой задачи в системата, включително вложените подзадачи
- извеждане на информация за всички задачи на стандартния изход

---

### Пример:

```cpp
int main() {
    TaskManager manager("Daily Tasks");

    manager.addTask("Throw the garbage", "Take out the trash in the evening");
    manager.addTask("Work out", "Complete today's training session");
    manager.addTask("Study", "Prepare for tomorrow's classes");

    manager["Work out"].addSubtask("Warm up", "Do 10 minutes of stretching");
    manager["Work out"].addSubtask("Cardio", "Run for 20 minutes");

    manager["Study"].addSubtask("Read OOP notes", "Revise smart pointers");
    manager["Study"].addSubtask("Solve problems", "Practice STL algorithms");

    manager["Throw the garbage"].markCompleted();

    std::cout << manager << '\n';
}
