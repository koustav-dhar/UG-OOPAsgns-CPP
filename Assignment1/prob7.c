#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
	int roll;
	char name[30];
	int score;
	struct node *next;
};

void screen (int type)
{
	printf("\n");
	if (type == 0) {
		printf("Currently the list is empty.\n");
		printf("Press 1 to add an element.\n");
		printf("Press 2 to exit.\n");
	} else {
		printf("Press 1 to add an element.\n");
		printf("Press 2 to delete an element.\n");
		printf("Press 3 to display the list.\n");
		printf("Press 4 to exit.\n");
	}
}

void getInput (struct node **el)
{
	int r, s;
	char n[30];
	printf("\n");
	printf("Enter roll number : \n");
	scanf("%d", &r);
	printf("Enter name : \n");
	scanf(" %[^\n]s", n);
	printf("Enter score : \n");
	scanf("%d", &s);
	(*el)->roll = r;
	strcpy((*el)->name, n);
	(*el)->score = s;
	(*el)->next = NULL;
}

void add (struct node **head, struct node *curr)
{
	struct node *newNode = (struct node*)malloc(sizeof(struct node));
	struct node *temp = *head;
	newNode = curr;
	newNode->next = NULL;
	if (*head == NULL) {
		*head = newNode;
		return;
	}
	while (temp->next != NULL) {
		temp = temp->next;
	}
	
	temp->next = newNode;
}

void delete (struct node **head, int key)
{
	struct node *temp = *head, *prev;
	if (temp->roll == key) {
		*head = temp->next;
		printf("Successfully deleted.\n");
		return;
	}
	while (temp != NULL && temp->roll != key) {
		prev = temp;
		temp = temp->next;
	}
	
	if (temp == NULL) {
		printf("Roll number couldn\'t be found.\n");
		return;
	}
	prev->next = temp->next;
	free(temp);
	printf("Successfully deleted.\n");
}

void display(struct node *head)
{
	struct node *temp = head;
	printf("The list contents are : \n");
	while (temp != NULL) {
		printf("[%d, \'%s\', %d] ---> ", temp->roll, temp->name, temp->score);
		temp = temp->next;
	}
	printf("NULL\n");
}

int main()
{
	struct node *head = NULL;
	int choice;
	do {
		if (head == NULL) {
			screen(0);
			scanf("%d", &choice);
			struct node *curr;
			switch (choice) {
				case 1 :	getInput(&curr);
							add(&head, curr);
							break;
				case 2 : 	choice = 4;
							break;
				default :	printf("Invalid Choice. Exiting...\n");
							choice = 4;
							break; 
			}
		} else {
			screen(1);
			scanf("%d", &choice);
			struct node *curr = (struct node*)malloc(sizeof(struct node));
			int key;
			switch (choice) {
				case 1 : 	getInput(&curr);
							add(&head, curr);
							break;
				case 2 : 	printf("Enter roll number to be deleted : \n");
							scanf("%d", &key);
							delete(&head, key);
							break;
				case 3 :	display(head);
				 			break;
				case 4 :	break;
				default : 	printf("Invalid Choice. Exiting...\n");
							choice = 4;
							break;
			}
		}
	} while (choice != 4);
	return 0;
}
