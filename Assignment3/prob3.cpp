#include <iostream>

using namespace std;

void swap(int& a, int& b)
{
	a = a + b;
	b = a - b;
	a = a - b;
}

int main() {

	int a, b;
	cout << "Enter 2 numbers: \n";
	cin >> a >> b;
	cout << "Before Swapping - a = " << a << " b = " << b << "\n";
	swap(a, b);
	cout << "After Swapping - a = " << a << " b = " << b << "\n";

	return 0;
}