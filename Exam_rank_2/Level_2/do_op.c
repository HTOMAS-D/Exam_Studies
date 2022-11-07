#include <stdio.h>
#include <stdlib.h>

void do_stuff(int a, int b, char c)
{
	if (c == '+')
		printf("%d", a + b);
	else if (c == '-')
		printf("%d", a - b);
	else if (c == '*')
		printf("%d", a * b);
	else if (c == '/')
		printf("%d", a / b);
	else if (c == '%')
		printf("%d", a % b);
}

int main(int ac, char **av)
{
	if (ac == 4)
	{	
		int a = atoi(av[1]);
		int b = atoi(av[3]);
		do_stuff(a, b, av[2][0]);
	}
	printf("\n");
}