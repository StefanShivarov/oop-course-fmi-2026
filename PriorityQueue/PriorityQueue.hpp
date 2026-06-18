#ifndef PRIORITYQUEUE_PRIORITYQUEUE_H
#define PRIORITYQUEUE_PRIORITYQUEUE_H
#include <concepts>
#include <vector>
#include <algorithm>
using namespace std;

struct BiggestFirst {
    bool operator()(int a, int b) const {
        return a > b;
    }
};
struct SmallestFirst {
    bool operator()(int a, int b) const {
        return a < b;
    }
};
struct LongestFirst {
    bool operator()(const std::string& a, const std::string& b) const {
        return a.length() > b.length();
    }
};
struct ShortestFirst {
    bool operator()(const std::string& a, const std::string& b) const {
        return a.length() < b.length();
    }
};

template<typename C, typename T>
concept ComparatorFor = requires(C cmp, T a, T b) {
    { cmp(a, b) } -> std::convertible_to<bool>;
};

template <typename T, typename Comparator>
requires ComparatorFor<Comparator, T> class PriorityQueue {
    std::vector<T> queue;
    Comparator cmp;
    public:
    void push(const T& item) {
        queue.push_back(item);
        sort(queue.begin(), queue.end(), [this](const T& a, const T& b) {
            return cmp(a, b);
        });
    }
    void push(T&& item) {
        queue.push_back(std::move(item));
        sort(queue.begin(), queue.end(), [this](const T& a, const T& b) {
            return cmp(a, b);
        });
    }
    T pop() {
        if (queue.empty()) {
            throw std::out_of_range("Queue is empty");
        }
        T item = std::move(queue.front());
        queue.erase(queue.begin());
        return item;
    }
    const T& peek() const {
        if (queue.empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return queue.front();
    }
    bool empty() const {
        return queue.empty();
    }
    size_t size() const {
        return queue.size();
    }
};

#endif //PRIORITYQUEUE_PRIORITYQUEUE_H
