# include "Complex.h"

Complex::Complex(double real, double im) : real(real), im(im) {}
double Complex::getReal()const
{
	return real;
}
double Complex::getIm () const
{
	return im;
}
Complex& Complex:: operator +=(const Complex& other) {
	real += other.real;
	im += other.im;
	return *this;

}
Complex& Complex:: operator -=(const Complex& other)
{
	real -= other.real;
	im -= other.im;
	return *this;
}

Complex& Complex:: operator /=(const Complex& other)
{
	double denominator = other.real * other.real + other.im * other.im;
	double newReal = (real * other.real + im * other.im) / denominator;  
	double newIm = (im * other.real - real * other.im) / denominator;
	real = newReal;
	im = newIm;
	return *this;
}
Complex& Complex:: operator*= (const Complex& other)
{
	double newReal = real * other.real - im * other.im;  
	double newIm = real * other.im + im * other.real;    
	real = newReal;
	im = newIm;
	return *this;
}


Complex Complex:: operator +() const {
	return *this;
}

Complex Complex:: operator -() const {

	return Complex(-real, -im);
}

Complex operator + (const Complex& lhs, const Complex& rhs)
{
	Complex res = lhs;
	res += rhs;
	return res;
}
Complex operator - (const Complex& lhs, const Complex& rhs)
{
	Complex res = lhs;
	res -= rhs;
	return res;
}
Complex operator /(const Complex& lhs, const Complex& rhs) {
	Complex res = lhs;
	res /= rhs;
	return res;
}

Complex operator *(const Complex& lhs, const Complex& rhs)
{
	Complex res = lhs;
	res *= rhs;
	return res;
}

bool operator ==(const Complex& lhs, const Complex& rhs)
{
	if (lhs.getReal() == rhs.getReal() && lhs.getIm() == rhs.getIm()) return true;
	return false;
}

bool operator !=(const Complex& lhs, const Complex& rhs)
{
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Complex& c) {
	os << c.real << " + (" << c.im << "i )";
	return os;
}

std::istream& operator>>(std::istream& is, Complex& c)
{
	is >> c.real >> c.im;
	return is;
}