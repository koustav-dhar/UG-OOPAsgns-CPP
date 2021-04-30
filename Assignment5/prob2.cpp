#include <iostream>
#include <ctime>

using namespace std;

class Book {
protected:
	int bookid;
	char title[101];
	char author[31];
	char publisher[31];
	int price;
public:
	void getid()
	{
		cout << "Enter book id: \n";
		cin >> bookid;
	}
	void getdetails()
	{
		cout << "Enter book title: \n";
		scanf(" %[^\n]s", title);
		cout << "Enter author name: \n";
		scanf(" %[^\n]s", author);
		cout << "Enter publisher name: \n";
		scanf(" %[^\n]s", publisher);
		cout << "Enter price: \n";
		cin >> price;
	}
};

class Copies {
	int slno;
	int available;
	Copies *next;
public:
	Copies(int sl = -1, int avl = 0)
	{
		slno = sl;
		available = avl;
		next = NULL;
	}
	friend class BookNode;
};

class BookNode: public Book {
protected:
	int noOfCopies;
	Copies *head;
	BookNode *next;
public:
	BookNode()
	{
		noOfCopies = 0;
		head = NULL;
		next = NULL;
	}
	bool searchCopy(int sno)
	{
		return (noOfCopies >= sno);
	}
	void addCopy()
	{
		Copies *temp;
		if (head == NULL) {
			temp = new Copies(1, 1);
			head = temp;
			++noOfCopies;
			return;
		}
		temp = head;
		int cnt = 2;
		while (temp->next != NULL) {
			temp = temp->next;
			++cnt;
		}
		Copies* newNode = new Copies(cnt, 1);
		temp->next = newNode;
		++noOfCopies;
	}
	int getFirstAvailable()
	{
		Copies *temp = head;
		int res = 0;
		while (temp != NULL) {
			++res;
			if (temp->available) {
				return res;
			}
			temp = temp->next;
		}
		return -1;
	}
	void toggleCopy(int sno)
	{
		if (noOfCopies < sno) {
			cout << "Invalid Serial Number passed.\n";
			return;
		}
		Copies *temp = head;
		while (temp != NULL) {
			if (temp->slno == sno) {
				temp->available ^= 1;
				cout << "Book Status Updated.\n";
				return;
			}
			temp = temp->next;
		}
	}
	friend class BookList;
};

class BookList {
	BookNode *head;
public:
	BookList()
	{
		head = NULL;
	}
	BookNode* searchBook(int bid)
	{
		BookNode *temp = head;
		while (temp != NULL) {
			if (temp->bookid == bid) {
				return temp;
			}
			temp = temp->next;
		}
		return NULL;
	}
	void addBook()
	{
		BookNode *newNode = new BookNode;
		newNode->getid();
		if (searchBook(newNode->bookid) != NULL) {
			cout << "Book ID already exists.\n";
			cout << "Adding one more copy of the book to our shelf.\n";
			BookNode *temp = searchBook(newNode->bookid);
			temp->addCopy();
			return;
		}
		newNode->getdetails();
		newNode->addCopy();
		newNode->next = NULL;
		if (head == NULL) {
			head = newNode;
			cout << "Added the book to our shelf successfully.\n";
			return;
		}
		BookNode *temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newNode;
		cout << "Added the book to our shelf successfully.\n";
	}
	// will return the serial number which will be issued,
	// -1 if no more books are available
	int issueBook(int bid)
	{
		if (searchBook(bid) != NULL) {
			BookNode *temp = searchBook(bid);
			int sno = temp->getFirstAvailable();
			if (sno > 0) {
				temp->toggleCopy(sno);
				return sno;
			} else {
				cout << "Sorry. We don\'t have any available copies of the book you\'re looking for.\n";
				return -1;
			}
		} else {
			cout << "Invalid Book ID given.\n";
			return 0;
		}
	}
	void returnBook(int bid, int sno)
	{
		if (searchBook(bid) != NULL) {
			BookNode *temp = searchBook(bid);
			temp->toggleCopy(sno);
		} else {
			cout << "Invalid Book ID given.\n";
		}
	}
};


class Member {
protected:
	static int count;
	int memberid;
	char name[31];
	char email[31];
	char address[101];
	int cardsLeft;
public:
	virtual void getinput() = 0;
	bool canIssue()
	{
		return (cardsLeft > 0);
	}
	void Issue()
	{
		--cardsLeft;
	}
	void Return()
	{
		++cardsLeft;
	}
};

int Member::count = 0;

class StudentMember: public Member {
	StudentMember *next;
public:
	StudentMember()
	{
		next = NULL;
	}
	void getinput()
	{
		cout << "Enter name: \n";
		scanf(" %[^\n]s", name);
		cout << "Enter email id: \n";
		cin >> email;
		cout << "Enter address: \n";
		scanf(" %[^\n]s", address);
		cout << "You are successfully registered as a student. \n";
		++Member::count;
		memberid = Member::count;
		cout << "Your Member ID is " << memberid << ". Kindly note it down.\n";
		cardsLeft = 2;
		cout << "You can have 2 books issued at a point of time.\n";
	}
	void displayname()
	{
		cout << "Name: " << name << ".\n";
		cout << "Member Type: Student.\n";
	}
	friend class StudentList;
};

class FacultyMember: public Member {
	FacultyMember *next;
public:
	FacultyMember()
	{
		next = NULL;
	}
	void getinput()
	{
		cout << "Enter name: \n";
		scanf(" %[^\n]s", name);
		cout << "Enter email id: \n";
		cin >> email;
		cout << "Enter address: \n";
		scanf(" %[^\n]s", address);
		cout << "You are successfully registered as a faculty. \n";
		++Member::count;
		memberid = Member::count;
		cout << "Your Member ID is " << memberid << ". Kindly note it down.\n";
		cardsLeft = 10;
		cout << "You can have 10 books issued at a point of time.\n";
	}
	void displayname()
	{
		cout << "Name: " << name << ".\n";
		cout << "Member Type: Faculty.\n";
	}
	friend class FacultyList;
};

class StudentList {
	StudentMember *head;
public:
	StudentList()
	{
		head = NULL;
	}
	StudentMember* searchStudent(int sid)
	{
		StudentMember *temp = head;
		while (temp != NULL) {
			if (temp->memberid == sid) {
				return temp;
			}
			temp = temp->next;
		}
		return NULL;
	}
	void addStudent()
	{
		StudentMember *newNode = new StudentMember;
		newNode->getinput();
		if (head == NULL) {
			head = newNode;
			return;
		}
		StudentMember *temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newNode;
	}
	bool canIssueStudent(int sid)
	{
		if (searchStudent(sid) != NULL) {
			StudentMember *temp = searchStudent(sid);
			return temp->canIssue();
		} else {
			cout << "Invalid Student Member ID entered.\n";
			return false;
		}
	}
	void IssueStudent(int sid)
	{
		if (searchStudent(sid) != NULL) {
			StudentMember *temp = searchStudent(sid);
			temp->Issue();
		} else {
			cout << "Invalid Student Member ID entered.\n";
		}
	}
	void ReturnStudent(int sid)
	{
		if (searchStudent(sid) != NULL) {
			StudentMember *temp = searchStudent(sid);
			temp->Return();
		} else {
			cout << "Invalid Student Member ID entered.\n";
		}
	}
};

class FacultyList {
	FacultyMember *head;
public:
	FacultyList()
	{
		head = NULL;
	}
	FacultyMember* searchFaculty(int fid)
	{
		FacultyMember *temp = head;
		while (temp != NULL) {
			if (temp->memberid == fid) {
				return temp;
			}
			temp = temp->next;
		}
		return NULL;
	}
	void addFaculty()
	{
		FacultyMember *newNode = new FacultyMember;
		newNode->getinput();
		if (head == NULL) {
			head = newNode;
			return;
		}
		FacultyMember *temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newNode;
	}
	bool canIssueFaculty(int fid)
	{
		if (searchFaculty(fid) != NULL) {
			FacultyMember *temp = searchFaculty(fid);
			return temp->canIssue();
		} else {
			cout << "Invalid Faculty Member ID entered.\n";
			return false;
		}
	}
	void IssueFaculty(int fid)
	{
		if (searchFaculty(fid) != NULL) {
			FacultyMember *temp = searchFaculty(fid);
			temp->Issue();
		} else {
			cout << "Invalid Faculty Member ID entered.\n";
		}
	}
	void ReturnFaculty(int fid)
	{
		if (searchFaculty(fid) != NULL) {
			FacultyMember *temp = searchFaculty(fid);
			temp->Return();
		} else {
			cout << "Invalid Faculty Member ID entered.\n";
		}
	}
};


class Transactions {
	int dd, mm, yy;
	int memid;
	char type;
	int bkid;
	int sno;
	int returned;
	Transactions *next;
public:
	Transactions()
	{
		dd = mm = yy = -1;
		memid = bkid = sno = -1;
		returned = 0;
		next = NULL;
	}
	bool getinputIssue(BookList *headb, StudentList *heads, FacultyList *headf, int willissue = 1)
	{
		cout << "Enter your Member ID:\n";
		cin >> memid;
		if (heads->searchStudent(memid)) {
			type = 's';
		} else if (headf->searchFaculty(memid)) {
			type = 'f';
		} else {
			cout << "This Member ID doesn\'t exist. Please enter valid ID.\n";
			return false;
		}
		time_t now = time(0);
		tm *ltm = localtime(&now);
		dd = ltm->tm_mday;
		mm = ltm->tm_mon;
		yy = ltm->tm_year;
		returned = 0;
		cout << "Enter Book ID: \n";
		cin >> bkid;
		if (willissue) {
			if (type == 's') {
				if (heads->canIssueStudent(memid)) {
					int serial = headb->issueBook(bkid);
					if (serial > 0) {
						sno = serial;
						heads->IssueStudent(memid);
					} else {
						return false;
					}
				} else {
					cout << "You cannot issue anymore books.\n";
					return false;
				}
			} else {
				if (headf->canIssueFaculty(memid)) {
					int serial = headb->issueBook(bkid);
					if (serial > 0) {
						sno = serial;
						headf->IssueFaculty(memid);
					} else {
						return false;
					}
				} else {
					cout << "You cannot issue anymore books.\n";
					return false;
				}
			}
			return true;
		} else {
			cout << "Enter Serial Number: \n";
			cin >> sno;
			return true;
		}
	}
	void returnIssue(BookList *headb, StudentList *heads, FacultyList *headf)
	{
		if (type == 's') {
			heads->ReturnStudent(memid);
		} else {
			headf->ReturnFaculty(memid);
		}
		headb->returnBook(bkid, sno);
		returned = 1;
		cout << "Book Returned successfully.\n";
	}
	bool compare(Transactions *returning)
	{
		if (returned == 0 && memid == returning->memid && bkid == returning->bkid && sno == returning->sno)
			return true;
		return false;
	}
	void issueReceipt(BookList *headb, StudentList *heads, FacultyList *headf)
	{
		cout << "Issue Successful!.\n";
		cout << "Receipt:\n";
		cout << "Date of Issue: " << dd << " / " << mm << " / " << yy << "\n";
		if (type == 's') {
			StudentMember *temp = heads->searchStudent(memid);
			temp->displayname();
		} else {
			FacultyMember *temp = headf->searchFaculty(memid);
			temp->displayname();
		}
		cout << "Book ID: " << bkid << "\n";
		cout << "Serial Number: " << sno << "\n";
	}
	friend class TransactionsList;
};

class TransactionsList {
	Transactions *head;
public:
	TransactionsList()
	{
		head = NULL;
	}
	Transactions* searchTransaction(Transactions *another)
	{
		Transactions *temp = head;
		while (temp != NULL) {
			if (temp->compare(another)) {
				return temp;
			}
			temp = temp->next;
		}
		return NULL;
	}
	void addTransaction(BookList *headb, StudentList *heads, FacultyList *headf)
	{
		Transactions *newNode = new Transactions;
		if (newNode->getinputIssue(headb, heads, headf)) {
			if (head == NULL) {
				head = newNode;
				newNode->issueReceipt(headb, heads, headf);
				return;
			}
			Transactions *temp = head;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = newNode;
			newNode->issueReceipt(headb, heads, headf);
		} else {
			cout << "Given request couldn\'t be issued.\n";
		}
	}
	void returnTransaction(BookList *headb, StudentList *heads, FacultyList *headf)
	{
		Transactions *temp = new Transactions;
		temp->getinputIssue(headb, heads, headf, 0);
		Transactions *temp2 = searchTransaction(temp);
		if (temp2 != NULL) {
			temp2->returnIssue(headb, heads, headf);
		} else {
			cout << "Enter valid details. No issue found with given details.\n";
		}
	}
};


class Operations {
	BookList B;
	StudentList S;
	FacultyList F;
	TransactionsList T;
public:
	int screen()
	{
		cout << "\nSelect what to perform:";
		cout << "\nPress 1 to add a book to the library.";
		cout << "\nPress 2 to register yourself.";
		cout << "\nPress 3 to issue a book.";
		cout << "\nPress 4 to return a book.";
		cout << "\nPress 5 to exit.";
		cout << "\nEnter a choice: \n";
		int choice;
		cin >> choice;
		return choice;
	}
	void operate()
	{
		int ch;
		while (1) {
			switch (screen()) {
			case 1:
				B.addBook();
				break;
			case 2:
				cout << "Select your status: \n";
				cout << "Press 1 if you are a student.\n";
				cout << "Press 2 if you are a faculty member.\n";
				cin >> ch;
				if (ch == 1) {
					S.addStudent();
				} else if (ch == 2) {
					F.addFaculty();
				} else {
					cout << "Invalid Choice.\n";
				}
				break;
			case 3:
				T.addTransaction(&B, &S, &F);
				break;
			case 4:
				T.returnTransaction(&B, &S, &F);
				break;
			case 5:
				exit(0);
				break;
			default:
				cout << "Invalid Choice.\n";
				break;
			}
		}
	}
};

signed main() {

	Operations O;
	O.operate();

	return 0;
}