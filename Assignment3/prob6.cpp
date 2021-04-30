#include <iostream>

using namespace std;

void f(int num)
{
	cout << "inside f(int)\n";
}

void f(float num)
{
	cout << "inside f(float)\n";
}

signed main() {

	int a = 1;
	char b = 'a';
	float c = 3.0;
	double d = 31.05;
	cout << "Passing int -> "; f(a); cout << "\n";
	cout << "Passing char -> "; f(b); cout << "\n";
	cout << "Passing float -> "; f(c); cout << "\n";
	// cout << "Passing double -> "; f(d); cout << "\n";

	return 0;
}