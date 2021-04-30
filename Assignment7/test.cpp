// #include <iostream>
// #include <vector>
// #include <algorithm>

// using namespace std;

// class if_lower {
// 	int lowlimit;
// public:
// 	if_lower(int val = 0)
// 	{
// 		lowlimit = val;
// 	}
// 	bool operator()(const int s)const
// 	{
// 		return (s < lowlimit);
// 	}
// };

// class low_scores {
// 	int lowlimit;
// public:
// 	low_scores(int val = 0)
// 	{
// 		lowlimit = val;
// 	}
// 	void operator()(const int s)const
// 	{
// 		if (s < lowlimit) {
// 			cout << "Low Score -> " << s << "\n";
// 		} else {
// 			cout << "Score OK -> " << s << "\n";
// 		}
// 	}
// };



// signed main() {

// 	vector<int> scores = {90, 70, 39, 37, 50};
// 	vector<int>::iterator it;
// 	low_scores a;
// 	for_each(scores.begin(), scores.end(), a);

// 	return 0;
// }

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Student
{
	int roll;
	string name;
	int score;
public:
	Student(int r = 0, string n = "", int s = 0)
	{
		roll = r;
		name = n;
		score = s;
	}
	int ret_score() const
	{
		return score;
	}
	string ret_name() const
	{
		return name;
	}
	void show()
	{
		cout << roll << "  " << name << "  " << score << endl;
	}
	bool operator ==(const Student &s) const
	{
		return roll == s.roll;
	}
};
class compare_score_descending
{
public:
	bool operator()(const Student &s1, const Student &s2)
	{
		return s1.ret_score() > s2.ret_score();
	}
};
int main()
{
	vector<Student> stdlist;
	stdlist.push_back(Student(1, "Avirup", 89));
	stdlist.push_back(Student(2, "Anik", 95));
	stdlist.push_back(Student(3, "Anand", 79));
	stdlist.push_back(Student(4, "Souparno", 85));
	sort(stdlist.begin(), stdlist.end(), compare_score_descending());
	vector<Student>::iterator it;
	for (it = stdlist.begin(); it != stdlist.end(); it--)
	{
		it->show();
	}
	return 0;
}