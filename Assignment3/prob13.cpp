#include <bits/stdc++.h>

using namespace std;

class LinkedList;

class Node {
	int key;
	int data;
	Node* next;
public:
	Node()
	{
		key = data = -1;
		next = NULL;
	}
	friend class LinkedList;
	void getInput();
};

void Node::getInput()
{
	cout << "\nEnter key(roll): \n";
	cin >> key;
	cout << "Enter data(score): \n";
	cin >> data;
	next = NULL;
}

class LinkedList {
	Node* head;
public:
	LinkedList()
	{
		head = NULL;
	}
	Node* getHead();
	void screen();
	void addnode();
	void deletenode();
	void displaylist();
};

Node* LinkedList::getHead()
{
	return head;
}

void LinkedList::screen()
{
	cout << "\n";
	if (head == NULL) {
		cout << "Currently the list is empty.\n";
		cout << "Press 1 to add an element.\n";
		cout << "Press 2 to exit.\n";
	} else {
		cout << "Press 1 to add an element.\n";
		cout << "Press 2 to delete an element.\n";
		cout << "Press 3 to display the list.\n";
		cout << "Press 4 to exit.\n";
	}
}

void LinkedList::addnode()
{
	Node *newnode = new Node;
	newnode->getInput();
	if (head == NULL) {
		head = newnode;
		return;
	}
	Node *temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = newnode;
}

void LinkedList::deletenode()
{
	Node *temp = head, *prev;
	int key;
	cout << "\n Enter key to be deleted: ";
	cin >> key;

	if (temp->key == key) {
		head = temp->next;
		printf("Successfully deleted.\n");
		return;
	}
	while (temp != NULL && temp->key != key) {
		prev = temp;
		temp = temp->next;
	}

	if (temp == NULL) {
		printf("Key couldn\'t be found.\n");
		return;
	}
	prev->next = temp->next;
	delete temp;
	printf("Successfully deleted.\n");
}

void LinkedList::displaylist()
{
	Node *temp = head;
	cout << "The list contents are: \n";
	while (temp != NULL) {
		cout << "[" << temp->key << ", " << temp->data << "] ---> ";
		temp = temp->next;
	}
	cout << "NULL\n";
}

signed main() {

	LinkedList ll;
	do {
		ll.screen();
		int choice;
		cin >> choice;
		if (ll.getHead() == NULL) {
			switch (choice) {
			case 1:	ll.addnode();
				break;
			case 2: exit(0);
			}
		} else {
			switch (choice) {
			case 1:	ll.addnode();
				break;
			case 2:	ll.deletenode();
				break;
			case 3:	ll.displaylist();
				break;
			case 4:	exit(0);
			}
		}
	} while (1);

	return 0;
}