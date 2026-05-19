#include "Task.h"
#include <algorithm>
#include <ostream>

Task::Task(const std::string& title, const std::string& description)
    : title(title), description(description) {
}

const std::string& Task::getTitle() const {
    return title;
}

const std::string& Task::getDescription() const {
    return description;
}

bool Task::isCompleted() const {
    return completed;
}

void Task::markCompleted() {
    completed = true;
}

void Task::markIncomplete() {
    completed = false;
}

bool Task::addSubtask(const std::string& title, const std::string& description) {
    auto it = std::find_if(subtasks.begin(), subtasks.end(),
        [&](const std::unique_ptr<Task>& subtask) {
            return subtask->getTitle() == title;
        });

    if (it != subtasks.end()) {
        return false;
    }

    subtasks.push_back(std::make_unique<Task>(title, description));
    return true;
}

bool Task::removeSubtask(const std::string& title) {
    auto oldSize = subtasks.size();

    std::erase_if(subtasks, [&](const std::unique_ptr<Task>& subtask) {
        return subtask->getTitle() == title;
    });

    // alternatively:
    /*
    int pos = 0;
    for (const auto& subtask : subtasks) {
        if (subtask->getTitle() == title) {
            break;
        }
        pos++;
    }
    subtasks.erase(subtasks.begin() + pos);
    */

    if (subtasks.size() != oldSize) {
        return true;
    }

    for (const auto& subtask : subtasks) {
        if (subtask->removeSubtask(title)) {
            return true;
        }
    }

    return false;
}

Task* Task::findSubtaskByTitle(const std::string& title) {
    auto it = std::find_if(subtasks.begin(), subtasks.end(),
        [&](const std::unique_ptr<Task>& subtask) {
            return subtask->getTitle() == title;
        });

    if (it != subtasks.end()) {
        return it->get();
    }

    for (const auto& subtask : subtasks) {
        Task* found = subtask->findSubtaskByTitle(title);
        if (found) {
            return found;
        }
    }

    return nullptr;
}

const Task* Task::findSubtaskByTitle(const std::string& title) const {
    auto it = std::find_if(subtasks.begin(), subtasks.end(),
        [&](const std::unique_ptr<Task>& subtask) {
            return subtask->getTitle() == title;
        });

    if (it != subtasks.end()) {
        return it->get();
    }

    for (const auto& subtask : subtasks) {
        const Task* found = subtask->findSubtaskByTitle(title);
        if (found) {
            return found;
        }
    }

    return nullptr;
}

bool Task::containsSubtask(const std::string& title) const {
    return findSubtaskByTitle(title) != nullptr;
}

Task& Task::operator[](const std::string& title) {
    Task* found = findSubtaskByTitle(title);
    return *found;
}

const Task& Task::operator[](const std::string& title) const {
    const Task* found = findSubtaskByTitle(title);
    return *found;
}

size_t Task::getSubtaskCount() const {
    return subtasks.size();
}

size_t Task::getTotalTaskCount() const {
    size_t total = 1;

    for (const auto& subtask : subtasks) {
        total += subtask->getTotalTaskCount();
    }

    return total;
}

bool Task::allSubtasksCompleted() const {
    return std::all_of(subtasks.begin(), subtasks.end(),
    [](const std::unique_ptr<Task>& subtask) {
            return subtask->isCompleted() && subtask->allSubtasksCompleted();
    });
}

void Task::print(std::ostream& os, size_t indent) const {
    for (size_t i = 0; i < indent; i++) {
        os << ' ';
    }

    os << "- " << title
       << " | " << (completed ? "completed" : "not completed")
       << " | " << description << '\n';

    for (const auto& subtask : subtasks) {
        subtask->print(os, indent + 2);
    }
}

std::ostream& operator<<(std::ostream& os, const Task& task) {
    task.print(os, 0);
    return os;
}
