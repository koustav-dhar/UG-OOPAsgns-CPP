#include <stdio.h>

int *f(int* pos)
{
	return pos;
}

int k = 1;

int main()
{
	int a = 5;
	*f(&a) = 3;
	printf("%d\n", a);
	
	int k = 2;
	{
		int k = 3;
		printf("%d")
	}
	
	return 0;
}
