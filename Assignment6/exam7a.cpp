#include <iostream>
#include <string.h>
using namespace std;

class Date {
	int dd;
	int mm;
	int yy;
public:
	Date(int d = -1, int m = -1, int y = -1)
	{
		dd = d;
		mm = m;
		yy = y;
	}
	bool isEntered();
	friend bool operator<=(Date& a, Date& b);
};

class Scores {
	int student_roll;
	int assign_id;
	Date dt_of_submission;
	int late_submission_or_not;
	int score_obtained;
	Scores *next;
public:
	Scores(int roll = -1, int aid = -1)
	{
		student_roll = roll;
		assign_id = aid;
		score_obtained = 0;
		next = NULL;
	}
	void getinput();
	friend class Scoresheet;
};

class Scoresheet {
	Scores *head;
public:
	Scoresheet()
	{
		head = NULL;
	}
	bool search(int roll, int aid);
	void add_node(int roll, int aid);
	void submission(int roll, int aid, Date deadline);
	void update_score(int roll, int aid, int score);
	void update_score_all(int aid, int score);
	void not_submitted(int aid);
	int get_total_score(int roll);

};

class Assignment {
	int assign_id;
	char assign_title[51];
	Date dt_of_publish;
	Date dt_of_submission;
	int full_marks;
	Assignment *next;
public:
	Assignment()
	{
		next = NULL;
	}
	void getinput();
	void showdata();
	friend class AssignmentList;
};

class AssignmentList {
	Assignment *head;
public:
	AssignmentList()
	{
		head = NULL;
	}
	bool search(int aid);
	void add_asgn(int RollList[], Scoresheet S);
};

class Interface {
	AssignmentList A;
	Scoresheet S;
	int RollList[100];
public:
	Interface(int rollsheet[100], int n)
	{
		for (int i = 0; i < n; ++i) {
			RollList[i] = rollsheet[i];
		}
	}
	int menu();
	void submit_assignment();
	void give_score();

};


class MIDSEM {
protected:
	int class_roll;
	int internal_score;
public:
	void getinput();
	void showdata();
};

class MIDSEM_Scoresheet {
	MIDSEM m[100];
	int no_of_students;
public:
	bool search(int roll);
	void add_data(int roll, int score);
	int get_score(int roll);
};

class ENDSEM {
protected:
	int exam_roll;
	int exam_score;
public:
	void getinput();
	void showdata();
};

class ENDSEM_Scoresheet {
	ENDSEM e[100];
	int no_of_students;
public:
	void apply();
	void add_data(int eroll, int score);
	int get_score(int eroll);
};

class COMPOSITE: public MIDSEM, public ENDSEM {
	int total_score;
public:
	void getinput();	// MIDSEM::getinput(), then ENDSEM_Scoresheet::apply(), then adddata()
	void calc_score();
};

class COMPOSITE_Scoresheet {
	COMPOSITE c[100];
	int no_of_students;
public:
	void add_data();

};

signed main() {



	return 0;
}