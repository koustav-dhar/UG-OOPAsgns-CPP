#include <iostream>
#include <fstream>
#include <ctime>
#include <string.h>
#include <bits/stdc++.h>

#define max_copies 25

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
public:
	Copies(int sl = -1, int avl = 0)
	{
		slno = sl;
		available = avl;
	}
	friend class BookNode;
};

class BookNode: public Book {
protected:
	int noOfCopies;
	Copies copyList[max_copies];
public:
	BookNode()
	{
		noOfCopies = 0;
	}
	bool searchCopy(int sno)
	{
		return (noOfCopies >= sno);
	}
	void addCopy()
	{
		if (noOfCopies < max_copies) {
			Copies temp(noOfCopies + 1, 1);
			copyList[noOfCopies] = temp;
			++noOfCopies;
		} else {
			cout << "Couldn\'t add more copies.\n";
		}
	}
	int getFirstAvailable()
	{
		for (int i = 0; i < noOfCopies; ++i) {
			if (copyList[i].available == 1) {
				return i + 1;
			}
		}
		return -1;
	}
	void toggleCopy(int sno)
	{
		if (noOfCopies < sno) {
			cout << "Invalid Serial Number passed.\n";
			return;
		}
		copyList[sno - 1].available ^= 1;
		cout << "Book Status Updated.\n";
	}
	friend class BookListFile;
};

class BookListFile {
	char filename[31];
public:
	BookListFile(const char* s = "")
	{
		strcpy(filename, s);
		fstream f(filename, ios::app | ios::binary);
		f.close();
	}
	int searchBook(int bid)
	{
		fstream fin(filename, ios::in | ios::binary);

		BookNode B;
		int cnt = 0;
		while (!fin.eof()) {
			fin.read((char*)&B, sizeof(BookNode));
			++cnt;
			if (B.bookid == bid) {
				fin.close();
				return cnt;
			}
		}
		fin.close();
		return 0;
	}
	void addBook()
	{
		fstream f;
		BookNode B;
		B.getid();
		int k = searchBook(B.bookid);
		if (k != 0) {
			cout << "Book ID already exists.\n";
			cout << "Adding one more copy of the book to our shelf.\n";
			f.open(filename, ios::in | ios::out | ios::binary);
			f.seekg((k - 1)*sizeof(BookNode), ios::beg);
			f.read((char*)&B, sizeof(BookNode));
			B.addCopy();
			f.clear();
			f.seekp((k - 1)*sizeof(BookNode), ios::beg);
			f.write((char*)&B, sizeof(BookNode));
			f.close();
		} else {
			B.getdetails();
			B.addCopy();
			f.open(filename, ios::app | ios::binary);
			f.write((char*)&B, sizeof(BookNode));
			f.close();
			cout << "Added the book to our shelf successfully.\n";
		}
	}
	// will return the serial number which will be issued,
	// -1 if no more books are available
	int issueBook(int bid)
	{
		fstream f;
		BookNode B;
		int k = searchBook(bid);
		if (k == 0) {
			cout << "Invalid Book ID given.\n";
			return 0;
		} else {
			f.open(filename, ios::in | ios::out | ios::binary);
			f.seekg((k - 1)*sizeof(BookNode), ios::beg);
			f.read((char*)&B, sizeof(BookNode));
			int sno = B.getFirstAvailable();
			if (sno > 0) {
				B.toggleCopy(sno);
				f.clear();
				f.seekp((k - 1)*sizeof(BookNode), ios::beg);
				f.write((char*)&B, sizeof(BookNode));
				f.close();
				return sno;
			} else {
				cout << "Sorry. We don\'t have any available copies of the book you\'re looking for.\n";
				f.close();
				return -1;
			}
		}
	}
	void returnBook(int bid, int sno)
	{
		fstream f;
		BookNode B;
		int k = searchBook(bid);
		if (k == 0) {
			cout << "Invalid Book ID given.\n";
		} else {
			f.open(filename, ios::in | ios::out | ios::binary);
			f.seekg((k - 1)*sizeof(BookNode), ios::beg);
			f.read((char*)&B, sizeof(BookNode));
			B.toggleCopy(sno);
			f.clear();
			f.seekp((k - 1)*sizeof(BookNode), ios::beg);
			f.write((char*)&B, sizeof(BookNode));
			f.close();
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
	static void init(int set_value)
	{
		Member::count = set_value;
	}
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
public:
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
	friend class StudentListFile;
};

class FacultyMember: public Member {
public:
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
	friend class FacultyListFile;
};

class StudentListFile {
	char filename[31];
public:
	StudentListFile(const char* fn = "")
	{
		strcpy(filename, fn);
		fstream f(filename, ios::app | ios::binary);
		f.close();
	}
	int returnMaxID()
	{
		fstream f;
		StudentMember S;
		int res = 0;
		f.open(filename, ios::in | ios::binary);
		while (!f.eof()) {
			f.read((char*)&S, sizeof(StudentMember));
			res = max(res, S.memberid);
		}
		f.close();
		return res;
	}
	int searchStudent(int sid)
	{
		fstream f;
		f.open(filename, ios::in | ios::binary);
		StudentMember S;
		int k = 0;
		while (!f.eof()) {
			f.read((char*)&S, sizeof(StudentMember));
			++k;
			if (S.memberid == sid) {
				f.close();
				return k;
			}
		}
		f.close();
		return 0;
	}
	void addStudent()
	{
		fstream f;
		StudentMember S;
		S.getinput();
		f.open(filename, ios::app | ios::binary);
		f.write((char*)&S, sizeof(StudentMember));
		f.close();
	}
	bool canIssueStudent(int sid)
	{
		fstream f;
		StudentMember S;
		int k = searchStudent(sid);
		if (k == 0) {
			cout << "Invalid Student Member ID entered.\n";
			return false;
		} else {
			f.open(filename, ios::in | ios::binary);
			f.seekg((k - 1)*sizeof(StudentMember), ios::beg);
			f.read((char*)&S, sizeof(StudentMember));
			f.close();
			return S.canIssue();
		}
	}
	void IssueStudent(int sid)
	{
		fstream f;
		StudentMember S;
		int k = searchStudent(sid);
		if (k == 0) {
			cout << "Invalid Student Member ID entered.\n";
		} else {
			f.open(filename, ios::in | ios::out | ios::binary);
			f.seekg((k - 1)*sizeof(StudentMember), ios::beg);
			f.read((char*)&S, sizeof(StudentMember));
			S.Issue();
			f.clear();
			f.seekp((k - 1)*sizeof(StudentMember), ios::beg);
			f.write((char*)&S, sizeof(StudentMember));
			f.close();
		}
	}
	void ReturnStudent(int sid)
	{
		fstream f;
		StudentMember S;
		int k = searchStudent(sid);
		if (k == 0) {
			cout << "Invalid Student Member ID entered.\n";
		} else {
			f.open(filename, ios::in | ios::out | ios::binary);
			f.seekg((k - 1)*sizeof(StudentMember), ios::beg);
			f.read((char*)&S, sizeof(StudentMember));
			S.Return();
			f.clear();
			f.seekp((k - 1)*sizeof(StudentMember), ios::beg);
			f.write((char*)&S, sizeof(StudentMember));
			f.close();
		}
	}
	void displayStudentName(int sid)
	{
		fstream f;
		StudentMember S;
		int k = searchStudent(sid);
		if (k == 0) {
			cout << "Invalid Student Member ID entered.\n";
		} else {
			f.open(filename, ios::in | ios::binary);
			f.seekg((k - 1)*sizeof(StudentMember), ios::beg);
			f.read((char*)&S, sizeof(StudentMember));
			f.close();
			S.displayname();
		}
	}
};

class FacultyListFile {
	char filename[31];
public:
	FacultyListFile(const char* fn = "")
	{
		strcpy(filename, fn);
		fstream f(filename, ios::app | ios::binary);
		f.close();
	}
	int returnMaxID()
	{
		fstream f;
		FacultyMember S;
		int res = 0;
		f.open(filename, ios::in | ios::binary);
		while (!f.eof()) {
			f.read((char*)&S, sizeof(FacultyMember));
			res = max(res, S.memberid);
		}
		f.close();
		return res;
	}
	int searchFaculty(int fid)
	{
		fstream f;
		f.open(filename, ios::in | ios::binary);
		FacultyMember S;
		int k = 0;
		while (!f.eof()) {
			f.read((char*)&S, sizeof(FacultyMember));
			++k;
			if (S.memberid == fid) {
				f.close();
				return k;
			}
		}
		f.close();
		return 0;
	}
	void addFaculty()
	{
		fstream f;
		FacultyMember S;
		S.getinput();
		f.open(filename, ios::app | ios::binary);
		f.write((char*)&S, sizeof(FacultyMember));
		f.close();
	}
	bool canIssueFaculty(int fid)
	{
		fstream f;
		FacultyMember S;
		int k = searchFaculty(fid);
		if (k == 0) {
			cout << "Invalid Faculty Member ID entered.\n";
			return false;
		} else {
			f.open(filename, ios::in | ios::binary);
			f.seekg((k - 1)*sizeof(FacultyMember), ios::beg);
			f.read((char*)&S, sizeof(FacultyMember));
			f.close();
			return S.canIssue();
		}
	}
	void IssueFaculty(int fid)
	{
		fstream f;
		FacultyMember S;
		int k = searchFaculty(fid);
		if (k == 0) {
			cout << "Invalid Faculty Member ID entered.\n";
		} else {
			f.open(filename, ios::in | ios::out | ios::binary);
			f.seekg((k - 1)*sizeof(FacultyMember), ios::beg);
			f.read((char*)&S, sizeof(FacultyMember));
			S.Issue();
			f.clear();
			f.seekp((k - 1)*sizeof(FacultyMember), ios::beg);
			f.write((char*)&S, sizeof(FacultyMember));
			f.close();
		}
	}
	void ReturnFaculty(int fid)
	{
		fstream f;
		FacultyMember S;
		int k = searchFaculty(fid);
		if (k == 0) {
			cout << "Invalid Faculty Member ID entered.\n";
		} else {
			f.open(filename, ios::in | ios::out | ios::binary);
			f.seekg((k - 1)*sizeof(FacultyMember), ios::beg);
			f.read((char*)&S, sizeof(FacultyMember));
			S.Return();
			f.clear();
			f.seekp((k - 1)*sizeof(FacultyMember), ios::beg);
			f.write((char*)&S, sizeof(FacultyMember));
			f.close();
		}
	}
	void displayFacultyName(int fid)
	{
		fstream f;
		FacultyMember S;
		int k = searchFaculty(fid);
		if (k == 0) {
			cout << "Invalid Faculty Member ID entered.\n";
		} else {
			f.open(filename, ios::in | ios::binary);
			f.seekg((k - 1)*sizeof(FacultyMember), ios::beg);
			f.read((char*)&S, sizeof(FacultyMember));
			f.close();
			S.displayname();
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
public:
	Transactions()
	{
		dd = mm = yy = -1;
		memid = bkid = sno = -1;
		returned = 0;
	}
	bool getinputIssue(BookListFile headb, StudentListFile heads, FacultyListFile headf, int willissue = 1)
	{
		cout << "Enter your Member ID:\n";
		cin >> memid;
		if (heads.searchStudent(memid) != 0) {
			type = 's';
		} else if (headf.searchFaculty(memid) != 0) {
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
				if (heads.canIssueStudent(memid)) {
					int serial = headb.issueBook(bkid);
					if (serial > 0) {
						sno = serial;
						heads.IssueStudent(memid);
					} else {
						return false;
					}
				} else {
					cout << "You cannot issue anymore books.\n";
					return false;
				}
			} else {
				if (headf.canIssueFaculty(memid)) {
					int serial = headb.issueBook(bkid);
					if (serial > 0) {
						sno = serial;
						headf.IssueFaculty(memid);
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
	void returnIssue(BookListFile headb, StudentListFile heads, FacultyListFile headf)
	{
		if (type == 's') {
			heads.ReturnStudent(memid);
		} else {
			headf.ReturnFaculty(memid);
		}
		headb.returnBook(bkid, sno);
		returned = 1;
		cout << "Book Returned successfully.\n";
	}
	bool compare(Transactions returning)
	{
		if (returned == 0 && memid == returning.memid && bkid == returning.bkid && sno == returning.sno)
			return true;
		return false;
	}
	void issueReceipt(BookListFile headb, StudentListFile heads, FacultyListFile headf)
	{
		cout << "Issue Successful!.\n";
		cout << "Receipt:\n";
		cout << "Date of Issue: " << dd << " / " << mm << " / " << yy << "\n";
		if (type == 's') {
			heads.displayStudentName(memid);
		} else {
			headf.displayFacultyName(memid);
		}
		cout << "Book ID: " << bkid << "\n";
		cout << "Serial Number: " << sno << "\n";
	}
	friend class TransactionsListFile;
};

class TransactionsListFile {
	char filename[31];
public:
	TransactionsListFile(const char* fn = "")
	{
		strcpy(filename, fn);
		fstream f(filename, ios::app | ios::binary);
		f.close();
	}
	int searchTransaction(Transactions another)
	{
		fstream f;
		Transactions T;
		int k = 0;
		f.open(filename, ios::in | ios::binary);
		while (!f.eof()) {
			f.read((char*)&T, sizeof(Transactions));
			++k;
			if (T.compare(another)) {
				f.close();
				return k;
			}
		}
		f.close();
		return 0;
	}
	void addTransaction(BookListFile headb, StudentListFile heads, FacultyListFile headf)
	{
		fstream f;
		Transactions newT;
		if (newT.getinputIssue(headb, heads, headf)) {
			f.open(filename, ios::app | ios::binary);
			f.write((char*)&newT, sizeof(Transactions));
			f.close();
			newT.issueReceipt(headb, heads, headf);
		} else {
			cout << "Given request couldn\'t be issued.\n";
		}
	}
	void returnTransaction(BookListFile headb, StudentListFile heads, FacultyListFile headf)
	{
		fstream f;
		Transactions temp;
		temp.getinputIssue(headb, heads, headf, 0);
		int k = searchTransaction(temp);
		if (k == 0) {
			cout << "Enter valid details. No issue found with given details.\n";
		} else {
			f.open(filename, ios::in | ios::out | ios::binary);
			f.seekg((k - 1)*sizeof(Transactions), ios::beg);
			Transactions temp2;
			f.read((char*)&temp2, sizeof(Transactions));
			temp2.returnIssue(headb, heads, headf);
			f.clear();
			f.seekp((k - 1)*sizeof(Transactions), ios::beg);
			f.write((char*)&temp2, sizeof(Transactions));
			f.close();
		}
	}
};


class Operations {
	BookListFile B;
	StudentListFile S;
	FacultyListFile F;
	TransactionsListFile T;
public:
	Operations(const char* fnb = "", const char* fns = "", const char* fnf = "", const char* fnt = ""): B(fnb), S(fns), F(fnf), T(fnt)
	{
		Member::init(max(S.returnMaxID(), F.returnMaxID()));
	}
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
				T.addTransaction(B, S, F);
				break;
			case 4:
				T.returnTransaction(B, S, F);
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


int var = 20;
signed main() {

	int var = var;
	printf("%d", var);
	cout << INT_MAX + 1 << "\n";

	return 0;
}
