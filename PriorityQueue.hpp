#pragma once
#include<iostream>
#include<print>
#include"MyVector.hpp"

template <typename T, typename Comparator>
class PriorityQueue
{
private:
	MyVector<T> data;
	Comparator cmp;

public:
	void heapUp(size_t index);
	void heapDown(size_t i);

	void push(const T& x);
	void push(T&& x);
	void pop();

	const T& peek()const;
	bool empty()const;
	size_t size()const;
};

template <typename T, typename Comparator>
void PriorityQueue<T,Comparator>::heapUp(size_t index)
{
	while (index > 0)
	{
		size_t parent = (index - 1) / 2;

		if(cmp(data[index],data[parent]))
		{ 
			std::swap(data[index], data[parent]);
			index = parent;
		}
		else
		{
			break;
		}
	}
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::heapDown(size_t i)
{
	size_t n = data.getSize();

	while (true)
	{
		size_t left = 2 * i + 1;
		size_t right = 2 * i + 2;
		size_t best = i;

		if (left < n && cmp(data[left], data[i]))
		{
			best = left;
		}

		if (right < n && cmp(data[right], data[i]))
		{
			best = right;
		}

		if (best != i)
		{
			std::swap(data[i], data[best]);
			i = best;
		} 
		else
		{
			break;
		}
	}
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::push(const T& x)
{
	data.push_back(x);
	heapUp(data.getSize() - 1);
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::push(T&& x)
{
	data.push_back(std::move(x));
	heapUp(data.getSize() - 1);
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::pop()
{
	if (empty())
	{
		std::println("The priority queue is empty!");
		return;
	}

	std::swap(data[0], data[data.getSize() - 1]);
	data.pop_back();

	if (!empty())
	{
		heapDown(0);
	}
}

template <typename T, typename Comparator>
const T& PriorityQueue<T, Comparator>::peek()const
{
	return data[0];
}

template <typename T, typename Comparator>
bool PriorityQueue<T, Comparator>::empty()const
{
	return data.getSize() == 0;
}

template <typename T, typename Comparator>
size_t PriorityQueue<T, Comparator>::size()const
{
	return data.getSize();
}