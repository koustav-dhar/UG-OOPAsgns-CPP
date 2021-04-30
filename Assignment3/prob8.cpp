#include <iostream>

using namespace std;

struct student {
	int roll;
	int score;
	void input();
	void output();
};

void student::input()
{
	cout << "Enter roll: \n";
	cin >> roll;
	cout << "Enter score: \n";
	cin >> score;
}

void student::output()
{
	cout << "The student data is: \n";
	cout << "Roll no.: " << roll << "\n";
	cout << "Score: " << score << "\n";
}

void modify(student& a)
{
	char choicer = 'n', choices = 'n';
	cout << "Do you want to modify your roll? (y/n): \n";
	cin >> choicer;
	if (choicer == 'y') {
		cout << "Enter new roll: \n";
		int newr;
		cin >> newr;
		a.roll = newr;
	}
	cout << "Do you want to modify your score? (y/n): \n";
	cin >> choices;
	if (choices == 'y') {
		cout << "Enter new score: \n";
		int news;
		cin >> news;
		a.score = news;
	}

	cout << "Successfully Updated!\n";
	a.output();
}

signed main() {

	student a;
	a.input();
	a.output();
	modify(a);

	return 0;
}