#include <iostream>
using namespace std;

class Complex {
	int real;
	int imag;
public:
	Complex(int r = 0, int im = 0)
	{
		real = r;
		imag = im;
	}
	operator int ()
	{
		return (real * real + imag * imag);
	}
	operator float ()
	{
		return (1.0 * real * real + imag * imag * 1.0);
	}
};

class A {
protected:
	int x;
public:
	A(int el = 0)
	{
		x = el;
	}
	virtual void f1()
	{
		cout << "In f1 of A\n";
	}
	virtual void f2()
	{
		cout << "In f2 of A\n";
	}
};

class B : public A {
protected:
	int y;
public:
	B(int el = 0)
	{
		y = el;
	}
	void f1(int a)
	{
		cout << "In f1 of B\n";
	}
	void f2()
	{
		cout << "In f2 of B\n";
	}
};

class C: public B {
	int z;
public:
	C(int el = 0 , int el2 = 0, int el3 = 0)
	{
		z = el;
	}
	void f()
	{
		cout << "In C\n";
	}
};

signed main() {

	Complex c(3, 4);
	char mag = float(c);
	cout << mag << "\n";

	A *p;
	B b;
	p = &b;
	p->f1();
	p->f2();
	// p->f1(10);
	// b.f1();

	return 0;
}