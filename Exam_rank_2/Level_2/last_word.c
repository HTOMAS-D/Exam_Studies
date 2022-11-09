#include <unistd.h>
#include <stdio.h>

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

void do_stuff(char *str)
{
	int i = ft_strlen(str) - 1;
	while(str[i] == '\t' || str[i] == 32)
		i--;
	while(!(str[i] == '\t' || str[i] == 32))
		i--;
	i++;
	while (str[i])
	{
		if (str[i] == '\t' || str[i] == 32)
			break;
		write(1, &str[i], 1);
		i++;
	}
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		do_stuff(av[1]);
	}
	write(1, "\n", 1);
}