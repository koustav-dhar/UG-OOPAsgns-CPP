#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

// defining a class for student
class Student {
	int roll;
	string name;
	int score;
public:
	Student(int r = 0, const string s = "", int sc = 0)
	{
		roll = r;
		name = s;
		score = sc;
	}
	int ret_roll()const	// accessor function to get roll
	{
		return roll;
	}
	string ret_name()const	// accessor function to get name
	{
		return name;
	}
	int ret_score()const	// accessor function to get score
	{
		return score;
	}
	void getdata()	// function to get input
	{
		cout << "Enter Roll: \n";
		cin >> roll;
		cout << "Enter Name: \n";
		cin >> name;
		cout << "Enter Score: \n";
		cin >> score;
	}
	void showdata()const	// function to print data
	{
		cout << "Roll: " << roll << "\n";
		cout << "Name: " << name << "\n";
		cout << "Score: " << score << "\n";
	}
	bool operator<(const Student &s)const	// overload < operator based on score
	{
		return (score < s.score);
	}
	bool operator==(const int &r)const	// overload == operator based on roll
	{
		return (roll == r);
	}
};

class Batch {
	map<int, Student> m;	// map with key as int and value as student
public:
	int screen()
	{
		cout << "\nSelect what to perform.";
		cout << "\nPress 1 to add a student.";
		cout << "\nPress 2 to find no of students.";
		cout << "\nPress 3 to get your score.";
		cout << "\nPress 4 to exit.\n";
		int choice;
		cin >> choice;
		return choice;
	}
	void operate()
	{
		while (1) {
			Student S;
			switch (screen()) {
			case 1:
				S.getdata();
				m[S.ret_roll()] = S;
				break;
			case 2:
				cout << "No of students: " << m.size() << "\n";
				break;
			case 3:
				int r;
				cout << "Enter roll: \n";
				cin >> r;
				if (m.find(r) == m.end())
					cout << "Not found.\n";
				else
					cout << "Your Score: " << m[r].ret_score() << "\n";
				break;
			case 4:
				exit(0);
				break;
			default:
				cout << "Invalid Choice.\n";
			}
		}
	}
};

signed main() {

	Batch B;
	B.operate();

	return 0;
}