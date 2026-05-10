#include <iostream>
#include "ComplexNumber.h"

int main() {
	ComplexNumber num1, num2;

	std::cin >> num1 >> num2;

	ComplexNumber sum = num1 + num2;

	std::cout << (num1 - 3) << std::endl;
	std::cout << num2 << std::endl;
	std::cout << sum << std::endl;
	std::cout << (num1 == num2) << std::endl;
	std::cout << (num1 != num2) << std::endl;
}