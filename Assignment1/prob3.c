#include <stdio.h>
#include <stdlib.h>

int main()
{
	int r, c;
	printf("Enter the row size : \n");
	scanf("%d", &r);
	printf("Enter the column size : \n");
	scanf("%d", &c);
	
	printf("Choose how to declare the 2D array : \n");
	printf("Press 1 for declaration using pointer to an array.\n");
	printf("Press 2 for declaration using array of pointers.\n");
	int choice;
	scanf("%d", &choice);
	if (choice == 1){
		int (*arr)[c] = malloc(sizeof(int[r][c]));
		printf("Enter the array elements : \n");
		for(int i = 0; i < r; ++i){
			for(int j = 0; j < c; ++j){
				scanf("%d", &arr[i][j]);
			}
		}
		printf("The array elements are : \n");
		for(int i = 0; i < r; ++i){
			for(int j = 0; j < c; ++j){
				printf("%d ", *(*(arr + i) + j));
			}
			printf("\n");
		}
		free(arr);
	}
	else if (choice == 2){
		int *arr[r];
		for(int i = 0; i < r; ++i){
			arr[i] = (int*)malloc(c * sizeof(int));
		}
		printf("Enter the array elements : \n");
		for(int i = 0; i < r; ++i){
			for(int j = 0; j < c; ++j){
				scanf("%d", (*(arr + i) + j));
			}
		}
		printf("The array elements are : \n");
		for(int i = 0; i < r; ++i){
			for(int j = 0; j < c; ++j){
				printf("%d ", *(*(arr + i) + j));
			}
			printf("\n");
		}
		for (int  i = 0; i < r; ++i){
			free(arr[i]);
		}
	}
	else{
		printf("Invalid Choice.\n");
	}
	
	return 0;
}
