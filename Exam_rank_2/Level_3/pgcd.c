#include <stdio.h>
#include <stdlib.h>

unsigned int ft_atoi(char *str)
{
	unsigned int res;
	int i = 0;
	while (str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

int main(int ac, char **av)
{
	if (ac == 3)
	{
		unsigned int a = ft_atoi(av[1]);
		unsigned int b = ft_atoi(av[2]);
		int i;
		if (a > b)
			i = b;
		else
			i = a;
		while (i > 0)
		{
			if (a % i == 0 && b % i == 0)
				printf("%d", i);
			i--;
		}
	}
	write(1, "\n", 1);
}