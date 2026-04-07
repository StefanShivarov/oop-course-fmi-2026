#include <iostream>

// Important! : infinite nesting -> compiler error (size of Node is impossible to compute)
struct BadNode {
    int value;
    BadNode next; // ERROR: a BadNode would contain a BadNode, which contains a BadNode,
                  //so it can't estimate its struct size
};

// Correct way to do it: use a pointer (fixed size) to refer to another node
struct Node {
    int value;
    Node* next; // pointer has fixed size (usually 4 or 8 bytes)

    void print() const {
        std::cout << value;
        if (next != nullptr) {
            std::cout << " -> ";
            next->print();
        }
    }
};

// Self-nested structs/classes are common in data structures such as linked lists and trees,
// but you will learn about those in the Data Structures and Algorithms course next year

int main() {
    Node first{10, nullptr};
    Node second{20, nullptr};
    Node third{30, nullptr};

    first.next = &second;
    second.next = &third;

    first.print(); // 10 -> 20 -> 30
    std::cout << "\n";
}
