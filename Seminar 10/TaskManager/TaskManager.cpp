#include "TaskManager.h"
#include "Task.h"
#include <algorithm>
#include <ostream>

TaskManager::TaskManager(const std::string& name)
    : name(name) {
}

const std::string& TaskManager::getName() const {
    return name;
}

bool TaskManager::addTask(const std::string& title, const std::string& description) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
        [&title](const std::unique_ptr<Task>& task) {
            return task->getTitle() == title;
        });

    if (it != tasks.end()) {
        return false;
    }

    tasks.push_back(std::make_unique<Task>(title, description));
    return true;
}

bool TaskManager::removeTask(const std::string& title) {
    auto oldSize = tasks.size();

    std::erase_if(tasks, [&title](const std::unique_ptr<Task>& task) {
        return task->getTitle() == title;
    });

    if (tasks.size() != oldSize) {
        return true;
    }

    for (const auto& task : tasks) {
        if (task->removeSubtask(title)) {
            return true;
        }
    }

    return false;
}

Task* TaskManager::findTaskByTitle(const std::string& title) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
        [&title](const std::unique_ptr<Task>& task) {
            return task->getTitle() == title;
        });

    if (it != tasks.end()) {
        return it->get();
    }

    for (const auto& task : tasks) {
        if (task->containsSubtask(title)) {
            return &((*task)[title]);
        }
    }
    
    return nullptr;
}

const Task* TaskManager::findTaskByTitle(const std::string& title) const {
    auto it = std::find_if(tasks.begin(), tasks.end(),
        [&title](const std::unique_ptr<Task>& task) {
            return task->getTitle() == title;
        });

    if (it != tasks.end()) {
        return it->get();
    }

    for (const auto& task : tasks) {
        if (task->containsSubtask(title)) {
            return &((*task)[title]);
        }
    }

    return nullptr;
}

bool TaskManager::containsTask(const std::string& title) const {
    return findTaskByTitle(title) != nullptr;
}

Task& TaskManager::operator[](const std::string& title) {
    Task* found = findTaskByTitle(title);
    return *found;
}

const Task& TaskManager::operator[](const std::string& title) const {
    const Task* found = findTaskByTitle(title);
    return *found;
}

size_t TaskManager::getRootTaskCount() const {
    return tasks.size();
}

size_t TaskManager::getTotalTaskCount() const {
    size_t total = 0;

    for (const auto& task : tasks) {
        total += task->getTotalTaskCount();
    }

    return total;
}

std::ostream& operator<<(std::ostream& os, const TaskManager& manager) {
    os << "Task manager: " << manager.name << '\n';
    os << "Root tasks: " << manager.getRootTaskCount() << '\n';
    os << "Total tasks (including subtasks): " << manager.getTotalTaskCount() << '\n';

    if (manager.tasks.empty()) {
        os << "<no tasks>\n";
        return os;
    }

    for (const auto& task : manager.tasks) {
        os << *task;
    }

    return os;
}
