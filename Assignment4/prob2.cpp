#include <iostream>

using namespace std;

class Complex {
	int r;
	int im;
public:
	Complex(int real = 0, int imag = 0)
	{
		r = real;
		im = imag;
	}
	Complex(Complex& C)
	{
		r = C.r;
		im = C.im;
	}
	friend Complex operator+(Complex a, Complex b)
	{
		Complex c;
		c.r = a.r + b.r;
		c.im = a.im + b.im;
		return c;
	}
	friend Complex operator-(Complex a, Complex b)
	{
		Complex c;
		c.r = a.r - b.r;
		c.im = a.im - b.im;
		return c;
	}
	friend istream& operator>>(istream& in, Complex& c)
	{
		cout << "Enter real part: ";
		in >> c.r;
		cout << "Enter imaginary part: ";
		in >> c.im;
		return in;
	}
	friend ostream& operator<<(ostream& out, Complex& c)
	{
		out << c.r;
		if (c.im >= 0) {
			out << "+";
		}
		out << c.im << "i\n";
		return out;
	}
};

signed main() {

	Complex c1, c2;
	cin >> c1 >> c2;
	Complex c3, c4;
	c3 = c1 + c2;
	c4 = c1 - c2;
	cout << "Sum: \n" << c3;
	cout << "Difference: \n" << c4;

	return 0;
}