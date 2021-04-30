#include <iostream>

namespace N1
{
class Student {
	int roll;
	int score;
public:
	int get_score()
	{
		return score;
	}
	void get_input();
	void show_data();
};
}

// signed main() {
// 	return 0;
// }