#include <unistd.h>

void do_stuff(char *str)
{
	int i = 0;
	while((str[i] == 32 || str[i] == '\t') && str[i])
		i++;
	while(str[i])
	{
		if (str[i] == 32 || str[i] == '\t')
		{
			write(1, " ", 1);
			while ((str[i] == 32 || str[i] == '\t') && str[i])
				i++;
		}
		else
		{
			write(1, &str[i], 1);
			i++;
		}
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