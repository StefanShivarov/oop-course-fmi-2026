#include <iostream>
#include"PriorityQueue.hpp"
#include"Comparator.h"

int main()
{
    PriorityQueue<int, GreaterFirst<int>> pq;

    pq.push(5);
    pq.push(1);
    pq.push(8);
    pq.push(3);

    std::println("Size: {}",pq.size());
    std::println("Peek: {}", pq.peek());

    while (!pq.empty()) 
    {
        std::print("{} ", pq.peek());
        pq.pop();
    }
    return 0;
}
