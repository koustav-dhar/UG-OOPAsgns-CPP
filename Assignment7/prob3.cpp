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

void addtoqueue(queue<Student> &q, vector<Student> &v, int r)
{
	vector<Student>::iterator it;
	it = find(v.begin(), v.end(), r);
	q.push(*it);
}

signed main() {

	vector<Student> v;
	v.push_back(Student(1, "StudentA", 97));
	v.push_back(Student(2, "StudentB", 86));
	v.push_back(Student(3, "StudentC", 91));
	v.push_back(Student(4, "StudentD", 77));
	v.push_back(Student(5, "StudentE", 84));

	queue<Student> q;
	addtoqueue(q, v, 2);
	addtoqueue(q, v, 1);
	addtoqueue(q, v, 5);

	while (!q.empty()) {
		q.front().showdata();
		q.pop();
	}

	return 0;
}