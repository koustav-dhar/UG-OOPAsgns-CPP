#include <iostream>

using namespace std;

#define MAXN 50
#define getMax(a, b) (((a) > (b)) ? (a) : (b))

int main() {

	int a, b;
	cout << "Enter 2 numbers: \n";
	cin >> a >> b;
	cout << "The max of them is: " << getMax(a, b) << "\n";

	char *s = new char[MAXN];
	char *t = new char[MAXN];
	cout << "Enter 2 strings: \n";
	cin >> s >> t;
	cout << "The greater of the strings lexicographically is: " << getMax(s, t) << "\n";

	return 0;
}