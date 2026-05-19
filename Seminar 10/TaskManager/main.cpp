#include <iostream>
#include "Task.h"
#include "TaskManager.h"

int main() {
    TaskManager manager("Daily Tasks");

    manager.addTask("Throw the garbage", "Take out the trash in the evening");
    manager.addTask("Work out", "Complete today's training session");
    manager.addTask("Study", "Prepare for tomorrow's classes");

    if (manager.containsTask("Work out")) {
        manager["Work out"].addSubtask("Warm up", "Do 10 minutes of stretching");
        manager["Work out"].addSubtask("Cardio", "Run for 20 minutes");
        manager["Work out"].addSubtask("Strength training", "Do push-ups and burpees");
    }

    if (manager.containsTask("Study")) {
        manager["Study"].addSubtask("Read OOP notes", "Revise smart pointers");
        manager["Study"].addSubtask("Solve problems", "Practice STL algorithms");
        manager["Study"].addSubtask("Review homework", "Check yesterday's solutions");
    }

    if (manager.containsTask("Read OOP notes")) {
        manager["Read OOP notes"].addSubtask("Review unique_ptr", "Read examples with unique ownership");
        manager["Read OOP notes"].addSubtask("Review shared_ptr", "Read examples with shared ownership");
        manager["Read OOP notes"].markCompleted();
    }

    if (manager.containsTask("Throw the garbage")) {
        manager["Throw the garbage"].markCompleted();
    }

    if (manager.containsTask("Warm up")) {
        manager["Warm up"].markCompleted();
    }

    std::cout << manager << '\n';

    std::cout << "All subtasks of Study completed: "
              << std::boolalpha
              << manager["Study"].allSubtasksCompleted()
              << '\n';

    return 0;
}
