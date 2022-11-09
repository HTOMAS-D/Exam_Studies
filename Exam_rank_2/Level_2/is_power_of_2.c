#include <stdio.h>

int is_power_of_2(unsigned int n)
{
	int numb = 1;
	while (numb <= n)
	{
		if (numb == n)
			return (1);
		numb *= 2;
	}
	return 0;
}