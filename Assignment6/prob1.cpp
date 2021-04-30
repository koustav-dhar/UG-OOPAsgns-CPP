#include <iostream>
#include <fstream>
#include <ctime>
#include <string.h>

#define max_copies 25	// no of max copies of a single book

using namespace std;

// defining a class for book details
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

// defining a class for copies of a book
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

// defining a class which contains bookdetails as well as
// an array of its copies with their availability status
class BookNode: public Book {
protected:
	int noOfCopies;
	Copies copyList[max_copies];
public:
	BookNode()
	{
		noOfCopies = 0;
	}
	bool searchCopy(int sno)	// function to check if passed serial no is valid
	{
		return (noOfCopies >= sno);
	}
	void addCopy()	// function to add a copy of the book to the library, if maxm limit isn't reached
	{
		if (noOfCopies < max_copies) {
			Copies temp(noOfCopies + 1, 1);
			copyList[noOfCopies] = temp;
			++noOfCopies;
		} else {
			cout << "Couldn\'t add more copies.\n";
		}
	}
	int getFirstAvailable()	// function which returns the smallest serial no of the book copy that is available at the moment
	{
		for (int i = 0; i < noOfCopies; ++i) {
			if (copyList[i].available == 1) {
				return i + 1;
			}
		}
		return -1;
	}
	void toggleCopy(int sno)	// function to change the availability status of a particular copy
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

// defining a class to handle the book file
class BookListFile {
	char filename[31];
public:
	BookListFile(const char* s = "")
	{
		strcpy(filename, s);
		fstream f(filename, ios::app | ios::binary);
		f.close();
	}
	int searchBook(int bid)	// function to search for a book by its bookid and return the index of it in the file, if present
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
	void addBook()	// function to add a book to the library, if present, then add a copy
	{
		fstream f;
		BookNode B;
		B.getid();
		int k = searchBook(B.bookid);
		if (k != 0) {	// book with same id exists, hence add a copy of that book
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
		} else {	// first copy of a new book gets added
			B.getdetails();
			B.addCopy();
			f.open(filename, ios::app | ios::binary);
			f.write((char*)&B, sizeof(BookNode));
			f.close();
			cout << "Added the book to our shelf successfully.\n";
		}
	}
	int issueBook(int bid)	// will return the serial number which will be issued, -1 if no more books are available
	{
		fstream f;
		BookNode B;
		int k = searchBook(bid);
		if (k == 0) {	// if book id couldn't be found
			cout << "Invalid Book ID given.\n";
			return 0;
		} else {
			f.open(filename, ios::in | ios::out | ios::binary);
			f.seekg((k - 1)*sizeof(BookNode), ios::beg);
			f.read((char*)&B, sizeof(BookNode));
			int sno = B.getFirstAvailable();	// get an available serial no
			if (sno > 0) {	// if a copy is available
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
	void returnBook(int bid, int sno)	// function to return a book, i.e. change it's availability status to available
	{
		fstream f;
		BookNode B;
		int k = searchBook(bid);
		if (k == 0) {	// if invalid bookid is passed
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

// defining a class for members of the library
class Member {
protected:
	static int count;	// variable to generate unique memberid for new members
	int memberid;
	char name[31];
	char email[31];
	char address[101];
	int cardsLeft;
public:
	static void init(int set_value)	// initialiser function for count
	{
		Member::count = set_value;
	}
	bool canIssue()	// function to check if the member can issue any more books at the moment
	{
		return (cardsLeft > 0);
	}
	void Issue()	// function to decrease no of cards of a member by 1
	{
		--cardsLeft;
	}
	void Return()	// function to increase no of cards of a member by 1
	{
		++cardsLeft;
	}
};

int Member::count = 0;

// defining a derived class for student members
class StudentMember: public Member {
public:
	void getinput()	// input function for students, memberid & 2 books limit is reported to student
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
	void displayname()	// display data function for students
	{
		cout << "Name: " << name << ".\n";
		cout << "Member Type: Student.\n";
		cout << "Member ID: " << memberid << ".\n";
	}
	friend class StudentListFile;
};

// defining a derived class for faculty members
class FacultyMember: public Member {
public:
	void getinput()	// input function for faculties, memberid & 10 books limit is reported to faculty
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
	void displayname()	// display data function for faculties
	{
		cout << "Name: " << name << ".\n";
		cout << "Member Type: Faculty.\n";
		cout << "Member ID: " << memberid << ".\n";
	}
	friend class FacultyListFile;
};

// defining a class for student members file
class StudentListFile {
	char filename[31];
public:
	StudentListFile(const char* fn = "")
	{
		strcpy(filename, fn);
		fstream f(filename, ios::app | ios::binary);
		f.close();
	}
	int returnMaxID()	// returns highest member id in the student file
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
	int searchStudent(int sid)	// searches a student member in the student member file, returns its index if present
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
	void addStudent()	// adds a student member to the file
	{
		fstream f;
		StudentMember S;
		S.getinput();
		f.open(filename, ios::app | ios::binary);
		f.write((char*)&S, sizeof(StudentMember));
		f.close();
	}
	bool canIssueStudent(int sid)	// checks if a certain student can issue a book at the moment
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
	void IssueStudent(int sid)	// performs the issue operation for a student member, and updates his card status
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
	void ReturnStudent(int sid)	// perform the return operation for a student member, and updates his card status
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
	void displayStudentName(int sid)	// displays student details for a certain student member
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

// defining a class for faculty member file
class FacultyListFile {
	char filename[31];
public:
	FacultyListFile(const char* fn = "")
	{
		strcpy(filename, fn);
		fstream f(filename, ios::app | ios::binary);
		f.close();
	}
	int returnMaxID()	// returns highest member id in the faculty file
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
	int searchFaculty(int fid)	// searches a faculty member in the faculty member file, returns its index if present
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
	void addFaculty()	// adds a faculty member to the file
	{
		fstream f;
		FacultyMember S;
		S.getinput();
		f.open(filename, ios::app | ios::binary);
		f.write((char*)&S, sizeof(FacultyMember));
		f.close();
	}
	bool canIssueFaculty(int fid)	// checks if a certain faculty can issue a book at the moment
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
	void IssueFaculty(int fid)	// perform the issue operation for a faculty member, and updates his card status
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
	void ReturnFaculty(int fid)	// perform the return operation for a faculty member, and updates his card status
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
	void displayFacultyName(int fid)	// displays faculty details for a certain faculty member
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

// defining a class for transactions
class Transactions {
protected:
	int dd, mm, yy;
	int memid;
	char type;
	int bkid;
	int sno;
public:
	Transactions()
	{
		dd = mm = yy = -1;
		memid = bkid = sno = -1;
	}
	int get_memid()const 	// accessor function to get memberid
	{
		return memid;
	}
	int get_bkid()const 	// accessor function to get bookid
	{
		return bkid;
	}
	int get_sno()const 		// accessor function to get serialno
	{
		return sno;
	}
	char get_type()const 	// accessor function to get membertype
	{
		return type;
	}
};

class Issue;

// defining a derived class for book returning transactions
class Return: public Transactions {
public:
	void getinputReturn(BookListFile headb, StudentListFile heads, FacultyListFile headf)	// takes input for a return query and checks for its validity
	{
		cout << "What is your status?\n";
		cout << "Press 1 if you are a faculty.\n";
		cout << "Press 2 if you are a student.\n";
		int c;
		cin >> c;
		if (c == 1) {
			type = 'f';
		} else if (c == 2) {
			type = 's';
		} else {
			cout << "Invalid Choice.\n";
			return;
		}
		cout << "Enter your Member ID:\n";
		cin >> memid;
		// checks if member id is valid
		if (type == 's' && heads.searchStudent(memid) != 0) {
			type = 's';
		} else if (type == 'f' && headf.searchFaculty(memid) != 0) {
			type = 'f';
		} else {
			cout << "This Member ID doesn\'t exist. Please enter valid ID.\n";
		}
		time_t now = time(0);
		tm *ltm = localtime(&now);
		dd = ltm->tm_mday;
		mm = ltm->tm_mon;
		yy = ltm->tm_year;
		cout << "Enter Book ID: \n";
		cin >> bkid;
		cout << "Enter Serial Number: \n";
		cin >> sno;
	}
	void returnIssue(BookListFile headb, StudentListFile heads, FacultyListFile headf, Issue &i);
};

// defining a class for book issuing transactions
class Issue: public Transactions {
	int returned;
public:
	Issue()
	{
		returned = 0;
	}
	void toggleStatus()	// function to change the returned status of the issue
	{
		returned ^= 1;
	}
	bool getinputIssue(BookListFile headb, StudentListFile heads, FacultyListFile headf)	// takes input for a issue query and returns true if the issue is a valid one, else false
	{
		cout << "What is your status?\n";
		cout << "Press 1 if you are a faculty.\n";
		cout << "Press 2 if you are a student.\n";
		int c;
		cin >> c;
		if (c == 1) {
			type = 'f';
		} else if (c == 2) {
			type = 's';
		} else {
			cout << "Invalid Choice.\n";
			return false;
		}
		cout << "Enter your Member ID:\n";
		cin >> memid;
		// checks if member id is valid
		if (type == 's' && heads.searchStudent(memid) != 0) {
			type = 's';
		} else if (type == 'f' && headf.searchFaculty(memid) != 0) {
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
		// checks if the respective member can issue, if can, perform issue operations on them
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
	}
	bool compare(Return returning)	// comparator function to match a return with the issue
	{
		if (returned == 0 && memid == returning.get_memid() && bkid == returning.get_bkid() && sno == returning.get_sno())
			return true;
		return false;
	}
	void issueReceipt(BookListFile headb, StudentListFile heads, FacultyListFile headf)	// display function to generate a receipt after a successful issue
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

void Return::returnIssue(BookListFile headb, StudentListFile heads, FacultyListFile headf, Issue &i)	// function to perform respective return operations on member and book files
{
	if (i.get_type() == 's') {
		heads.ReturnStudent(i.get_memid());
	} else {
		headf.ReturnFaculty(i.get_memid());
	}
	headb.returnBook(i.get_bkid(), i.get_sno());
	i.toggleStatus();
	cout << "Book Returned successfully.\n";
}

// defining a class for transaction records file
class TransactionsListFile {
	char filename[31];
public:
	TransactionsListFile(const char* fn = "")
	{
		strcpy(filename, fn);
		fstream f(filename, ios::app | ios::binary);
		f.close();
	}
	int searchTransaction(Return another)	// searches for a matching issue record for passed return query, returns index of record if found
	{
		fstream f;
		Issue T;
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
	void addTransaction(BookListFile headb, StudentListFile heads, FacultyListFile headf)	// performs an issue transaction
	{
		fstream f;
		Issue newT;
		if (newT.getinputIssue(headb, heads, headf)) {
			f.open(filename, ios::app | ios::binary);
			f.write((char*)&newT, sizeof(Transactions));
			f.close();
			newT.issueReceipt(headb, heads, headf);
		} else {
			cout << "Given request couldn\'t be issued.\n";
		}
	}
	void returnTransaction(BookListFile headb, StudentListFile heads, FacultyListFile headf)	// performs a return transaction
	{
		fstream f;
		Return temp;
		temp.getinputReturn(headb, heads, headf);
		int k = searchTransaction(temp);
		if (k == 0) {
			cout << "Enter valid details. No issue found with given details.\n";
		} else {
			f.open(filename, ios::in | ios::out | ios::binary);
			f.seekg((k - 1)*sizeof(Transactions), ios::beg);
			Issue temp2;
			f.read((char*)&temp2, sizeof(Transactions));
			Return temp3;
			temp3.returnIssue(headb, heads, headf, temp2);
			f.clear();
			f.seekp((k - 1)*sizeof(Transactions), ios::beg);
			f.write((char*)&temp2, sizeof(Transactions));
			f.close();
		}
	}
};

// defining a batch class for a library system
class Operations {
	BookListFile B;
	StudentListFile S;
	FacultyListFile F;
	TransactionsListFile T;
public:
	Operations(const char* fnb = "", const char* fns = "", const char* fnf = "", const char* fnt = ""): B(fnb), S(fns), F(fnf), T(fnt)
	{
		Member::init(max(S.returnMaxID(), F.returnMaxID()));	// initialising the count with max member id generated till now, to avoid duplicate id generation
	}
	int screen()	// menu
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

signed main() {

	Operations O("books.dat", "students.dat", "faculties.dat", "transactions.dat");
	O.operate();

	return 0;
}