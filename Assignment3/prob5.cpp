#include <iostream>

using namespace std;

int getIncomeTaxReturn(int income, int 	taxRate = 10)
{
	int amt = income * taxRate;
	amt /= 100;
	return amt;
}

int main() {

	int income;
	cout << "Enter your income: \n";
	cin >> income;
	char choice = 'n';
	cout << "Do you want to enter a custom income tax rate? (y/n): \n";
	cin >> choice;
	if (choice == 'y') {
		int taxRate;
		cout << "Enter tax rate: \n";
		cin >> taxRate;
		cout << "Your income tax payable is: " << getIncomeTaxReturn(income, taxRate) << "\n";
	} else {
		cout << "Your income tax payable is: " << getIncomeTaxReturn(income) << "\n";
	}

	return 0;
}