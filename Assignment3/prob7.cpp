#include <iostream>

using namespace std;

void f(int a, char b)
{
	cout << "inside (int, char) function. \n";
}

void f(char a, int b)
{
	cout << "inside (char, int) function. \n";
}

int main() {

	int a = 5;
	char x = 'a', y = 'z';
	float b = 31.05, c = 20.02;

	cout << "Passing (int, char) -> ";
	f(a, x);

	cout << "Passing (char, char) -> ambiguity error.\n";
	// f(x, y);

	cout << "Passing (float, float) -> ambiguity error.\n";
	// f(b, c);

	return 0;
}