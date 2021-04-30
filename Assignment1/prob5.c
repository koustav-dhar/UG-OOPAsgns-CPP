#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100

void allocate(int **age, char ***names, int n)
{
	*names = malloc(n * sizeof(char*));
	for(int i = 0; i < n; ++i){
		(*names)[i] = (char*)malloc(MAXN * sizeof(char));
	}
	*age = (int*)malloc(n * sizeof(int));
}

void input(int *age, char **names, int n)
{
	printf("Enter age and name of the people respectively : \n");
	for(int i = 0; i < n; ++i){
		scanf("%d", &age[i]);
		scanf("%[^\n]s", names[i]);
	}
}


void Sort(int *age, char **names, int n)
{
	for(int i = 0; i < n; ++i){
		for(int j = i + 1; j < n; ++j){
			if (age[i] > age[j]){
				int temp = age[j];
				age[j] = age[i];
				age[i] = temp;
				char temps[MAXN];
				strcpy(temps, names[j]);
				strcpy(names[j], names[i]);
				strcpy(names[i], temps);
			}
		}
	}
}

void output(int *age, char **names, int n)
{
	printf("The list of people in sorted order of age is : \n");
	for(int i = 0; i < n; ++i){
		printf("%s - %d\n", names[i], age[i]);
		free(names[i]);
	}
	free(age);
}

int main()
{
	int n;
	printf("Enter the number of people : \n");
	scanf("%d", &n);
	char **names;
	int *age;
	allocate(&age, &names, n);
	input(age, names, n);
	Sort(age, names, n);
	output(age, names, n);
	/*for (int i = 0; i < n; ++i) {
		free(names[i]);
	}
	free(age);*/
	
	return 0;
}
