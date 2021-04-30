#include <bits/stdc++.h>

using namespace std;

class ItemList;

class Item {
	int itemcode;
	char name[30];
	int rate;
	int quantity;
	Item* next;
public:
	Item()
	{
		itemcode = rate = quantity = -1;
		next = NULL;
	}
	friend class ItemList;
	void getInput();
};

void Item::getInput()
{
	cout << "Enter item code: \n";
	cin >> itemcode;
	cout << "Enter item name: \n";
	scanf(" %[^\n]s", name);
	cout << "Enter rate: \n";
	cin >> rate;
	cout << "Enter quantity available: \n";
	cin >> quantity;
	next = NULL;
}

class ItemList {
	Item* head;
public:
	ItemList()
	{
		head = NULL;
	}
	Item* getHead();
	bool search(int code);
	void screen();
	void addItem();
	void updateItem();
	void deleteItem();
	void displayItemDetails();
};

Item* ItemList::getHead()
{
	return head;
}

bool ItemList::search(int code)
{
	Item *temp = head;
	while (temp != NULL) {
		if (temp->itemcode == code) {
			cout << "Found an item with item code " << code << ".\n";
			return true;
		}
		temp = temp->next;
	}
	cout << "Item with item code " << code << " couldn\'t be found.\n";
	return false;
}

void ItemList::screen()
{
	cout << "\n";
	if (head == NULL) {
		cout << "Currently the item list is empty.\n";
		cout << "Press 1 to add an item.\n";
		cout << "Press 2 to exit.\n";
	} else {
		cout << "Press 1 to add an item.\n";
		cout << "Press 2 to delete an item.\n";
		cout << "Press 3 to display details of an item.\n";
		cout << "Press 4 to update an item (update rate / restock / issue).\n";
		cout << "Press 5 to exit.\n";
	}
}

void ItemList::addItem()
{
	Item *newItem = new Item;
	newItem->getInput();
	if (head == NULL) {
		head = newItem;
		return;
	}
	Item *temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = newItem;
}

void ItemList::updateItem()
{
	cout << "What update you want to do?\n";
	cout << "Press 1 to update rate of an item.\n";
	cout << "Press 2 to restock an item.\n";
	cout << "Press 3 to issue some item.\n";
	int choice;
	cin >> choice;
	int code;
	int updrate, delqty;
	switch (choice) {
	case 1:
		cout << "Enter item code of the item whose rate you want to update: \n";
		cin >> code;
		if (search(code)) {
			cout << "Enter new rate: \n";
			cin >> updrate;
			Item* temp = head;
			while (temp != NULL) {
				if (temp->itemcode == code) {
					temp->rate = updrate;
					break;
				}
				temp = temp->next;
			}
		} else {
			cout << "Enter a valid item code.\n";
		}
		break;
	case 2:
		cout << "Enter item code of the item which you want to restock: \n";
		cin >> code;
		if (search(code)) {
			cout << "Enter quantity you\'ll restock: \n";
			cin >> delqty;
			Item* temp = head;
			while (temp != NULL) {
				if (temp->itemcode == code) {
					temp->quantity += delqty;
					cout << "Restock done successfully.\n";
					break;
				}
				temp = temp->next;
			}
		} else {
			cout << "Enter a valid item code.\n";
		}
		break;
	case 3:
		cout << "Enter item code of the item which you want to issue: \n";
		cin >> code;
		if (search(code)) {
			cout << "Enter quantity you want to issue: \n";
			cin >> delqty;
			Item* temp = head;
			while (temp != NULL) {
				if (temp->itemcode == code) {
					if (temp->quantity >= delqty) {
						temp->quantity -= delqty;
						cout << delqty << " items issued.\n";
					} else {
						cout << "Enough items are not available.\n";
					}
					break;
				}
				temp = temp->next;
			}
		} else {
			cout << "Enter a valid item code.\n";
		}
		break;
	default:
		cout << "Invalid Choice.\n";
		break;
	}

}

void ItemList::deleteItem()
{
	Item *temp = head, *prev;
	int itemcode;
	cout << "\n Enter itemcode to be deleted: ";
	cin >> itemcode;

	if (temp->itemcode == itemcode) {
		head = temp->next;
		printf("Successfully deleted.\n");
		return;
	}
	while (temp != NULL && temp->itemcode != itemcode) {
		prev = temp;
		temp = temp->next;
	}

	if (temp == NULL) {
		printf("itemcode couldn\'t be found.\n");
		return;
	}
	prev->next = temp->next;
	delete temp;
	printf("Successfully deleted.\n");
}

void ItemList::displayItemDetails()
{
	cout << "Enter item code whose details you want to see: \n";
	int code;
	cin >> code;
	if (search(code)) {
		Item* temp = head;
		while (temp != NULL) {
			if (temp->itemcode == code) {
				cout << "\nItem Code: " << temp->itemcode << "\n";
				cout << "Item Name: " << temp->name << "\n";
				cout << "Rate: " << temp->rate << "\n";
				cout << "Available Quantity: " << temp->quantity << "\n";
				break;
			}
			temp = temp->next;
		}
	} else {
		cout << "Enter a valid item code.\n";
	}
}

signed main() {

	ItemList ll;
	do {
		ll.screen();
		int choice;
		cin >> choice;
		if (ll.getHead() == NULL) {
			switch (choice) {
			case 1:	ll.addItem();
				break;
			case 2: exit(0);
			}
		} else {
			switch (choice) {
			case 1:	ll.addItem();
				break;
			case 2:	ll.deleteItem();
				break;
			case 3:	ll.displayItemDetails();
				break;
			case 4:	ll.updateItem();
				break;
			case 5:	exit(0);
			}
		}
	} while (1);

	return 0;
}