#include <iostream>

using namespace std;

class Applicant {
	static int lastId;
	int id;
	char name[30];
	int score;
public:
	void input();
	void output();
	static int numberOfStudents();
	static void increment();
};

int Applicant::lastId = 0;

void Applicant::input()
{
	cout << "Enter data of applicant: \n";
	id = Applicant::numberOfStudents() + 1;
	increment();
	cout << "Enter name: \n";
	scanf(" %[^\n]s", name);
	cout << "Enter score: \n";
	cin >> score;
}

void Applicant::output()
{
	cout << "Data entered successfully. \n";
	cout << "Student ID: " << id << "\n";
	cout << "Nane: " << name << "\n";
	cout << "Score: " << score << "\n";
}

int Applicant::numberOfStudents()
{
	return Applicant::lastId;
}

void Applicant::increment()
{
	++Applicant::lastId;
}

class Batch {
	Applicant a[100];
public:
	void menu();
};

void Batch::menu()
{
	int choice = 0;
	do {
		cout << "Select what to do.\n";
		cout << "Press 1 to apply.\n";
		cout << "Press 2 to see number of applicants.\n";
		cout << "Press 3 to exit.\n";
		cin >> choice;
		switch (choice) {
		case 1:	a[Applicant::numberOfStudents()].input();
			a[Applicant::numberOfStudents() - 1].output();
			break;
		case 2:	cout << "Number of applicants: " << Applicant::numberOfStudents() << "\n";
			break;
		case 3:	exit(0);
			break;
		case 4:
			break;
		}
	} while (choice != 3);
}

signed main() {

	Batch b;
	b.menu();

	return 0;
}