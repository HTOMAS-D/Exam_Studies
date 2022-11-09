#include <unistd.h>
int iter(char *str, char c, int len)
{
	int i = 0;
	while (str[i] && (i < len || len == -1))
	{
		if (str[i++] == c)
			return (1);
	}
	return (0);
}

int main(int ac, char **av)
{
	int i = 0;
	if (ac == 3)
	{
		while (ac[1][i])
		{
			if (!iter(av[1], av[1][i], i) && iter(av[2], av[1][i], -1))
				write(1, &str[i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
}