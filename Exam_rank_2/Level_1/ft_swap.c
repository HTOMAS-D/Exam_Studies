#include <stdio.h>

void ft_swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int main()
{
	int a = 3;
	int b = 7;
	printf("a: %d || b: %d\n\n", a, b);
	ft_swap(&a, &b);
	printf("a: %d || b: %d", a, b);
}