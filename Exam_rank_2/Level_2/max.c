#include <stdio.h>

int max(int *tab, unsigned int len)
{
	int i = 0;
	int temp = tab[i];
	
	while (i < len)
	{
		if (tab[i] > temp)
			temp = tab[i];
		i++;
	}
	return (temp);
}