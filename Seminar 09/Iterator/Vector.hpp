#pragma once
#include <iostream>

template <typename T>
class Vector {
public:
    Vector();
    explicit Vector(size_t capacity);

    Vector(const Vector& other);
    Vector& operator=(const Vector& other);
    Vector(Vector&& other) noexcept;
    Vector& operator=(Vector&& other) noexcept;
    ~Vector();

    size_t size() const;
    size_t capacity() const;
    bool empty() const;
    void clear();

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    void pushBack(const T& obj);
    void pushBack(T&& obj);

    class Iterator {
    public:
        explicit Iterator(T* ptr) : ptr(ptr) {}

        T& operator*() const {
            return *ptr;
        }

        T* operator->() const {
            return ptr;
        }

        Iterator& operator++() {
            ++ptr;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp(*this);
            ++(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const Iterator& other) const {
            return ptr != other.ptr;
        }

    private:
        T* ptr;
    };

    Iterator begin();
    Iterator end();

private:
    T* data = nullptr;
    size_t currentSize = 0;
    size_t currentCapacity = 0;

    static constexpr size_t DEFAULT_CAPACITY = 16;

    void resize(size_t newCapacity);
    void free();
    void copyFrom(const Vector& other);
    void moveFrom(Vector&& other) noexcept;
};

template <typename T>
void Vector<T>::free() {
    delete[] data;
    data = nullptr;
    currentSize = currentCapacity = 0;
}

template <typename T>
void Vector<T>::copyFrom(const Vector& other) {
    data = new T[other.currentCapacity];
    for (size_t i = 0; i < other.currentSize; i++) {
        this->data[i] = other.data[i];
    }
    currentCapacity = other.currentCapacity;
    currentSize = other.currentSize;
}

template <typename T>
void Vector<T>::moveFrom(Vector&& other) noexcept {
    data = other.data;
    other.data = nullptr;
    currentCapacity = other.currentCapacity;
    currentSize = other.currentSize;
    other.currentSize = other.currentCapacity = 0;
}

template <typename T>
Vector<T>::Vector(const Vector& other) {
    copyFrom(other);
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept {
    moveFrom(std::move(other));
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template <typename T>
Vector<T>::~Vector() {
    free();
}

template <typename T>
Vector<T>::Vector(size_t capacity) : currentCapacity(capacity) {
    data = new T[capacity];
}

template <typename T>
Vector<T>::Vector() : Vector(DEFAULT_CAPACITY) {}

template <typename T>
size_t Vector<T>::size() const {
    return currentSize;
}

template <typename T>
size_t Vector<T>::capacity() const {
    return currentCapacity;
}

template <typename T>
bool Vector<T>::empty() const {
    return currentSize == 0;
}

template <typename T>
void Vector<T>::clear() {
    currentSize = 0;
}

template <typename T>
T& Vector<T>::operator[](size_t index) {
    // if (index >= currentSize) {
    //     throw std::out_of_range("Index is out of range");
    // }

    // alternatively you can return Optional<T>
    return data[index];
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const {
    // if (index >= currentSize) {
    //     throw std::out_of_range("Index is out of range");
    // }
    // alternatively you can return Optional<T>
    return data[index];
}

template <typename T>
void Vector<T>::resize(size_t newCapacity) {
    T* resizedData = new T[newCapacity];
    size_t elementsToMove = currentSize < newCapacity ? currentSize : newCapacity;
    for (size_t i = 0; i < elementsToMove; i++) {
        resizedData[i] = std::move(data[i]);
    }
    delete[] data;
    data = resizedData;
    currentSize = elementsToMove;
    currentCapacity = newCapacity;
}

template <typename T>
void Vector<T>::pushBack(const T& obj) {
    if (currentSize >= currentCapacity) {
        resize(currentCapacity == 0 ? 1 : currentCapacity * 2);
    }
    data[currentSize++] = obj;
}

template <typename T>
void Vector<T>::pushBack(T&& obj) {
    if (currentSize >= currentCapacity) {
        resize(currentCapacity == 0 ? 1 : currentCapacity * 2);
    }
    data[currentSize++] = std::move(obj);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::begin() {
    return Iterator(data);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::end() {
    return Iterator(data + currentSize);
}
