#include "bits/stdc++.h"

using namespace std;

class KD {
	int roll;
	int score1;
	int score2;
public:
	KD(int r = -1, int s1 = 0, int s2 = 0)
	{
		roll = r;
		score1 = s1;
		score2 = s2;
	}
	KD(KD& temp)
	{
		roll = temp.roll;
		score1 = score2 = (temp.score1 + temp.score2) / 2;
	}
	void get_score_difference(KD a);
	void print();
};

void KD::get_score_difference(KD a)
{
	cout << abs(score1 - a.score1) << " " << abs(score2 - a.score2) << "\n";
}

void KD::print()
{
	cout << roll << " " << score1 << " " << score2 << "\n";
}


class OO {
	int roll;
	int score;
public:
	OO(int r = -1, int s = 0)
	{
		roll = r , score = s;
	}
	OO(OO& temp)
	{
		roll = temp.roll;
		score = temp.score;
	}
	friend bool operator<(OO a, int b)
	{
		return (a.score < b);
	}
};

signed main() {
	// OO a(1, 99), b(2, 98);
	// if (5 < a) {
	// 	cout << "HELLO\n";
	// }

	KD a(1, 98, 98);
	KD b;
	b = a;
	b.print();

}