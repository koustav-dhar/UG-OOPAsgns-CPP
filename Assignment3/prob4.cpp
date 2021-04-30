#include <iostream>

using namespace std;

int& getMaxRef(int& a, int& b)
{
	if (a > b)
		return a;
	else
		return b;
}

int main() {

	int a, b;
	cout << "Enter 2 numbers: \n";
	cin >> a >> b;
	int x = getMaxRef(a, b);
	cout << "Using a max function returning variable: \n";
	cout << "Max element = " << x << "\n";
	++x;
	cout << "Incrementing the max element, we get: \n";
	cout << "a = " << a << " b = " << b << " Max = " << x << "\n";

	int& y = getMaxRef(a, b);
	cout << "Using a max function returning reference: \n";
	cout << "Max element = " << y << "\n";
	++y;
	cout << "Incrementing the max element, we get: \n";
	cout << "a = " << a << " b = " << b << " Max = " << y << "\n";
	return 0;
}