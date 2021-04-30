#include <iostream>

using namespace std;

class Withdraw;

class AccountList;

class Account {
	int acc_number;
	int balance_amt;
	Account* next;
public:
	Account()
	{
		acc_number = -1;
		balance_amt = 0;
		next = NULL;
	}
	void get_input()
	{
		cout << "Enter account number: \n";
		cin >> acc_number;
		cout << "Enter balance amount: \n";
		cin >> balance_amt;
		next = NULL;
	}
	friend class AccountList;
};

class Withdraw {
	int acc_number;
	int withdraw_amt;
public:
	Withdraw()
	{
		acc_number = -1;
		withdraw_amt = 0;
	}
	void get_input();
	friend class AccountList;
};

void Withdraw::get_input()
{
	cout << "Enter account number: \n";
	cin >> acc_number;
	cout << "Enter amount to be withdrawn: \n";
	cin >> withdraw_amt;
}

class AccountList {
	Account* head;
	Withdraw wobj;
public:
	AccountList()
	{
		head = NULL;
	}
	void add_account();
	bool find_account(int ac_num);
	void withdraw_amount();
	void display_accounts();
};

void AccountList::add_account()
{
	Account* newNode = new Account;
	newNode->get_input();
	if (find_account(newNode->acc_number) == true) {
		cout << "Please enter a unique account number, this account number already exists.\n";
		return;
	}
	if (head == NULL) {
		head = newNode;
		cout << "Account added successfully.\n";
		return;
	}
	Account* temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = newNode;
	cout << "Account added successfully.\n";
}

bool AccountList::find_account(int ac_num)
{
	Account* temp = head;
	while (temp != NULL) {
		if (temp->acc_number == ac_num) {
			cout << "Account with account number " << ac_num << " found.\n";
			return true;
		}
		temp = temp->next;
	}
	cout << "Account with account number " << ac_num << " couldn\'t be found.\n";
	return false;
}

void AccountList::display_accounts()
{
	if (head == NULL) {
		cout << "No accounts present to display. Try adding some accounts.\n";
		return;
	}
	Account* temp = head;
	while (temp != NULL) {
		cout << "\nAccount Number: " << temp->acc_number;
		cout << "\nBalance Amount: " << temp->balance_amt << "\n";
		temp = temp->next;
	}
}

void AccountList::withdraw_amount()
{
	wobj.get_input();
	if (find_account(wobj.acc_number) == false) {
		cout << "Enter a valid account number.\n";
		return;
	}
	Account* temp = head;
	while (temp != NULL) {
		if (temp->acc_number == wobj.acc_number) {
			if (wobj.withdraw_amt > temp->balance_amt) {
				cout << "Not enough cash to withdraw. Try a smaller amount.\n";
				return;
			} else {
				temp->balance_amt -= wobj.withdraw_amt;
				wobj.acc_number = -1;
				wobj.withdraw_amt = 0;
				cout << "Transaction successful!\n";
				return;
			}
		}
		temp = temp->next;
	}
}

class Operations {
	AccountList A;
public:
	int screen();
	void operate();
};

int Operations::screen()
{
	cout << "\nSelect any option to perform respective operation.";
	cout << "\nPress 1 to add an account.";
	cout << "\nPress 2 to check if an account is present.";
	cout << "\nPress 3 to display all accounts.";
	cout << "\nPress 4 to withdraw amount.";
	cout << "\nPress 5 to exit.\n";
	int choice;
	cin >> choice;
	return choice;
}

void Operations::operate()
{
	while (1) {
		int ac_num;
		switch (screen()) {
		case 1:
			A.add_account();
			break;
		case 2:
			cout << "Enter account number of the account to be searched: \n";
			cin >> ac_num;
			A.find_account(ac_num);
			break;
		case 3:
			A.display_accounts();
			break;
		case 4:
			A.withdraw_amount();
			break;
		case 5:
			exit(0);
			break;
		default:
			cout << "Invalid Choice. Try Again.\n";
			break;
		}
	}
}

signed main() {

	Operations O;
	O.operate();

	return 0;
}