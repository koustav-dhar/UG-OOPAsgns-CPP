#include <iostream>

using namespace std;

class Cricketer {
protected:
	char name[31];
	int dd, mm, yy;
	int matches_played;
public:
	void getinput()
	{
		cout << "Enter name: \n";
		scanf(" %[^\n]s", name);
		cout << "Enter date of birth: \n";
		cout << "Enter dd: ";
		cin >> dd;
		cout << "Enter mm: ";
		cin >> mm;
		cout << "Enter yyyy: ";
		cin >> yy;
		cout << "Enter matches played: \n";
		cin >> matches_played;
	}
	void showdetails()
	{
		cout << "Name: " << name << "\n";
		cout << "Date of Birth: " << dd << " / " << mm << " / " << yy << "\n";
		cout << "Matches Played: " << matches_played << "\n";
	}
};

class Batsman: virtual public Cricketer {
protected:
	int runs_scored;
	double batting_average;
public:
	void getinput(int flag = 1)
	{
		if (flag)
			Cricketer::getinput();
		cout << "Enter runs scored: \n";
		cin >> runs_scored;
		cout << "Enter batting average: \n";
		cin >> batting_average;
	}
	void showdetails(int flag = 1)
	{
		if (flag)
			Cricketer::showdetails();
		cout << "Runs Scored: " << runs_scored << "\n";
		cout << "Batting average: " << batting_average << "\n";
	}
};

class Bowler: virtual public Cricketer {
protected:
	int wickets_taken;
	double average_economy;
public:
	void getinput(int flag = 1)
	{
		if (flag)
			Cricketer::getinput();
		cout << "Enter wickets taken: \n";
		cin >> wickets_taken;
		cout << "Enter average economy: \n";
		cin >> average_economy;
	}
	void showdetails(int flag = 1)
	{
		if (flag)
			Cricketer::showdetails();
		cout << "wickets Taken: " << wickets_taken << "\n";
		cout << "Average Economy: " << average_economy << "\n";
	}
};

class AllRounder: public Batsman, public Bowler {
public:
	void getinput()
	{
		Batsman::getinput();
		Bowler::getinput(0);
	}
	void showdetails()
	{
		Batsman::showdetails();
		Bowler::showdetails(0);
	}
};

class DoubleWicketPair {
	Batsman bt;
	Bowler bo;
public:
	void getinput()
	{
		cout << "Enter details of the Batsman.\n";
		bt.getinput();
		cout << "Enter details of the Bowler.\n";
		bo.getinput();
	}
	void showdetails()
	{
		cout << "Batsman Details: \n";
		bt.showdetails();
		cout << "Bowler Details: \n";
		bo.showdetails();
	}
};

signed main() {



	return 0;
}