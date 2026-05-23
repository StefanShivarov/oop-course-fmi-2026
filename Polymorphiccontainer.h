#pragma once
#include <memory>
#include <vector>
#include <concepts>
#include <stdexcept>

template<typename T>
concept Cloneable = requires(const T& t)
{ 
    { t.clone() } -> std::convertible_to<std::unique_ptr<T>>;// Concept -T must have clone(), and returns unique_ptr<T>

};


template<Cloneable T>

class UniqueContainer
{
private:
    std::vector<std::unique_ptr<T>> items;
public:

    UniqueContainer() = default;
    UniqueContainer(UniqueContainer&&) noexcept = default;
    UniqueContainer& operator=(UniqueContainer&&) noexcept = default;

    UniqueContainer(const UniqueContainer& other)
    {
        items.reserve(other.items.size());
        for (const auto& p : other.items)
        {
            items.push_back(p->clone());
        }
    }

    UniqueContainer& operator=(const UniqueContainer& other)
    {
        if (this != &other)
        {
            UniqueContainer tmp(other);     
            std::swap(items, tmp.items); 
        }
        return *this;
    }
  
    void push(std::unique_ptr<T> obj)
    {
        items.push_back(std::move(obj));
    }

    void remove(std::size_t index)
    {
        if (index >= items.size())
        {
            throw std::out_of_range("index out of range");
        }
        items.erase(items.begin() + index);
    }

    T& operator[](std::size_t index)
    {
        if (index >= items.size())
        {
            throw std::out_of_range("index out of range");
        }
        return *items[index];
    }

    const T& operator[](std::size_t index) const
    {
        if (index >= items.size())
        {
            throw std::out_of_range("index out of range");
        }
        return *items[index];
    }

    std::size_t size() const 
    {
        return items.size();
    }

   
    struct Iterator
    {
        using It = typename std::vector<std::unique_ptr<T>>::iterator;
        It current;

        Iterator(It it):current(it) {}

        T& operator*() const
        {
            return **current;
        }

        T* operator->() const 
        {
            return current->get();
        }

        Iterator& operator++() 
        {
            current++;
            return *this; 
        }
        Iterator operator++(int)
        {
            Iterator tmp = *this; 
            current++;
            return tmp;
        }

        bool operator==(const Iterator& other) const 
        {
            return current == other.current; 
        }
        bool operator!=(const Iterator& other) const 
        {
            return current != other.current;
        }
    };

    struct ConstIterator
    {
        using It = typename std::vector<std::unique_ptr<T>>::const_iterator;
        It current;

        ConstIterator(It it):current(it) {}

        const T& operator*() const
        { 
            return **current; 
        }

        const T* operator->() const
        {
            return current->get(); 
        }

        ConstIterator& operator++() 
        {
            current++;
            return *this; 
        }
        ConstIterator operator++(int) 
        { 
            ConstIterator tmp = *this;
            current++;
            return tmp; 
        }

        bool operator==(const ConstIterator& other) const 
        {
            return current == other.current;
        }
        bool operator!=(const ConstIterator& other) const 
        {
            return current != other.current;
        }
    };

    Iterator begin() 
    {
        return Iterator(items.begin()); 
    }
    Iterator end() 
    {
        return Iterator(items.end()); 
    }

    ConstIterator begin() const 
    {
        return ConstIterator(items.begin());
    }
    ConstIterator end() const 
    {
        return ConstIterator(items.end()); 
    }

};



template<Cloneable T>

class SharedDeepContainer
{
private:
    std::vector<std::shared_ptr<T>> items;

public:

    SharedDeepContainer() = default;
    SharedDeepContainer(SharedDeepContainer&&) noexcept = default;
    SharedDeepContainer& operator=(SharedDeepContainer&&) noexcept = default;

    SharedDeepContainer(const SharedDeepContainer& other)
    {
        items.reserve(other.items.size());
        for (const auto& p : other.items)
        {
            items.push_back(p->clone());
        }
    }

    SharedDeepContainer& operator=(const SharedDeepContainer& other)
    {
        if (this != &other)
        {
            SharedDeepContainer tmp(other);
            std::swap(items, tmp.items);
        }
        return *this;
    }

    void push(std::unique_ptr<T> obj)
    {
        items.push_back(std::shared_ptr<T>(std::move(obj)));
    }
    void pushShared(std::shared_ptr<T> obj)
    {
        items.push_back(std::move(obj));
    }
    void remove(std::size_t index)
    {
        if (index >= items.size())
        {
            throw std::out_of_range("index out of range");
        }
        items.erase(items.begin() + index);
    }
    T& operator[](std::size_t index)
    {
        if (index >= items.size())
        {
            throw std::out_of_range("index out of range");
        }
        return *items[index];
    }

    const T& operator[](std::size_t index) const
    {
        if (index >= items.size())
        {
            throw std::out_of_range("index out of range");
        }
        return *items[index];
    }

    std::size_t size() const 
    {
        return items.size(); 
    }
 
    struct Iterator
    {
        using It = typename std::vector<std::shared_ptr<T>>::iterator;
        It current;

        Iterator(It it):current(it) {}

        T& operator*() const 
        {
            return **current;
        }
        T* operator->() const 
        {
            return current->get();
        }
        Iterator& operator++() 
        {
            current++;
            return *this;
        }
        Iterator  operator++(int) 
        {
            Iterator tmp = *this; 
            current++; 
            return tmp; 
        }
        bool operator==(const Iterator& o) const 
        {
            return current == o.current; 
        }
        bool operator!=(const Iterator& o) const 
        {
            return current != o.current; 
        }
    };

    struct ConstIterator
    {
        using It = typename std::vector<std::shared_ptr<T>>::const_iterator;
        It current;

        ConstIterator(It it):current(it) {}

        const T& operator*() const 
        {
            return **current;
        }
        const T* operator->() const 
        {
            return current->get();
        }

        ConstIterator& operator++() 
        { 
            ++current; 
            return *this; 
        }
        ConstIterator  operator++(int)
        {
            ConstIterator tmp = *this;
            current++;
            return tmp; 
        }
        bool operator==(const ConstIterator& o) const 
        {
            return current == o.current; 
        }
        bool operator!=(const ConstIterator& o) const 
        {
            return current != o.current;
        }
    };

    Iterator begin() 
    {
        return Iterator(items.begin()); 
    }
    Iterator end() 
    {
        return Iterator(items.end()); 
    }
    ConstIterator begin() const 
    {
        return ConstIterator(items.begin()); 
    }
    ConstIterator end() const 
    {
        return ConstIterator(items.end()); 
    }
 
};



template<typename T>         
class SharedShallowContainer
{
private:
    std::vector<std::shared_ptr<T>> items;

public:
    SharedShallowContainer() = default;

    void push(std::shared_ptr<T> obj)
    {
        items.push_back(std::move(obj));
    }

    void remove(std::size_t index)
    {
        if (index >= items.size())
        {
            throw std::out_of_range("index out of range");
        }
        items.erase(items.begin() + index);
    }

    T& operator[](std::size_t index)
    {
        if (index >= items.size())
        {
            throw std::out_of_range(" index out of range");
        }
        return *items[index];
    }

    const T& operator[](std::size_t index) const
    {
        if (index >= items.size())
        {
            throw std::out_of_range(" index out of range");
        }
        return *items[index];
    }

    std::size_t size() const 
    {
        return items.size();
    }

    struct Iterator
    {
        using It = typename std::vector<std::shared_ptr<T>>::iterator;
        It current;

        Iterator(It it):current(it) {}

        T& operator*() const 
        {
            return **current;
        }
        T* operator->() const 
        {
            return current->get();
        }
        Iterator& operator++() 
        { 
            current++;
            return *this; 
        }
        Iterator operator++(int) 
        {
            Iterator tmp = *this;
            current++; 
            return tmp;
        }
        bool operator==(const Iterator& o) const
        {
            return current == o.current; 
        }
        bool operator!=(const Iterator& o) const 
        {
            return current != o.current; 
        }
    };

    struct ConstIterator
    {
        using It = typename std::vector<std::shared_ptr<T>>::const_iterator;
        It current;

        ConstIterator(It it):current(it) {}
       const T& operator*() const
        {
            return **current;
        }
       const T* operator->() const
        {
            return current->get();
        }
        ConstIterator& operator++()
        {
            current++;
            return *this;
        }
        ConstIterator operator++(int)
        {
            ConstIterator tmp = *this;
            current++;
            return tmp;
        }
        bool operator==(const ConstIterator& o) const
        {
            return current == o.current;
        }
        bool operator!=(const ConstIterator& o) const
        {
            return current != o.current;
        }
    };

    Iterator begin() 
    {
        return Iterator(items.begin());
    }
    Iterator end()
    {
        return Iterator(items.end()); 
    }
    ConstIterator begin() const 
    {
        return ConstIterator(items.begin()); 
    }
    ConstIterator end() const 
    {
        return ConstIterator(items.end());
    }
   
};
