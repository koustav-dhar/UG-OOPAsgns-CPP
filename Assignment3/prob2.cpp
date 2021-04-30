#include <iostream>
#include <iomanip>
#include <time.h>
#include <ctime>

using namespace std;

int func(int a, int b)
{
	int res;
	res = a * b;
	return res;
}

inline int ifunc(int a, int b)
{
	int res;
	res = a * b;
	return res;
}

int main() {

	int a, b;
	cout << "Enter 2 numbers: \n";
	cin >> a >> b;
	int n;
	cout << "How many times you'd like to see the product : \n";
	cin >> n;

	clock_t start, end;

	start = clock();

	for (int i = 0; i < n; ++i) {
		cout << func(a, b) << "\n";
	}

	end = clock();

	cout << "\nTime Elapsed using function: " << fixed << setprecision(10) << 1.0 * (end - start) / (1.0 * CLOCKS_PER_SEC) << " sec\n";

	start = clock();

	for (int i = 0; i < n; ++i) {
		cout << ifunc(a, b) << "\n";
	}

	end = clock();

	cout << "\nTime Elapsed using inline function: " << fixed << setprecision(10) << 1.0 * (end - start) / (1.0 * CLOCKS_PER_SEC) << " sec\n";

	return 0;
}