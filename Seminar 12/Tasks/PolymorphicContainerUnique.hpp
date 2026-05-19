#pragma once
#include <iostream>
#include <memory>
#include <vector>
template <typename T>
class PolymoprhicContainerUnique {
private:
	std::vector<std::unique_ptr<T>> collection;

	void cloneAll(const PolymoprhicContainerUnique& other) {
		for (auto& ptr : other.collection) {
			if (ptr) {
				collection.push_back(ptr->clone());					// std::unique_ptr<T> clone() const;
			}
		}
	}

public:
	PolymoprhicContainerUnique() = default;

	PolymoprhicContainerUnique(const PolymoprhicContainerUnique& other) {
		cloneAll(other);
	}

	PolymoprhicContainerUnique& operator=(const PolymoprhicContainerUnique& other) {
		if (this != &other)
		{
			collection.clear();
			cloneAll(other);
		}
		return *this;
	}

	void add(const T& obj) {
		collection.push_back(obj.clone());
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