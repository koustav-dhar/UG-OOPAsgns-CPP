#include <iostream>
#include "myspace.cpp"

using namespace std;

namespace N1
{
void Student::get_input()
{
	cout << "Enter roll: \n";
	cin >> roll;
	cout << "Enter score: \n";
	cin >> score;
}
void Student::show_data()
{
	cout << "Roll: " << roll << "\n";
	cout << "Score: " << score << "\n";
}
}

signed main() {

	N1::Student S;
	S.get_input();
	S.show_data();

	return 0;
}

