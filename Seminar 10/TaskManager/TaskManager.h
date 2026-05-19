#pragma once
#include <memory>
#include <string>
#include <vector>

class Task;

class TaskManager {
private:
    std::string name;
    std::vector<std::unique_ptr<Task>> tasks;

private:
    Task* findTaskByTitle(const std::string& title);
    const Task* findTaskByTitle(const std::string& title) const;

public:
    explicit TaskManager(const std::string& name);

    const std::string& getName() const;

    bool addTask(const std::string& title, const std::string& description);
    bool removeTask(const std::string& title);

    bool containsTask(const std::string& title) const;

    Task& operator[](const std::string& title);
    const Task& operator[](const std::string& title) const;

    size_t getRootTaskCount() const;
    size_t getTotalTaskCount() const;

    friend std::ostream& operator<<(std::ostream& os, const TaskManager& manager);
};