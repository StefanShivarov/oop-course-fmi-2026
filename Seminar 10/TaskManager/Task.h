#pragma once
#include <memory>
#include <string>
#include <vector>

class Task {
private:
    std::string title;
    std::string description;
    bool completed = false;
    std::vector<std::unique_ptr<Task>> subtasks;

    Task* findSubtaskByTitle(const std::string& title);
    const Task* findSubtaskByTitle(const std::string& title) const;
    void print(std::ostream& os, size_t indent) const;

public:
    Task(const std::string& title, const std::string& description);

    const std::string& getTitle() const;
    const std::string& getDescription() const;
    bool isCompleted() const;

    void markCompleted();
    void markIncomplete();

    bool addSubtask(const std::string& title, const std::string& description);
    bool removeSubtask(const std::string& title);

    bool containsSubtask(const std::string& title) const;

    Task& operator[](const std::string& title);
    const Task& operator[](const std::string& title) const;

    size_t getSubtaskCount() const;
    size_t getTotalTaskCount() const;
    bool allSubtasksCompleted() const;

    friend std::ostream& operator<<(std::ostream& os, const Task& task);
};