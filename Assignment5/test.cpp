#include <iostream>

using namespace std;

////////////////////////////////////////
class A {
public:
	void f(void)
	{
		cout << "WORLD\n";
	}
};

class B: public A {
protected:
	int x;
};

class C: public B {
public:
	void f(void)
	{
		cout << "HELLO ";
	}
};
////////////////////////////////////////
class Base {
	int x;
public:

	virtual void f() = 0;
};
class Derived: public Base {
	int y;
public:
	void f()
	{
		cout << "DERIVED\n";
	}
};
////////////////////////////////////////

int x = 0;
class X {
	int x;
};
class Y : public X {
public:
	void f()
	{
		// cout << x << "\n";
	}
};
///////////////////////////////////////
signed main() {

	int x = 2;
	printf("%d %d %d\n", ++x, x, x++);
	x = 2;
	printf("%d %d %d\n", x++, x, ++x);


	return 0;
}