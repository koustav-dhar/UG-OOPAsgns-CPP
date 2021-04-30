#include <iostream>

using namespace std;

class Employee {
protected:
	int empid;
	char name[31];
	char desgination[31];
	double basicpay;
public:
	virtual void computeSalary() = 0;
	void getinput()
	{
		cout << "Enter Employee ID: \n";
		cin >> empid;
		cout << "Enter Name: \n";
		scanf(" %[^\n]s", name);
		cout << "Enter Designation: \n";
		scanf(" %[^\n]s", desgination);
		cout << "Enter Basic Pay: \n";
		cin >> basicpay;
		computeSalary();
	}
};

class PermanentEmployee: public Employee {
public:
	void computeSalary()
	{
		double salary = basicpay;
		salary += 1.1 * basicpay;
		cout << "Your Salary is: " << salary << "\n";
	}
};

class ContractualEmployee: public Employee {
public:
	void computeSalary()
	{
		double salary = basicpay;
		cout << "Enter Allowance: \n";
		double allowance;
		cin >> allowance;
		salary += allowance;
		cout << "Your Salary is: " << salary << "\n";
	}
};

signed main() {

	Employee *e;
	PermanentEmployee p;
	ContractualEmployee c;

	e = &p;
	e->getinput();

	e = &c;
	e->getinput();

	return 0;
}