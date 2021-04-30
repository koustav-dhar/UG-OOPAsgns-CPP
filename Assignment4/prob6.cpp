#include <iostream>
#include <string.h>

using namespace std;

class Subject;
class SubjectListNode;
class SubjectList;
class Student;
class StudentList;

class Student {
	int roll;
	char name[30];
	long long int phone_no;
	int no_of_subs;
	Subject* subs;
	Student* next;
public:
	Student()
	{
		roll = -1;
		strcpy(name, "");
		phone_no = 0;
		subs = NULL;
		next = NULL;
	}
	void get_input(SubjectList& subject_list);
	void add_student_to_the_subjects(SubjectList& subject_list);
	void display_details();
	friend class StudentList;
	friend class SubjectListNode;
};

class Subject {
	int s_code;
	char s_name[30];
public:
	Subject()
	{
		s_code = -1;
		strcpy(s_name, "");
	}
	void get_input()
	{
		cout << "Enter subject code:\n";
		cin >> s_code;
		cout << "Enter subject name:\n";
		scanf(" %[^\n]s", s_name);
	}
	friend class SubjectList;
	friend class Student;
};

class SubjectListNode {
	Subject S;
	Student* head;
	SubjectListNode* next;
public:
	SubjectListNode()
	{
		head = NULL;
		next = NULL;
	}
	void get_input()
	{
		S.get_input();
		head = NULL;
		next = NULL;
	}
	void add_student(Student newS)
	{
		Student* temp = head;
		Student* newStu = new Student;
		newStu->roll = newS.roll;
		strcpy(newStu->name, newS.name);
		newStu->phone_no = newS.phone_no;
		newStu->no_of_subs = newS.no_of_subs;
		newStu->subs = newS.subs;
		newStu->next = NULL;
		if (head == NULL) {
			head = newStu;
			return;
		}
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newStu;
	}
	void display_student_list()
	{
		Student* temp = head;
		while (temp != NULL) {
			temp->display_details();
			temp = temp->next;
		}
	}
	friend class SubjectList;
};

class SubjectList {
	SubjectListNode* head;
public:
	SubjectList()
	{
		head = NULL;
	}
	bool find_subject(int code)
	{
		SubjectListNode* temp = head;
		while (temp != NULL) {
			if (temp->S.s_code == code) {
				return true;
			}
			temp = temp->next;
		}
		return false;
	}
	void add_subject()
	{
		SubjectListNode* newNode = new SubjectListNode;
		newNode->get_input();
		if (head == NULL) {
			head = newNode;
			return;
		}
		if (find_subject(newNode->S.s_code)) {
			cout << "Another subject with this subject code already exists. Please enter correct subject code.\n";
			return;
		}
		SubjectListNode* temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newNode;
	}
	void display_subject()
	{
		int code;
		cout << "Enter subject code for the subject you want to view:\n";
		cin >> code;
		if (find_subject(code)) {
			SubjectListNode* temp = head;
			while (temp != NULL) {
				if (temp->S.s_code == code) {
					cout << "\nSubject: " << temp->S.s_name;
					cout << "\nSubject Code: " << temp->S.s_code;
					cout << "\nStudents enrolled in this subject:\n";
					temp->display_student_list();
					return;
				}
				temp = temp->next;
			}
		} else {
			cout << "Subject with given subject code couldn\'t be found.\n";
			return;
		}
	}
	int display_all_subjects(int todisplay = 1)
	{
		int iter = 1;
		cout << "Subjects available: \n";
		SubjectListNode* temp = head;
		while (temp != NULL) {
			if (todisplay)
				cout << iter << ". " << temp->S.s_name << " [" << temp->S.s_code << "].\n";
			temp = temp->next;
			++iter;
		}
		return iter - 1;
	}
	Subject get_sub_details(int option)
	{
		int iter = 1;
		SubjectListNode* temp = head;
		Subject temp_sub;
		while (temp != NULL) {
			if (iter == option) {
				temp_sub = temp->S;
				return temp_sub;
			}
			temp = temp->next;
			++iter;
		}
		return temp_sub;
	}
	void add_student_to_subject(int code, Student newS)
	{
		SubjectListNode* temp = head;
		while (temp != NULL) {
			if (temp->S.s_code == code) {
				temp->add_student(newS);
				return;
			}
			temp = temp->next;
		}
	}
};

void Student::get_input(SubjectList& subject_list)
{
	cout << "Enter roll number:\n";
	cin >> roll;
	cout << "Enter name:\n";
	scanf(" %[^\n]s", name);
	cout << "Enter phone number:\n";
	cin >> phone_no;
	int tot = subject_list.display_all_subjects();
	cout << "Enter number of subjects you want to choose:\n";
	cin >> no_of_subs;
	subs = new Subject[no_of_subs];
	int sub_temp[tot + 1];
	for (int i = 0; i <= tot; ++i)
		sub_temp[i] = 0;
	int sub;
	for (int i = 0; i < no_of_subs; ++i) {
		cout << "Enter your option for subject " << i + 1 << ": \n";
		cin >> sub;
		if (sub_temp[sub] != 0) {
			cout << "You\'ve already opted for this subject. Please enter another subject.\n";
			--i;
			continue;
		}
		if (sub < 1 || sub > tot) {
			cout << "Please enter a valid option. Choice must lie between 1 and " << no_of_subs << "\n";
			--i;
			continue;
		}
		sub_temp[sub] = 1;
		subs[i] = subject_list.get_sub_details(sub);
	}
	next = NULL;
}
void Student::add_student_to_the_subjects(SubjectList& subject_list)
{
	for (int i = 0; i < no_of_subs; ++i) {
		subject_list.add_student_to_subject(subs[i].s_code, *this);
	}
}
void Student::display_details()
{
	cout << "\nRoll: " << roll;
	cout << "\nName: " << name;
	cout << "\nContact No.: " << phone_no;
	cout << "\nSubjects Enrolled in: ";
	for (int i = 0; i < no_of_subs; ++i) {
		cout << subs[i].s_name;
		if (i != no_of_subs - 1)
			cout << ", ";
		else
			cout << "\n";
	}
}

class StudentList {
	Student* head;
public:
	StudentList()
	{
		head = NULL;
	}
	bool find_student(int sroll)
	{
		Student* temp = head;
		while (temp != NULL) {
			if (temp->roll == sroll) {
				return true;
			}
			temp = temp->next;
		}
		return false;
	}
	void add_student(SubjectList& subject_list)
	{
		Student* newNode = new Student;
		newNode->get_input(subject_list);
		if (find_student(newNode->roll)) {
			cout << "Student with this roll number already exists. Please enter a unique roll number.\n";
			return;
		}
		newNode->add_student_to_the_subjects(subject_list);
		if (head == NULL) {
			head = newNode;
			return;
		}
		Student* temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newNode;
	}
	void display_student_detail()
	{
		cout << "Enter roll number of student: \n";
		int sroll;
		cin >> sroll;
		if (find_student(sroll)) {
			Student* temp = head;
			while (temp != NULL) {
				temp->display_details();
				if (temp->roll == sroll) {
					temp->display_details();
					return;
				}
				temp = temp->next;
			}
		} else {
			cout << "Student with given roll number couldn\'t be found. Please enter a valid roll number.\n";
			return;
		}
	}
};

class Operations {
	StudentList students;
	SubjectList subjects;
public:
	int screen()
	{
		cout << "Select what to do.\n";
		cout << "Press 1 to add a subject.\n";
		cout << "Press 2 to view a subject details.\n";
		cout << "Press 3 to add a student.\n";
		cout << "Press 4 to view a student details.\n";
		cout << "Press 5 to exit.\n";
		int choice;
		cout << "Enter your choice: \n";
		cin >> choice;
		return choice;
	}
	void operate()
	{
		while (1) {
			switch (screen()) {
			case 1:
				subjects.add_subject();
				break;
			case 2:
				subjects.display_subject();
				break;
			case 3:
				students.add_student(subjects);
				break;
			case 4:
				students.display_student_detail();
				break;
			case 5:
				exit(0);
				break;
			default:
				cout << "Enter a valid choice.\n";
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