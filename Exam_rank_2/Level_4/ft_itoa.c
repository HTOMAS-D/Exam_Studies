#include <unistd.h>

int get_size(int nbr)
{
	int i = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		nbr *= -1;
		i++;
	}
	while (nbr > 0)
	{
		i++:
		nbr /= 10;
	}
	return (i);
}

char *ft_itoa(int nbr)
{
	char *str;
	int size = get_size(nbr);
	int i = 0;
	str = (char *) malloc(sizeof(char) * size + 1);
	str[size] == '\0';
	if (nbr < 0)
	(
		str[i] = '-';
		nbr *= -1;
		i++;
	)
	while (nbr > 0)
	{
		str[size - 1] = nbr % 10 + '0';
		nbr = nbr / 10;
		size--;
	}
}