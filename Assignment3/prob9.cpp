#include <iostream>

using namespace std;

class TIME {
	int h, m, s;
	bool isSet;
public:
	TIME()
	{
		h = 0, m = 0, s = 0;
		isSet = false;
	}
	void menu();
	void input();
	void output24hr();
	void output12hr();
	void addmin();
};

void TIME::menu()
{
	cout << "\nSelect what to do.\n";
	cout << "Press 1 to set initial time.\n";
	cout << "Press 2 to view the current time in 24hrs format.\n";
	cout << "Press 3 to view the current time in 12hrs format.\n";
	cout << "Press 4 to add minutes to the current time.\n";
	cout << "Press 5 to exit.\n";
}

void TIME::input()
{
	int choice = 0;
	cout << "How do you want to enter the time?\n";
	cout << "1. 24 hr format\n2. 12 hr format (AM / PM).\nEnter your choice (1/2): \n";
	cin >> choice;
	if (choice == 1) {
		cout << "Enter the time in hh : mm : ss format\n";
		cout << "ALERT: 0 <= hh <= 23  0 <= mm <= 59  0 <= ss <= 59\n";
		cout << "hh: ";
		cin >> h;
		cout << "mm: ";
		cin >> m;
		cout << "ss: ";
		cin >> s;
		isSet = true;
		bool ok = 1;
		if (h < 0 || h > 23)
			ok = 0;
		if (m < 0 || m > 59)
			ok = 0;
		if (s < 0 || s > 59)
			ok = 0;
		if (!ok) {
			cout << "Invalid Time!\n";
			h = m = s = 0;
			isSet = false;
		}
	} else if (choice == 2) {
		cout << "Enter the time in hh : mm : ss (AM / PM) format\n";
		cout << "ALERT: 1 <= hh <= 12  0 <= mm <= 59  0 <= ss <= 59\n";
		cout << "hh: ";
		cin >> h;
		cout << "mm: ";
		cin >> m;
		cout << "ss: ";
		cin >> s;
		cout << "(AM / PM)? Press 1 for AM, 2 for PM\n";
		int zone = 0;
		cin >> zone;
		isSet = true;
		bool ok = 1;
		if (h < 1 || h > 12)
			ok = 0;
		if (m < 0 || m > 59)
			ok = 0;
		if (s < 0 || s > 59)
			ok = 0;
		if (!ok) {
			cout << "Invalid Time!\n";
			h = m = s = 0;
			isSet = false;
		}
		if (zone == 1) {
			if (h == 12) {
				h = 0;
			}
		} else {
			h += 12;
		}
	} else {
		cout << "Invalid Choice.\n";
	}
}

void TIME::output24hr()
{
	if (isSet) {
		cout << "Current time is: " << h << " : " << m << " : " << s << "\n";
	} else {
		cout << "Initial time is still not set. Please set the time first.\n";
	}
}

void TIME::output12hr()
{
	if (isSet) {
		if (h < 12) {
			cout << "Current time is: " << (h == 0 ? 12 : h) << " : " << m << " : " << s << " AM\n";
		} else {
			cout << "Current time is: " << (h == 12 ? 12 : h - 12) << " : " << m << " : " << s << " PM\n";
		}
	} else {
		cout << "Initial time is still not set. Please set the time first.\n";
	}
}

void TIME::addmin()
{
	if (isSet) {
		cout << "Enter time in minutes to add: \n";
		int mins = 0;
		cin >> mins;
		int hrs = mins / 60;
		mins %= 60;
		(h += hrs) %= 24;
		if (m + mins >= 60) {
			(h += 1) %= 24;
			(m += mins) %= 60;
		} else {
			m += mins;
		}
	} else {
		cout << "Initial time is still not set. Please set the time first.\n";
	}
}

signed main() {

	TIME t;
	int choice;
	do {
		t.menu();
		cin >> choice;
		switch (choice) {
		case 1:	t.input();
			break;
		case 2:	t.output24hr();
			break;
		case 3:	t.output12hr();
			break;
		case 4:	t.addmin();
			break;
		case 5:	exit(0);
			break;
		default: cout << "Invalid Choice.\n";
		}
	} while (choice != 5);

	return 0;
}