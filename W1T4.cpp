#include <iostream>

struct Rational
{
	int upperpart = 0;
	int lowerpart = 1;
	bool valid() {
		if (lowerpart == 0) {
			return false;
		}
		return true;
	}
	bool isinteger() {
		if (upperpart % lowerpart == 0) {
			return true;
		}
		else
		{
			return false;
		}
	}
	void print() {
		if (isinteger()) {
			std::cout << upperpart / lowerpart << std::endl;
		}
		else {
			std::cout << upperpart << "/" << lowerpart << std::endl;
		}	
	}
	int nod(int a, int b) {
		int r = a % b;
		while (r != 0)
		{
			a = b;
			b = r;
			r = a % b;
		}
		return b;
	}

	void simplify(int& a, int& b) {
		int del = nod(a, b);
		a /= del;
		b /= del;
	}
	Rational add(Rational number) {
		Rational result;
		result.upperpart = upperpart * number.lowerpart + number.upperpart * lowerpart;
		result.lowerpart = lowerpart * number.lowerpart;
		simplify(result.upperpart, result.lowerpart);
		return result;
	}
	Rational subtract(Rational number) {
		Rational result;
		result.upperpart = upperpart * number.lowerpart - number.upperpart * lowerpart;
		result.lowerpart = lowerpart * number.lowerpart;
		simplify(result.upperpart, result.lowerpart);
		return result;
	}
	Rational multiplication(Rational number) {
		Rational result;
		result.upperpart = upperpart * number.upperpart;
		result.lowerpart = lowerpart * number.lowerpart;
		simplify(result.upperpart, result.lowerpart);
		return result;
	}
	Rational devision(Rational number) {
		Rational result;
		result.upperpart = upperpart * number.lowerpart;
		result.lowerpart = lowerpart * number.upperpart;
		simplify(result.upperpart, result.lowerpart);
		return result;
	}
};
int main()
{
	Rational r;
	r.upperpart = 1;
	r.lowerpart = 2;
	Rational r2;
	r2.upperpart = 1;
	r2.lowerpart = -2;
	Rational re = r.add(r2);
	re.print();
}