#pragma once
#include <vector>
#include <iostream>

template <typename T, typename Comparator>
size_t findIndex(const std::vector<T> &data, const T &obj, Comparator cmp)
{
    size_t start = 0;
    size_t end = data.size();
    while (start < end)
    {
        size_t mid = (start + end) / 2;
        if (cmp(data.at(mid), obj))
        {
            start = mid + 1;
        }
        else
        {
            end = mid;
        }
    }
    return start;
}
template <typename T, typename Comparator>
class PriorityQueue
{
private:
    std::vector<T> data;
    Comparator cmp;

public:
    void push(const T &obj)
    {
        size_t index = findIndex(data, obj, cmp);
        data.insert(data.begin() + index, obj);
    }
    void push(T &&obj)
    {
        size_t index = findIndex(data, obj, cmp);
        data.insert(data.begin() + index, std::move(obj));
    }
    T pop()
    {
        T temp = std::move(data.back());
        data.pop_back();
        return temp;
    }
    T peek() const
    {
        return data.at(data.size() - 1);
    }
    bool empty() const
    {
        return data.empty();
    }
    size_t size() const
    {
        return data.size();
    }
};