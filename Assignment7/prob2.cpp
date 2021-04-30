#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

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

// class for function object for substring check
class substring_check {
	int fnf;
	string sub;
public:
	substring_check(int type = 1, const string s = "")
	{
		fnf = type;
		sub = s;
	}
	void operator()(const Student &s)const	// overloading () operator for the function object
	{
		if ((s.ret_name().find(sub) == string::npos) ^ (fnf)) {
			s.showdata();
		}
	}
};

class Batch {
	vector<Student> v;
public:
	int screen()
	{
		cout << "\nSelect what to perform.";
		cout << "\nPress 1 to add a student.";
		cout << "\nPress 2 to find no of students.";
		cout << "\nPress 3 to find highest score.";
		cout << "\nPress 4 to find students with given substring present in their names.";
		cout << "\nPress 5 to find students with given substring not present in their names.";
		cout << "\nPress 6 to remove a student.";
		cout << "\nPress 7 to sort the students in descending order of their scores and view.";
		cout << "\nPress 8 to combine two student collections.";
		cout << "\nPress 9 to exit.\n";
		int choice;
		cin >> choice;
		return choice;
	}
	void operate()
	{
		while (1) {
			Student S;
			vector<Student>::iterator it;
			string sub;
			switch (screen()) {
			case 1:
				S.getdata();
				v.push_back(S);
				break;
			case 2:
				cout << "No of students: " << v.size() << "\n";
				break;
			case 3:
				if (v.empty()) {
					cout << "No students added.\n";
					break;
				}
				it = max_element(v.begin(), v.end());
				cout << "Highest Score: " << it->ret_score() << "\n";
				break;
			case 4:
				cout << "Enter substring: \n";
				cin >> sub;
				for_each(v.begin(), v.end(), substring_check(1, sub));
				break;
			case 5:
				cout << "Enter substring: \n";
				cin >> sub;
				for_each(v.begin(), v.end(), substring_check(0, sub));
				break;
			case 6:
			{
				cout << "Enter roll to be removed: \n";
				int r;
				cin >> r;
				it = find(v.begin(), v.end(), r);
				v.erase(it);
				break;
			}
			case 7:
				sort(v.begin(), v.end(), greater<Student>());
				for (it = v.begin(); it != v.end(); ++it) {
					it->showdata();
				}
				break;
			case 8:
			{
				cout << "Enter number of new students: \n";
				int n;
				cin >> n;
				vector<Student> v2(n);
				for (int i = 0; i < n; ++i) {
					v2[i].getdata();
				}
				copy(v2.begin(), v2.end(), back_inserter(v));
				break;
			}
			case 9:
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