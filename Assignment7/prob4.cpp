#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

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
	bool operator<(const Student &s)const	// overloading < operator based on score
	{
		return (score < s.score);
	}
	bool operator>(const Student &s)const	// overloading > operator based on score
	{
		return (score > s.score);
	}
	bool operator==(const int &r)const	// overloading == operator based on roll
	{
		return (roll == r);
	}
};

class Batch {
	priority_queue<Student> pq;
public:
	int screen()
	{
		cout << "\nSelect what to perform.";
		cout << "\nPress 1 to add a student.";
		cout << "\nPress 2 to find no of students.";
		cout << "\nPress 3 to find highest score.";
		cout << "\nPress 4 to display the ordering of students.";
		cout << "\nPress 5 to exit.\n";
		int choice;
		cin >> choice;
		return choice;
	}
	void operate()
	{
		while (1) {
			Student S;
			priority_queue<Student> temp;
			switch (screen()) {
			case 1:
				S.getdata();
				pq.push(S);
				break;
			case 2:
				cout << "No of students: " << pq.size() << "\n";
				break;
			case 3:
				if (pq.empty()) {
					cout << "No students added.\n";
					break;
				}
				cout << "Highest Score: " << pq.top().ret_score() << "\n";
				break;
			case 4:
				while (!pq.empty()) {
					temp.push(pq.top());
					pq.top().showdata();
					pq.pop();
				}
				while (!temp.empty()) {
					pq.push(temp.top());
					temp.pop();
				}
				break;
			case 5:

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