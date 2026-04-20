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

// template specialization for bool
// we can implement it as bitset, so that we store the same information
// but instead of 1 byte per element, we use 1 bit
template <>
class Vector<bool> {
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

    bool get(size_t index) const;
    void set(size_t index, bool value);

    void pushBack(bool value);

private:
    uint8_t* bytes = nullptr;
    size_t currentSize = 0;      // number of bool elements
    size_t currentCapacity = 0;  // capacity in bool elements

    static constexpr size_t BITS_IN_BYTE = 8;

    static size_t getBytesCount(size_t elementsCount);
    static size_t getByteIndex(size_t index);
    static uint8_t getMask(size_t index);

    void resize(size_t newCapacity);
    void free();
    void copyFrom(const Vector& other);
    void moveFrom(Vector&& other) noexcept;
};

inline size_t Vector<bool>::getBytesCount(size_t elementsCount) {
    return elementsCount / BITS_IN_BYTE + (elementsCount % BITS_IN_BYTE != 0);
}

inline size_t Vector<bool>::getByteIndex(size_t index) {
    return index / BITS_IN_BYTE;
}

inline uint8_t Vector<bool>::getMask(size_t index) {
    size_t shift = index % BITS_IN_BYTE;
    uint8_t mask = 1;
    mask <<= (BITS_IN_BYTE - 1 - shift);
    return mask;
}

inline void Vector<bool>::free() {
    delete[] bytes;
    bytes = nullptr;
    currentSize = currentCapacity = 0;
}

inline void Vector<bool>::copyFrom(const Vector& other) {
    currentSize = other.currentSize;
    currentCapacity = other.currentCapacity;

    size_t bytesCount = getBytesCount(currentCapacity);
    bytes = new uint8_t[bytesCount]{};

    for (size_t i = 0; i < bytesCount; i++) {
        bytes[i] = other.bytes[i];
    }
}

inline void Vector<bool>::moveFrom(Vector&& other) noexcept {
    bytes = other.bytes;
    currentSize = other.currentSize;
    currentCapacity = other.currentCapacity;

    other.bytes = nullptr;
    other.currentSize = 0;
    other.currentCapacity = 0;
}

inline void Vector<bool>::resize(size_t newCapacity) {
    size_t newBytesCount = getBytesCount(newCapacity);
    uint8_t* newBytes = new uint8_t[newBytesCount]{};

    size_t oldBytesCount = getBytesCount(currentCapacity);
    size_t bytesToCopy = oldBytesCount < newBytesCount ? oldBytesCount : newBytesCount;

    for (size_t i = 0; i < bytesToCopy; i++) {
        newBytes[i] = bytes[i];
    }

    delete[] bytes;
    bytes = newBytes;
    currentCapacity = newCapacity;

    if (currentSize > currentCapacity) {
        currentSize = currentCapacity;
    }
}

inline Vector<bool>::Vector() : Vector(BITS_IN_BYTE) {}

inline Vector<bool>::Vector(size_t capacity) : currentCapacity(capacity) {
    size_t bytesCount = getBytesCount(currentCapacity);
    bytes = new uint8_t[bytesCount]{0};
}

inline Vector<bool>::Vector(const Vector& other) {
    copyFrom(other);
}

inline Vector<bool>::Vector(Vector&& other) noexcept {
    moveFrom(std::move(other));
}

inline Vector<bool>& Vector<bool>::operator=(const Vector& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

inline Vector<bool>& Vector<bool>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

inline Vector<bool>::~Vector() {
    free();
}

inline size_t Vector<bool>::size() const {
    return currentSize;
}

inline size_t Vector<bool>::capacity() const {
    return currentCapacity;
}

inline bool Vector<bool>::empty() const {
    return currentSize == 0;
}

inline void Vector<bool>::clear() {
    currentSize = 0;
}

inline bool Vector<bool>::get(size_t index) const {
    if (index >= currentSize) {
        return false;
    }
    size_t byteIndex = getByteIndex(index);
    uint8_t mask = getMask(index);
    return (bytes[byteIndex] & mask) != 0;
}

inline void Vector<bool>::set(size_t index, bool value) {
    if (index >= currentCapacity) {
        return;
    }
    size_t byteIndex = getByteIndex(index);
    uint8_t mask = getMask(index);

    if (value) {
        bytes[byteIndex] |= mask;
    } else {
        bytes[byteIndex] &= (~mask);
    }
}

inline void Vector<bool>::pushBack(bool value) {
    if (currentSize >= currentCapacity) {
        resize(currentCapacity == 0 ? 1 : currentCapacity * 2);
    }

    set(currentSize, value);
    currentSize++;
}
