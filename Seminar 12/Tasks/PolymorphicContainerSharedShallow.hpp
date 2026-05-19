#pragma once
#include <iostream>
#include <memory>
#include <vector>
template <typename T>
class PolymoprhicContainerSharedShallow {
private:
	std::vector<std::shared_ptr<T>> collection;

	void copyFrom(const PolymoprhicContainerSharedShallow& other) {
		for (const auto& ptr : other.collection) {
			if (ptr) {
				collection.push_back(ptr);					
			}
		}
	}

public:
	PolymoprhicContainerSharedShallow() = default;

	PolymoprhicContainerSharedShallow(const PolymoprhicContainerSharedShallow& other) {
		copyFrom(other);
	}

	PolymoprhicContainerSharedShallow& operator=(const PolymoprhicContainerSharedShallow& other) {
		if (this != &other)
		{
			collection.clear();
			copyFrom(other);
		}
		return *this;
	}

	void add(const std::shared_ptr<T>& obj) {
		collection.push_back(obj);
	}

	void removeObjAt(int index) {
		if (index >= collection.size())
		{
			throw std::out_of_range("index out of bounds");
		}
		collection.erase(collection.begin() + index);
	}

	const T& operator[](int index) const {
		if (index >= collection.size())
		{
			throw std::out_of_range("index out of bounds");
		}
		return *collection[index];
	}

	T& operator[](int index) {
		if (index >= collection.size())
		{
			throw std::out_of_range("index out of bounds");
		}
		return *collection[index];
	}

	void print() const {
		for (auto& ptr : collection) {
			ptr->printInfo();
		}
	}

	auto begin() { return collection.begin(); }
	auto begin() const { return collection.begin(); }
	auto end() { return collection.end(); }
	auto end() const { return collection.end(); }
};