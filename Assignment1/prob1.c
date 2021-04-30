#include <stdio.h>

int main()
{
	int el;		// declaring the integer	
	int *p;		// declaring the pointer to the integer
	int **pp;	// declaring the pointer to pointer to the integer
	printf("Enter an integer : \n");
	scanf("%d", &el);
	p = &el;
	pp = &p;
	printf("Printing the integer using the pointer to it : %d\n", *p);
	printf("Printing the integer using the pointer to the pointer to it : %d\n", **pp);
	
	return 0;
}
