#include <iostream>
#include <string.h>

using namespace std;

#define MAX 100

// defining class for a student
class Student {
	int roll;
	char name[31];
	int score;
public:
	Student(int r = -1, const char* s = "", int sc = 0)
	{
		roll = r;
		strcpy(name, s);
		score = sc;
	}
	void getinput()	// function to get input
	{
		cout << "Enter roll number: \n";
		cin >> roll;
		cout << "Enter name:\n";
		scanf(" %[^\n]s", name);
		cout << "Enter score:\n";
		cin >> score;
	}
	void showdata()	// function to print data
	{
		cout << "Roll: " << roll << "\n";
		cout << "Name: " << name << "\n";
		cout << "Score: " << score << "\n";
	}
};

// defining a batch class for a group of students
class Batch {
	static int total;
	Student S[MAX];
public:
	void addStudent()	// function to add a student
	{
		if (total == MAX)	// if no more space is there
			throw "overflow";	// throws overflow error message
		S[Batch::total].getinput();
		++Batch::total;
	}
	void showStudentbyIndex(int ind)	// function to show student data by index
	{
		if (ind <= 0 || ind > total) {	// if passed index is out of bounds
			throw "out of bounds";	// throw out of bounds error message
		}
		S[ind - 1].showdata();
	}
	void operate()
	{
		while (1) {
			cout << "\nSelect what to perform:";
			cout << "\nPress 1 to add a student.";
			cout << "\nPress 2 to display student details.";
			cout << "\nPress 3 to exit.\n";
			int choice;
			cin >> choice;
			int c;
			switch (choice) {
			case 1:
				try {
					addStudent();
				} catch (const char* s) {	// catch block for overflow error
					cout << "No more students can be added.\n";
				}
				break;
			case 2:
				try {
					cout << "Enter number of student you want to get info about: \n";
					cin >> c;
					showStudentbyIndex(c);
				} catch (const char* s) {	// catch block for out of bounds error
					cout << "Index passed is out of bounds.\n";
				}
				break;
			case 3:
				exit(0);
				break;
			default:
				cout << "Invalid choice.\n";
			}
		}
	}
};

int Batch::total = 0;

signed main() {

	Batch B;
	B.operate();

	return 0;
}