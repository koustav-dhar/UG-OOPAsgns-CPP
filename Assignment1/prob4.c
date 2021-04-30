#include <stdio.h>
#include <stdlib.h>

#define MAXC 100

void getSize1D (int *n)
{
	printf("Enter no of elements in the 1D array : \n");
	scanf("%d", n);
}

void getSize2D (int *r, int *c)
{
	printf("Enter no of rows and columns of the 2D array respectively : \n");
	scanf("%d%d", r, c);
}

void allocate1D (int *arr, int n)
{
	arr = (int*)malloc(n * sizeof(int));
}

/*int (*allocate2Dpoa (int r, int c))[MAXC]
{
	int (*p)[c] = (int(*)[c])malloc(r * sizeof(int[c]));
	return p;
}*/

int** allocate2Dpoa(int r, int c)
{
	int **p = (int**)malloc(r * c * sizeof(int));
	return p;
}

void allocate2Daop (int *arr[], int r, int c)
{
	for (int i = 0; i < r; ++i) {
		arr[i] = (int*)malloc(c * sizeof(int));
	}
}

void input1D (int *arr, int n)
{
	printf("Enter the array elements : \n");
	for (int i = 0; i < n; ++i) {
		scanf("%d", (arr + i));
	}
}

void input2Dpoa (int (*arr)[MAXC], int r, int c)
{
	printf("Enter the array elements : \n");
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			scanf("%d", (*(arr + i) + j));
		}
	}
}

void input2Daop (int *arr[], int r, int c)
{
	printf("Enter the array elements : \n");
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			scanf("%d", (*(arr + i) + j));
		}
	}
}

void output1D (int *arr, int n)
{
	printf("The array elements are : \n");
	for (int i = 0; i < n; ++i) {
		printf("%d ", *(arr + i));
	}
	printf("\n");
}

void output2Dpoa (int (*arr)[MAXC], int r, int c)
{
	printf("The array elements are : \n");
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			printf("%d ", *(*(arr + i) + j));
		}
		printf("\n");
	}
}

void output2Daop (int *arr[], int r, int c)
{
	printf("The array elements are : \n");
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			printf("%d ", *(*(arr + i) + j));
		}
		printf("\n");
	}
}

int main()
{
	printf("Press 1 for dynamically allocating 1D array.\n");
	printf("Press 2 for dynamically allocating 2D array.\n");
	printf("Enter your choice (1 / 2) : \n");
	int choice;
	scanf("%d", &choice);

	if (choice == 1) {
		int n;
		getSize1D(&n);
		int *arr;
		allocate1D(arr, n);
		input1D(arr, n);
		output1D(arr, n);
	} else if (choice == 2) {
		int r, c;
		getSize2D(&r, &c);
		printf("Choose how to declare the 2D array : \n");
		printf("Press 1 for declaration using pointer to an array.\n");
		printf("Press 2 for declaration using array of pointers.\n");
		int ch;
		scanf("%d", &ch);
		if (ch == 1) {
			int (*arr)[c];
			arr = allocate2Dpoa(r, c);
			input2Dpoa(arr, r, c);
			output2Dpoa(arr, r, c);
			free(arr);
		} else if (ch == 2) {
			int *arr[r];
			allocate2Daop(arr, r, c);
			input2Daop(arr, r, c);
			output2Daop(arr, r, c);
			for (int i = 0; i < r; ++i) {
				free(arr[i]);
			}
		} else {
			printf("Invalid Choice.\n");
		}
	} else {
		printf("Invalid Choice.\n");
	}
	return 0;
}


