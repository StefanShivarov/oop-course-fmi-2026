#include "PriorityQueue.hpp"
#include <iostream>
#include <cstring>

using std::cout;

struct GreaterFirst {
	bool operator()(int a, int b) const {
		return a > b;
	}
};

struct LongerStringFirst {
	bool operator()(const std::string& str1, const std::string& str2) const {
		return str1.length() > str2.length();
	}
};

int main()
{
	
	PriorityQueue<int, GreaterFirst> pq;
	pq.push(5);
	pq.push(1);
	pq.push(8);
	pq.push(3);

	for (size_t i = 0; i < pq.size(); i++)
	{
		cout << pq[i] << " ";
	}
	cout << '\n';
	cout << "Highest priority element: " << pq.peek() << '\n';
	cout << "Highest priority element: " << pq.pop() << '\n';
	cout << "Highest priority element after pop(): " << pq.peek() << '\n';

	cout << '\n';

	PriorityQueue<std::string, LongerStringFirst> p2;
	p2.push("OOP");
	p2.push("Geometry");
	p2.push("DIS");
	p2.push("DSTR");

	for (size_t i = 0; i < p2.size(); i++)
	{
		cout << p2[i] << " ";
	}
	cout << '\n';
	cout << "Highest priority element: " << p2.peek() << '\n';
	cout << "Highest priority element: " << p2.pop() << '\n';
	cout << "Highest priority element after pop(): " << p2.peek() << '\n';

}

