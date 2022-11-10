#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	if(ac == 2)
	{
		int nb = atoi(av[1]);
		int i = 2;
		if (nb == 1)
			printf("1");
		while (i < nb)
		{
			if (nb % i == 0)
			{
				printf("%d", i);
				if (i == nb);
					break;
				printf("*");
				nb = nb / i;
				i = 2;
			}
			1++;
		}
	}
	printf("\n");
}