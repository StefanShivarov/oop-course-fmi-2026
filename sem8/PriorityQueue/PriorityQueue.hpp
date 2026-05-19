#pragma once
#include <iostream>
#include <utility>

template <typename T, typename Comparator>
class PriorityQueue 
{
	size_t current_size = 0;
	size_t capacity = 0;
	T* data = nullptr;
	Comparator cmp;

	void resize(size_t newCapacity);
	void free();
	void copyFrom(const PriorityQueue& other);
	void moveFrom(PriorityQueue&& other);

public:
	PriorityQueue();
	PriorityQueue(const PriorityQueue& other);
	PriorityQueue& operator=(const PriorityQueue& other);
	PriorityQueue(PriorityQueue&& other) noexcept;
	PriorityQueue& operator=( PriorityQueue&& other)noexcept;
	~PriorityQueue();

	const T& operator[](size_t index) const;

	void push(const T& element);
	void push(T&& element);
	T& pop();
	const T& peek() const;

	bool empty() const;
	size_t size() const;
};

template<typename T, typename Comparator>
inline void PriorityQueue<T, Comparator>::resize(size_t newCapacity)
{
	capacity = newCapacity;
	T* temp = new T[newCapacity];
	for (size_t i = 0; i < current_size; i++)
	{
		temp[i] = data[i];
	}
	delete[] data;
	data = temp;
}

template<typename T, typename Comparator>
inline void PriorityQueue<T, Comparator>::free()
{
	delete[]data;
	data = nullptr;
}

template<typename T, typename Comparator>
inline void PriorityQueue<T, Comparator>::copyFrom(const PriorityQueue& other)
{
	current_size = other.current_size;
	capacity = other.capacity;

	data = new T[capacity];
	for (size_t i = 0; i < current_size; i++)
	{
		data[i] = other.data[i];
	}
}

template<typename T, typename Comparator>
inline void PriorityQueue<T, Comparator>::moveFrom(PriorityQueue&& other)
{
	current_size = other.current_size;
	capacity = other.capacity;
	data = other.data;

	other.current_size = 0;
	other.capacity = 0;
	other.data = nullptr;
}

template<typename T, typename Comparator>
inline PriorityQueue<T, Comparator>::PriorityQueue() : current_size(0), capacity(8), data(new T[capacity]{}) {}

template<typename T, typename Comparator>
inline PriorityQueue<T, Comparator>::PriorityQueue(const PriorityQueue& other)
{
	copyFrom(other);
}

template<typename T, typename Comparator>
inline PriorityQueue<T, Comparator>& PriorityQueue<T, Comparator>::operator=(const PriorityQueue& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T, typename Comparator>
inline PriorityQueue<T, Comparator>::PriorityQueue(PriorityQueue&& other) noexcept
{
	moveFrom(std::move(other));
}

template<typename T, typename Comparator>
inline PriorityQueue<T, Comparator>& PriorityQueue<T, Comparator>::operator=(PriorityQueue&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<typename T, typename Comparator>
inline PriorityQueue<T, Comparator>::~PriorityQueue()
{
	free();
}

template<typename T, typename Comparator>
inline void PriorityQueue<T, Comparator>::push(const T& element)
{
	size_t newCap = (capacity == 0) ? 8 : capacity * 2;
	if (current_size == capacity) {
		resize(newCap);
	}

	data[current_size] = element;
	current_size++;
}

template<typename T, typename Comparator>
inline void PriorityQueue<T, Comparator>::push(T&& element)
{
	size_t newCap = (capacity == 0) ? 8 : capacity * 2;
	if (current_size == capacity) {
		resize(newCap);
	}

	data[current_size] = std::move(element);
	current_size++;
}

template<typename T, typename Comparator>
inline T& PriorityQueue<T, Comparator>::pop() 
{
	//if(empty())

	size_t highestIndex = 0;
	for (size_t i = 0; i < current_size; i++)
	{
		if (cmp(data[i], data[highestIndex])) {
			highestIndex = i;
		}
	}
	
	std::swap(data[highestIndex], data[current_size - 1]);
	current_size--;

	return data[current_size];
}

template<typename T, typename Comparator>
inline const T& PriorityQueue<T, Comparator>::peek() const
{
	//if(empty())

	size_t highestIndex = 0;
	for (size_t i = 0; i < current_size; i++)
	{
		if (cmp(data[i], data[highestIndex])) {
			highestIndex = i;
		}
	}
	return data[highestIndex];
}

template<typename T, typename Comparator>
bool PriorityQueue<T, Comparator>::empty() const {
	return current_size == 0;
}

template<typename T, typename Comparator>
size_t PriorityQueue<T, Comparator>::size() const {
	return current_size;
}

template<typename T, typename Comparator>
inline const T& PriorityQueue<T, Comparator>::operator[](size_t index) const
{
	return data[index];
}
