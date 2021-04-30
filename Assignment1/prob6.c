#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100

struct ppl
{
	int age;
	char *name;
};

void allocate(struct ppl **people, int n)
{
	*people = (struct ppl*)malloc(n * sizeof(struct ppl));	
	for(int i = 0; i < n; ++i){
		(*people)[i].name = (char*)malloc(MAXN * sizeof(char));
	}
}

void input(struct ppl *people, int n)
{
	printf("Enter age and name of the people respectively : \n");
	for(int i = 0; i < n; ++i){
		scanf("%d", &people[i].age);
		scanf("%[^\n]s", people[i].name);
	}
}

void Sort(struct ppl *people, int n)
{
	char *temps;
	temps = (char*)malloc(MAXN * sizeof(char));
	for(int i = 0; i < n; ++i){
		for(int j = i + 1; j < n; ++j){
			if (people[i].age > people[j].age){
				int temp = people[j].age;
				people[j].age = people[i].age;
				people[i].age = temp;
				strcpy(temps, people[j].name);
				strcpy(people[j].name, people[i].name);
				strcpy(people[i].name, temps);
			}
		}
	}
	free(temps);
}

void output(struct ppl *people, int n)
{
	printf("The list of people in sorted order of age is : \n");
	for(int i = 0; i < n; ++i){
		printf("%s - %d\n", people[i].name, people[i].age);
	}
}

int main()
{
	int n;
	printf("Enter the number of people : \n");
	scanf("%d", &n);
	struct ppl *people;
	allocate(&people, n);
	input(people, n);
	Sort(people, n);
	output(people, n);
	for(int i = 0; i < n; ++i) {
		free(people[i].name);
		people[i].name = NULL;
	}
	free(people);
}
