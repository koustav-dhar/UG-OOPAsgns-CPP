#include <iostream>
#include <assert.h>

using namespace std;

class Array {
	int size;
	int* arr;
public:
	int& operator[](int i)
	{
		if (i < 0 || i >= size) {
			cout << "Index out of bounds.\n";
			return arr[0];
		}
		return arr[i];
	}
	Array(int sz = 0, int val = 0)
	{
		size = max(0, sz);
		if (size == 0) {
			arr = NULL;
		} else {
			arr = new int[size];
			for (int i = 0; i < size; ++i) {
				arr[i] = val;
			}
		}
	}
	Array(Array& temp)
	{
		size = temp.size;
		if (size == 0) {
			arr = NULL;
		} else {
			arr = new int[size];
			for (int i = 0; i < size; ++i) {
				arr[i] = temp[i];
			}
		}
	}
	void operator=(const Array& a)
	{
		delete[] arr;
		size = a.size;
		arr = new int[size];
		for (int i = 0; i < size; ++i) {
			arr[i] = a.arr[i];
		}
	}
	Array(int *temp, int sz)
	{
		size = sz;
		if (size == 0) {
			arr = NULL;
		} else {
			arr = new int[size];
			for (int i = 0; i < size; ++i) {
				arr[i] = temp[i];
			}
		}
	}
	friend Array operator+(Array a, Array b)
	{
		assert(a.size == b.size);
		Array c(a.size);
		for (int i = 0; i < c.size; ++i) {
			c[i] = a[i] + b[i];
		}
		return c;
	}
	friend Array operator*(Array a, int n)
	{
		Array b(a);
		for (int i = 0; i < a.size; ++i) {
			b[i] = a[i] * n;
		}
		return b;
	}
	friend Array operator*(int n, Array a)
	{
		Array b(a);
		for (int i = 0; i < a.size; ++i) {
			b[i] = a[i] * n;
		}
		return b;
	}
	friend ostream& operator<<(ostream& out, Array a)
	{
		for (int i = 0; i < a.size; ++i) {
			out << a[i] << " ";
		}
		out << "\n";
		return out;
	}
	~Array()
	{
		delete[] arr;
	}
};

signed main() {

	Array a(5, 5);
	Array b = *(new Array(5, 7));
	int c[] = {1, 2, 3, 4, 5};
	Array d(c, (sizeof(c) / sizeof(int)));
	Array e;
	e = b + d;
	Array f, g;
	f = a * 3;
	g = 7 * a;
	cout << a << b << d << e << f << g;

	return 0;
}