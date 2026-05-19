
#include <iostream>
using std::cout;
using std::cin;

namespace RationalN
{
	struct Rational
	{
		int numerator;
		int denominator;
	};

		bool isInteger(Rational r)
		{
			if (r.denominator == 0)
				return false;

			return r.numerator % r.denominator == 0;
		}
		bool isValid(Rational r)
		{
			return r.denominator != 0;
		}
		int gcd(int a, int b) {
			a = (a < 0) ? -a : a;
			b = (b < 0) ? -b : b;
			while (b) 
			{ 
				int t = b; 
				b = a % b;
				a = t; 
			}
			return a;
		}

		Rational simplify(Rational r) {
			int g = gcd(r.numerator, r.denominator);
			r.numerator /= g;
			r.denominator /= g;
			if (r.denominator < 0) {
				r.numerator = -r.numerator;
				r.denominator = -r.denominator;
			}
			return r;
		}
	Rational sum (Rational r1, Rational r2)
	{
		if (!isValid(r1) || !isValid(r2)) return { 0, 0 };

		Rational result;
		result.numerator = r1.numerator * r2.denominator + r2.numerator * r1.denominator;
		result.denominator = r1.denominator * r2.denominator;
		return simplify(result);
	}
	Rational sub (Rational r1, Rational r2)
	{
		if (!isValid(r1) || !isValid(r2)) return { 0, 0 };

		Rational result;
		result.numerator = r1.numerator * r2.denominator - r2.numerator * r1.denominator;
		result.denominator = r1.denominator * r2.denominator;
		return simplify(result);
	}
	Rational mul (Rational r1, Rational r2)
	{
		if (!isValid(r1) || !isValid(r2)) return { 0, 0 };

		Rational result;
		result.numerator = r1.numerator * r2.numerator;
		result.denominator = r1.denominator * r2.denominator;
		return simplify(result);
	}
	
	Rational div (Rational r1, Rational r2)
	{
		if (!isValid(r1) || !isValid(r2)) return { 0, 0 };
		if (r2.numerator == 0) return { 0, 0 }; 
		Rational result;
		result.numerator = r1.numerator * r2.denominator;
		result.denominator = r1.denominator * r2.numerator;
		return simplify(result);
	}
	void print(Rational r) {
		if (!isValid(r)) { cout << "undefined"; return; }
		if (isInteger(r)) cout << r.numerator / r.denominator;
		else cout << r.numerator << "/" << r.denominator;
	}
}

int main()
{
	using namespace RationalN;
	Rational r1, r2;
	cout << "Enter the numerator and denominator of the first rational number: ";
	cin >> r1.numerator >> r1.denominator;
	cout << "Enter the numerator and denominator of the second rational number: ";
	cin >> r2.numerator >> r2.denominator;
	print(sum(r1, r2)); cout << "\n";
	print(sub(r1, r2)); cout << "\n";
	print(mul(r1, r2)); cout << "\n";
	print(div(r1, r2)); cout << "\n";

	

		
}
