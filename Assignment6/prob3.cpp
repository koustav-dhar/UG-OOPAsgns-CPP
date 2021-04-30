#include <iostream>

using namespace std;

// class template for Array class
template<class X>
class Array {
	X *arr;
	int size;
public:
	Array(int s = 0)
	{
		if (s == 0)
			arr = NULL;
		else
			arr = new X[s];
		size = s;
	}
	void getinput();
	X getMax();
	X getSum();
};

// function template to get input
template<class T>
void Array<T>::getinput()
{
	cout << "Enter " << size << " values: \n";
	for (int i = 0; i < size; ++i) {
		cin >> arr[i];
	}
}

// function template to find maximum value
template<class T>
T Array<T>::getMax()
{
	T mx = arr[0];
	for (int i = 0; i < size; ++i) {
		mx = max(mx, arr[i]);
	}
	return mx;
}

// function template to find sum
template<class T>
T Array<T>::getSum()
{
	T sum = arr[0];
	for (int i = 1; i < size; ++i) {
		sum += arr[i];
	}
	return sum;
}

signed main() {

	while (1) {
		cout << "\nSelect what to do.";
		cout << "\nPress 1 to create an array of integers.";
		cout << "\nPress 2 to create an array of floats.";
		cout << "\nPress 3 to create an array of doubles.";
		cout << "\nPress 4 to exit.\n";
		int choice;
		cin >> choice;
		if (choice == 1) {
			cout << "Enter number of elements: \n";
			int n;
			cin >> n;
			Array<int> a(n);
			a.getinput();
			cout << "Max: " << a.getMax() << "\n";
			cout << "Sum: " << a.getSum() << "\n";
		} else if (choice == 2) {
			cout << "Enter number of elements: \n";
			int n;
			cin >> n;
			Array<float> a(n);
			a.getinput();
			cout << "Max: " << a.getMax() << "\n";
			cout << "Sum: " << a.getSum() << "\n";
		} else if (choice == 3) {
			cout << "Enter number of elements: \n";
			int n;
			cin >> n;
			Array<double> a(n);
			a.getinput();
			cout << "Max: " << a.getMax() << "\n";
			cout << "Sum: " << a.getSum() << "\n";
		} else if (choice == 4) {
			exit(0);
		} else {
			cout << "Invalid Choice.\n";
		}
	}

	return 0;
}