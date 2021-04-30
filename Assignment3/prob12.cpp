#include <bits/stdc++.h>

using namespace std;

class Student {
	static int lastId;
	int roll;
	char name[30];
	char dept[10];
	int dd;
	int mm;
	int yyyy;
	int score[5];
public:
	Student()
	{
		roll = dd = mm = yyyy = -1;
		for (int i = 0; i < 5; ++i) {
			score[i] = -1;
		}
	}
	void admission();
	void input_marks();
	bool check_marks_allocated();
	void prepare_marksheet();
	static int numOfStudents();
};

int Student::lastId = 0;

void Student::admission()
{
	cout << "Enter date of admission (dd / mm / yyyy): \n";
	cout << "Enter dd: ";
	cin >> dd;
	cout << "Enter mm: ";
	cin >> mm;
	cout << "Enter yyyy: ";
	cin >> yyyy;
	cout << "Enter name of student: ";
	scanf(" %[^\n]s", name);
	cout << "Enter course: ";
	cin >> dept;
	++Student::lastId;
	roll = lastId;
	cout << "Allotted roll number is: " << roll;
}

void Student::input_marks()
{
	cout << "Enter score of 5 subjects: \n";
	for (int i = 0; i < 5; ++i) {
		cout << "Enter score of subject " << (i + 1) << ": ";
		cin >> score[i];
	}
}

bool Student::check_marks_allocated()
{
	bool ok = 1;
	for (int i = 0; i < 5; ++i) {
		if (score[i] < 0) {
			ok = 0;
			break;
		}
	}
	return ok;
}

void Student::prepare_marksheet()
{
	if (check_marks_allocated() == false) {
		cout << "\nEnter marks first!!!\n";
		return;
	}
	cout << "\n-------------------------------------------------------------------\n";
	cout << "MARKSHEET OF " << name << "\n";
	cout << "Roll - " << roll << "\n";
	cout << "Dept - " << dept << "\n";
	cout << "Date of admission(dd / mm / yyyy): " << dd << " / " << mm << " / " << yyyy << "\n";
	cout << "Marks: \n";
	for (int i = 0; i < 5; ++i) {
		cout << "Subject " << (i + 1) << ": " << score[i] << "\n";
	}
	cout << "-------------------------------------------------------------------\n";
}

int Student::numOfStudents()
{
	return Student::lastId;
}

class Batch {
	Student s[100];
public:
	int input_roll();
	void menu();
};

int Batch::input_roll()
{
	cout << "Enter roll of the student: \n";
	int r;
	cin >> r;
	if (r > 0 && r <= Student::numOfStudents()) {
		return r;
	} else {
		cout << "Student with entered roll doesn\'t exist!\n";
		return 0;
	}
}

void Batch::menu()
{
	int choice = 0;
	do {
		cout << "\nSelect what to do.\n";
		cout << "Press 1 to take admission.\n";
		cout << "Press 2 to see number of admitted students.\n";
		cout << "Press 3 to enter scores of an admitted student.\n";
		cout << "Press 4 to see the marksheet of an admitted student.\n";
		cout << "Press 5 to exit.\n";
		cin >> choice;
		int r;
		switch (choice) {
		case 1:	s[Student::numOfStudents()].admission();
			break;
		case 2:	cout << "\nNumber of students taken admission is " << Student::numOfStudents() << "\n";
			break;
		case 3:	r = input_roll();
			if (r) {
				s[r - 1].input_marks();
			}
			break;
		case 4:	r = input_roll();
			if (r) {
				s[r - 1].prepare_marksheet();
			}
			break;
		case 5:	exit(0);
			break;
		}
	} while (choice != 5);
}

signed main() {

	Batch b;
	b.menu();

	return 0;
}