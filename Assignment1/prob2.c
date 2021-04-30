#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n;
	printf("Enter size of array : \n");
	scanf("%d", &n);
	int* arr;
	arr = (int*)malloc(n * sizeof(int));
	if (arr == NULL){
		printf("ERROR. Failed to dynamically allocate memory.\n");
		exit(0);
	}
	else{
		printf("Enter %d elements of the array : \n", n);
		for(int i = 0; i < n; ++i){
			scanf("%d", arr + i);
		}
		printf("The array elements are : \n");
		for(int i = 0; i < n; ++i){
			printf("%d ", *(arr + i));
		}
		printf("\n");
	}
	free(arr);
	return 0;
}
